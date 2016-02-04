import bs4
import json
import logging
import os
import queue
import random
import re
import requests
import threading
import time
import uuid

class CrawlerConf(object):
  def __init__(self, confFile):
    if len(confFile) == 0:
      raise ValueError("conf file isn't set")
    with open(confFile, 'r') as cf:
      j = json.load(cf)

    self.proxies_ = j['crawler']['proxies']
    self.seeds_ = j['crawler']['seeds']
    self.timeout_ = j['crawler']['timeout']
    self.maxCount_ = j['crawler']['max count']
    self.threadNum_ = j['crawler']['thread num']
    self.pauseTime_ = j['crawler']['pause time']
    self.headers_ = j['crawler']['headers']

    fetchedFolder = j['fetched folder']

    if fetchedFolder == '':
      fetchedFolder = os.getcwd()
    else:
      if not os.path.exists(fetchedFolder):
        os.makedirs(fetchedFolder)
    self.fetchedPath_ = os.path.join(fetchedFolder.strip('/'), 'CrawlerData_' + time.strftime('%Y-%m-%d_%H-%M-%S', time.localtime()) + '.txt')
    
    logFolder = j['log folder']

    if logFolder == '':
      logFolder = os.getcwd()
    else:
      if not os.path.exists(logFolder):
        os.makedirs(logFolder)
    logPath = os.path.join(logFolder.strip('/'), 'CrawlerLog_' + time.strftime('%Y-%m-%d_%H-%M-%S', time.localtime()) + '.txt')
      
    level = getattr(logging, j['crawler']['log level'].upper(), None)

    if not isinstance(level, int):
      raise ValueError('invalid log level: %s' % loglevel)

    logging.basicConfig(filename=logPath, level=level,
                    format='%(asctime)s:%(levelname)s:%(message)s',
                    datefmt='%Y-%m-%d %H:%M:%S')
    logging.info('timeout: {0}'.format(self.timeout_))
    logging.info('max count: {0}'.format(self.maxCount_))
    logging.info('thread num: {0}'.format(self.threadNum_))
    logging.info('pause time: {0}'.format(self.pauseTime_))
    logging.info('headers: {0}'.format(self.headers_))
    logging.info('crawler data: {0}'.format(self.fetchedPath_))
    logging.info('crawler log: {0}'.format(logPath))
    logging.info('setup crawler')
    logging.info('add seeds')

class Crawler(object):
  def __init__(self, crawlerConf):
    self.crawlerConf = crawlerConf

    self.proxies_ = []
    for p in crawlerConf.proxies_:
      if re.search('^\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}:\d{1,4}$', p):
        p = 'http://' + p

      self.proxies_.append({'http': p, 'https': p})

    self.urlCount_ = 0
    self.fileLock_ = threading.Lock()
    self.logLock_ = threading.Lock()
    self.urlVisited_ = self._UrlVisited()
    self.urlQueue_ = self._UrlQueue(self.logLock_)

    for seed in crawlerConf.seeds_:
      self.urlQueue_.put(seed.strip('/'))

  def _saveFile(self, data):
    try:
      with open(self.crawlerConf.fetchedPath_, 'a', encoding = 'utf-8') as file:
        file.write(data)
    except Exception as e:
      with self.logLock_:
        logging.info('data unsaved')
        logging.debug('in _saveFile')
        logging.debug(e)

  def _generateItem(self, url, title, text):
    return '{0}\t{1}\t{2}\t{3}\t{4}\t{5}\t{6}\t{7}\t{8}\t{9}\t{10}\n'.format(1, 2, 3, 4, 5, 6, 7, uuid.uuid5(uuid.NAMESPACE_URL, url), title, text, url)

  def _fetch(self):
    while True:
      url = self.urlQueue_.get()

      if url not in self.urlVisited_:
        self.urlVisited_.add(url)

        try:
          time.sleep(self.crawlerConf.pauseTime_)
          response = requests.get(url, headers=self.crawlerConf.headers_, timeout=self.crawlerConf.timeout_,
                                  proxies=self.proxies_[random.randint(0, len(self.proxies_) - 1)])
          content = response.content.decode('utf-8', 'ignore')
        except Exception as e:
          with self.logLock_:
            logging.debug('in _fetch: requests.get')
            logging.debug(e)
          continue
        
        soup = bs4.BeautifulSoup(content, 'html.parser')
        
        #won't work for English words.
        #text = ' '.join([t.text.replace('\n', ' ').replace('\r', ' ')
        #                .replace('\t', ' ').replace(' ', ' ')
        #                for t in soup.find_all('p')])

        text = ''
        for w in [t.text.split() for t in soup.find_all('p')]:
            text += ' '.join(w)

        with self.fileLock_:
          if len(text) > 0:
            logging.info('got: ' + str(self.urlCount_) + ': ' + url)
            logging.info('saving: ' + url)

            try:
              title = ' '.join(soup.find('title').text.split())
            except:
              logging.info('no title finded, use customized one')
              title = text[:6]
            
            self._saveFile(self._generateItem(url, title, text))
            self.urlCount_ += 1
          else:
            logging.info('ignoring: ' + url)

          if self.urlCount_ > self.crawlerConf.maxCount_:
            return

        for l in soup.find_all('a'):
          try:
            newUrl = str(l['href'])

            if len(newUrl) > 0:
              if newUrl.startswith('/'):
                newUrl = url + newUrl
              elif newUrl.startswith('http') or newUrl.startswith('https'):
                pass
              else:
                continue

              newUrl = newUrl.strip('/')

              if newUrl not in self.urlVisited_ and newUrl not in self.urlQueue_:
                self.urlQueue_.put(newUrl)
              else:
                with self.logLock_:
                  logging.info('page ' + url + ' exists')

          except Exception as e:
            with self.logLock_:
              logging.warning(e)

  def crawl(self):
    threads = []
    for t in range(self.crawlerConf.threadNum_):
      threads.append(threading.Thread(target=self._fetch))

    for t in threads:
      t.start()

    for t in threads:
      t.join()

  class _UrlVisited(object):
    def __init__(self):
      self.rwlock_ = threading.RLock()
      self.urlVisited_ = set()

    def __contains__(self, item):
      with self.rwlock_:
        return item in self.urlVisited_

    def add(self, item):
      with self.rwlock_:
        self.urlVisited_ |= {item}

  class _UrlQueue(object):
    def __init__(self, logLock):
      self.logLock_ = logLock
      self.urlcv_ = threading.Condition()
      self.urlQueue_ = queue.deque()

    def __contains__(self, item):
      with self.urlcv_:
        return item in self.urlQueue_

    def get(self):
      with self.urlcv_:
        if not self.urlQueue_:
          #todo: self.urlcv_.wait()不行，不管是否指定urlcv_的lock都不行，为什么？
          self.urlcv_.wait_for(lambda : self.urlQueue_)

        try:
          item = self.urlQueue_.popleft()
          return item
        except Exception as e:
          with self.logLock_:
            logging.warning(e)

    def put(self, item):
      with self.urlcv_:
        self.urlQueue_.append(item)
        self.urlcv_.notify_all()