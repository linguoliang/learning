import Crawler
import time
import yappi

class Timer(object):
    def __init__(self, verbose=False):
      self.verbose = verbose

    def __enter__(self):
      self.start = time.time()
      return self

    def __exit__(self, *args):
      self.end = time.time()
      self.secs = self.end - self.start
      self.msecs = self.secs * 1000  # millisecs
      if self.verbose:
          print('elapsed time: {0} ms'.format(self.msecs))

#crawler = Crawler.Crawler(dataFolder='D:\Documents\GitHub\learning\cpp_learning\LocalWordCount\RunningData\data',
#                          logFolder='D:\Documents\GitHub\learning\cpp_learning\LocalWordCount\RunningData\log',
#                          seeds=['http://news.dbanotes.net'], timeout=5, maxCount=100, threadNum=4, pauseTime=2)

crawler = Crawler.Crawler(dataFolder='D:\Documents\GitHub\learning\cpp_learning\LocalWordCount\RunningData\data',
                          logFolder='D:\Documents\GitHub\learning\cpp_learning\LocalWordCount\RunningData\log',
                          seeds=['https://wanqu.co/blog/2015-05-24-behind-the-scenes.html'], timeout=5, maxCount=10, threadNum=1, pauseTime=1)

yappi.start()
crawler.crawl()
yappi.get_func_stats().print_all()
yappi.get_thread_stats().print_all()