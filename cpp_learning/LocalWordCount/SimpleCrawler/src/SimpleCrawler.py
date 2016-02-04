import Crawler

confFile = 'D:\Documents\GitHub\learning\cpp_learning\LocalWordCount\RunningData\conf\conf.json'

crawler = Crawler.Crawler(Crawler.CrawlerConf(confFile))
crawler.crawl()