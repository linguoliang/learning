#include "WordCount.h"

#include <fstream>
#include <iostream>
#include <string>

#include "Conf.h"

using std::cout;
using std::endl;
using std::ifstream;
using std::string;

WordCount::WordCount(const Conf &c): conf(c) {
}

WordCount::~WordCount() {
}

void WordCount::Count() {
  ifstream fs(conf.fetchedPath_);
  if (!fs.is_open()) {
    cout << "cannot open " << conf.fetchedPath_ << endl;
    return;
  }

  size_t lineNum = 0;
  string item;
  while (getline(fs, item)) {
    if (item.size() == 0) {
      continue;
    }

    auto start = item.find_first_of('7') + 2;
    auto end = item.find_first_of('\t', start);
    string wordId = item.substr(start, end - start);

    start = end + 1;
    end = item.find_first_of('\t', end);
    string word = item.substr(start, end - start);

    start = end + 1;
    end = item.find_first_of('\t', end);
    string text = item.substr(start, end - start);
  }
}