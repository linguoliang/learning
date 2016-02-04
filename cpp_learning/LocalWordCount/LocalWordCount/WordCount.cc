#include "WordCount.h"

#include <fstream>
#include <iostream>
#include <string>

#include "Conf.h"

using std::cout;
using std::endl;

#ifdef _MSC_VER

using std::wifstream;
using std::wstring;

using ifstream = wifstream;
using string = wstring;

#else

using std::ifstream;
using std::string;

using ifstream = ifstream;
using string = string;

#endif // ifdef _MSC_VER


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