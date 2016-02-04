#ifndef WORDCOUNT_H_
#define WORDCOUNT_H_

#include <string>
#include <unordered_map>

#include "cppjieba/Jieba.hpp"
#include "cppjieba/KeywordExtractor.hpp"

#include "Conf.h"

class WordCount {
 public:
  WordCount(const Conf &conf, const cppjieba::Jieba &jieba,
            const cppjieba::KeywordExtractor &extractor);
  ~WordCount();

  void Count();

 private:
  const Conf &conf_;
  const cppjieba::Jieba &jieba_;
  const cppjieba::KeywordExtractor &extractor_;
  std::unordered_map<std::string, size_t> wc_;
};

#endif /* ifndef WORDCOUNT_H_ */
