from Crawler import Crawler

crawler = Crawler(filePath = r'D:\Documents\GitHub\learning\cpp_learning\LocalWordCount\data\CrawlerOut.txt',
                  seed = 'http://news.dbanotes.net', timeout = 5, maxCount = 10)
crawler.crawl()