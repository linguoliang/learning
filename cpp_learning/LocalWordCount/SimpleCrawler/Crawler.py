import bs4
import queue
import requests
import threading
import time
import os
import uuid

class Crawler():
  def __init__(self, filePath, seeds=[], timeout=1, maxCount=10, threadNum=4, pauseTime=5,
               headers={
              'Connection':'keep-alive',
              'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8',
              'Accept-Language':'en-US,en;q=0.8,zh-CN;q=0.6,zh;q=0.4',
              'User-Agent':'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/47.0.2526.111 Safari/537.36'
              }):
    self.headers_ = headers
    self.filePath_ = filePath
    self.timeout_ = timeout
    self.maxCount_ = maxCount
    self.threadNum_ = threadNum
    self.pauseTime_ = pauseTime
    self.urlCount_ = 0
    self.urlVisited_ = self._UrlVisited()
    self.urlQueue_ = self._UrlQueue()
    self.fileLock_ = threading.Lock()
    self.printLock_ = threading.Lock()

    for seed in seeds:
      self.urlQueue_.put(seed.strip('/'))

    if os.path.exists(self.filePath_):
      os.remove(self.filePath_)

    with open(self.filePath_, 'w') as file:
      pass

  def _saveFile(self, data):
    try:
      with open(self.filePath_, 'a', encoding = 'utf-8') as file:
        file.write(data)
    except Exception as e:
      with self.printLock_:
        print('in _saveFile')
        print(e)

  def _generateItem(self, url, title, text):
    return '{0}\t{1}\t{2}\t{3}\t{4}\t{5}\t{6}\t{7}\t{8}\t{9}\t{10}\n'.format(1, 2, 3, 4, 5, 6, 7, uuid.uuid5(uuid.NAMESPACE_URL, url), title, text, url)

  def _fetch(self):
    while True:
      url = self.urlQueue_.get()

      if url not in self.urlVisited_:
        self.urlVisited_.add(url)

        try:
          time.sleep(self.pauseTime_)
          response = requests.get(url, headers=self.headers_, timeout=self.timeout_)
          content = response.content.decode('utf-8', 'ignore')
        except Exception as e:
          with self.printLock_:
            print('in _fetch requests.get')
            print(e)
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
            print('got: ' + str(self.urlCount_) + ': ' + url)
            print('saving: ' + url)

            try:
              title = ' '.join(soup.find('title').text.split())
            except:
              print('no title finded, use customized one')
              title = text[:6]
            
            self._saveFile(self._generateItem(url, title, text))
            self.urlCount_ += 1
          else:
            print('ignoring: ' + url)

          if self.urlCount_ > self.maxCount_:
            break

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
                with self.printLock_:
                  print('page ' + url + ' exists')

          except Exception as e:
            with self.printLock_:
              print(e)

  def crawl(self):
    threads = []
    for t in range(self.threadNum_):
      threads.append(threading.Thread(target=self._fetch))

    for t in threads:
      t.start()

    for t in threads:
      t.join()

  class _UrlVisited():
    def __init__(self):
      self.rwlock_ = threading.RLock()
      self.urlVisited_ = set()

    def __contains__(self, item):
      with self.rwlock_:
        return item in self.urlVisited_

    def add(self, item):
      with self.rwlock_:
        self.urlVisited_ |= {item}

  class _UrlQueue():
    def __init__(self):
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
          with self.printLock_:
            print(e)

    def put(self, item):
      with self.urlcv_:
        self.urlQueue_.append(item)
        self.urlcv_.notify_all()