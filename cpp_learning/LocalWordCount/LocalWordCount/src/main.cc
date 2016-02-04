#include "cppjieba/Jieba.hpp"
#include "cppjieba/KeywordExtractor.hpp"

#include "Conf.h"
#include "WordCount.h"

using cppjieba::Jieba;
using cppjieba::KeywordExtractor;

int main(int argc, char *argv[]) {
  Conf conf(
      "/home/chaomai/Documents/Codes/Current/GitHub/learning/cpp_learning/"
      "LocalWordCount/RunningData/conf/conf.json");
  Jieba jieba(conf.dictPath_, conf.modelPath_, conf.userDictPath_);
  KeywordExtractor extractor(conf.dictPath_, conf.modelPath_, conf.idfPath_,
                             conf.stopWordPath_);
  WordCount count(conf, jieba, extractor);
  count.Count();

  return 0;
}
