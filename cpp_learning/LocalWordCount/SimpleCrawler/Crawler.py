import bs4
import requests
import os.path

from collections import deque
from threading import Lock
from threading import Thread

class Crawler:
  def __init__(self,filePath, seed, timeout=1, maxCount=10, threadNum=4,
               headers={
              'Connection':'keep-alive',
              'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8',
              'Accept-Language':'en-US,en;q=0.8,zh-CN;q=0.6,zh;q=0.4',
              'User-Agent':'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/47.0.2526.111 Safari/537.36'
              }):
    self.headers_ = headers
    self.filePath_ = filePath
    self.seed_ = seed
    self.timeout_ = timeout
    self.maxCount_ = maxCount
    self.threadNum_ = threadNum
    self.urlCount_ = 1
    self.urlVisited_ = set()
    self.urlQueue_ = deque()
    self.urlQueue_.append(self.seed_)

    self.lock_ = Lock()
    self.fileLock_ = Lock()

    if not os.path.exists(self.filePath_):
      with open(self.filePath_, 'w') as file:
        file.write('')

  def _saveFile(self, data):
    try:
      with open(self.filePath_, 'a') as file:
        file.write(data)
    except:
      print('saving error')

  def crawl(self):
    pass