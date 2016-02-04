#include <string>

#include "gtest/gtest.h"

#include "Util.h"

using std::string;

TEST(trimTailTest, Test1) {
  string path =
    "D:\\Documents\\GitHub\\learning\\cpp_learning\\LocalWordCount\\RunningData\\fetched\\\\";

  ASSERT_EQ("D:\\Documents\\GitHub\\learning\\cpp_learning\\LocalWordCount\\RunningData\\fetched",
            trimTail(path, "\\"));
}
