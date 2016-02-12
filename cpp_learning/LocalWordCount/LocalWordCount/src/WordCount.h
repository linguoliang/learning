#ifndef WORDCOUNT_H_
#define WORDCOUNT_H_

#include <string>
#include <unordered_map>

#include "cppjieba/Jieba.hpp"
#include "cppjieba/KeywordExtractor.hpp"

#include "Conf.h"

// 如果Conf.h没有包含WordCount.h，
// 则一下声明无必要。
//
// 如果包含了，则有必要，原因如下，
// 此处的声明是有必要的，
// conf.h中已经include了WordCount.h，
// 而WordCount.h有header guard，
// 因此此时Conf.h不会在WordCount.h中再次被include，
// 故如果无声明，下面定义中的Conf就会提示未知类型。
// class Conf;

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
