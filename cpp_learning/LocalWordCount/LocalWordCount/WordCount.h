#pragma once

#include "Conf.h"

class WordCount {
 public:
  WordCount(const Conf &conf);
  ~WordCount();

  void Count();

 private:
  const Conf &conf;
};