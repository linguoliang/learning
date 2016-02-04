import unittest

from Crawler import Crawler

class Test_SimpleCrawlerTest(unittest.TestCase):
    def testFilePath(self):
      try:
        with open('D:\Documents\GitHub\learning\cpp_learning\LocalWordCount\data\test.txt') as file:
          print(file)
      except:
        print('normal error')

if __name__ == '__main__':
    unittest.main()