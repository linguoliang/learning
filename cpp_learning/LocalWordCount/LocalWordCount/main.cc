#include "Conf.h"
#include "WordCount.h"

int main(int argc, char *argv[]) {
  Conf conf("D:\\Documents\\GitHub\\learning\\cpp_learning\\LocalWordCount\\RunningData\\conf\\conf.json");
  WordCount count(conf);
  count.Count();

  return 0;
}