import Crawler

#crawler = Crawler.Crawler(filePath=r'D:\Documents\GitHub\learning\cpp_learning\LocalWordCount\data\CrawlerOut.txt',
#                  seeds=['https://wanqu.co/blog/2015-05-24-behind-the-scenes.html', 'http://news.dbanotes.net'], timeout=5, maxCount=5000, threadNum=64, pauseTime=10)

crawler = Crawler.Crawler(filePath=r'D:\Documents\GitHub\learning\cpp_learning\LocalWordCount\data\CrawlerOut.txt',
                  seeds=['https://wanqu.co/blog/2015-05-24-behind-the-scenes.html'], timeout=5, maxCount=5000, threadNum=1, pauseTime=0)

crawler.crawl()