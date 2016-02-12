#include "gtest/gtest.h"

#include "Conf.h"

TEST(ConfTest, Test1) {
  Conf conf(
      "/home/chaomai/Documents/Codes/Current/GitHub/learning/cpp_learning/"
      "LocalWordCount/RunningData/conf/conf.json");
  // ASSERT_EQ(
  // "/home/chaomai/Documents/Codes/Current/GitHub/learning/cpp_learning/"
  // "LocalWordCount/RunningData/dict/jieba.dict.utf8",
  // conf.dictPath_);
}
