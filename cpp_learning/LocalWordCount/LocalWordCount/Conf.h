#pragma once

#include <string>

class Conf {

 public:
  Conf(std::string confPath);
  ~Conf() {}

//private:
  std::string fetchedPath_;
  std::string logPath_;
  std::string dictPath_;
  std::string modelPath_;
  std::string userDictPath_;
};