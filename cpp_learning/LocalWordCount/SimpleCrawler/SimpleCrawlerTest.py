import unittest

from Crawler import Crawler

class Test_SimpleCrawlerTest(unittest.TestCase):
    def testFilePath(self):
      try:
        with open(r'D:\Documents\GitHub\learning\cpp_learning\LocalWordCount\data\test.txt') as file:
          print(file)
      except:
        print('normal error')

    def testCrawler(self):
      c = Crawler('http://news.dbanotes.net')
      c.crawl()

if __name__ == '__main__':
    unittest.main()