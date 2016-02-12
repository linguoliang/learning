#ifndef CONF_H_
#define CONF_H_

#include <string>

// 此处包含无必要，用声明即可，
// 如果包含了Count中还会有额外的麻烦。
// #include "WordCount.h"

class WordCount;

class Conf {
  friend class WordCount;
  // 这个仅仅是为了试试friend，
  // not a good practice
  friend int main(int argc, char *argv[]);

 public:
  Conf(std::string confPath);
  ~Conf() {}

 private:
  std::string fetchedPath_;
  std::string logPath_;
  std::string resPath_;
  std::string dictPath_;
  std::string modelPath_;
  std::string userDictPath_;
  std::string idfPath_;
  std::string stopWordPath_;
};

#endif /* ifndef CONF_H_ */
