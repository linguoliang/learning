import re
import urllib.request
import http.cookiejar

from collections import deque

# another method to custimze header:
# https://jecvay.com/2014/09/python3-web-bug-series3.html

def makeMyOpener(head={
  'Connection':'keep-alive',
  'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8',
  'Accept-Language':'en-US,en;q=0.8,zh-CN;q=0.6,zh;q=0.4',
  'User-Agent':'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/47.0.2526.111 Safari/537.36'
  }):
  cookiejar = http.cookiejar.CookieJar()
  opener = urllib.request.build_opener(urllib.request.HTTPCookieProcessor(cookiejar))
  header = []
  for key,value in head.items():
    elem = (key,value)
    header.append(elem)
  opener.addheaders = header
  return opener

def savaFile(data):
  path=''

queue = deque()
visited = set()

#url = 'http://news.dbanotes.net'
url = 'http://www.qq.com'

queue.append(url)
count = 0

while queue:
  url = queue.popleft()
  visited |= {url}

  print('got: ' + str(count))
  print('geting: ' + url)

  count += 1
  urlop = opener.open(url, timeout=10)

  if 'html' not in urlop.getheader('Content-Type'):
    continue

  try:
    data = urlop.read().decode('gbk')
  except:
    continue

  print(data)

  linkre = re.compile('href="(.+?)"')

  for l in linkre.findall(data):
    if 'http' in l and l not in visited:
      queue.append(l)
      print('add ' + l)
