#include "WordCount.h"

#include <fstream>
#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <utility>

#include "cppjieba/Jieba.hpp"
#include "cppjieba/KeywordExtractor.hpp"

#include "Conf.h"
#include "Util.h"

using std::cout;
using std::endl;
using std::pair;
using std::vector;
using std::unordered_map;

#ifdef _MSC_VER

using std::wifstream;
using std::wofstream;
using std::wstring;

using ifstream = wifstream;
using ofstream = wofstream;
using string = wstring;

#else

using std::ifstream;
using std::ofstream;
using std::string;

using ifstream = ifstream;
using ofstream = ofstream;
using string = string;

#endif  // ifdef _MSC_VER

using cppjieba::Jieba;

WordCount::WordCount(const Conf &conf, const cppjieba::Jieba &jieba,
                     const cppjieba::KeywordExtractor &extractor)
    : conf_(conf), jieba_(jieba), extractor_(extractor) {}

WordCount::~WordCount() {}

void WordCount::Count() {
  ifstream ifs(conf_.fetchedPath_);
  if (!ifs.is_open()) {
    cout << "cannot open " << conf_.fetchedPath_ << endl;
    return;
  }

  Timer timer;

  string item;
  while (getline(ifs, item)) {
    if (item.size() == 0) {
      continue;
    }

    auto start = item.find_first_of('7') + 2;
    auto end = item.find_first_of('\t', start);
    string wordId = item.substr(start, end - start);

    start = end + 1;
    end = item.find_first_of('\t', end);
    string title = item.substr(start, end - start);

    start = end + 1;
    end = item.find_first_of('\t', end);
    string text = item.substr(start, end - start);

    vector<string> words;
    jieba_.Cut(text, words);

    vector<pair<string, double>> ww;
    extractor_.Extract(text, ww, 1);
    words.push_back(ww[0].first);

    for (const auto &word : words) {
      if (wc_.find(word) == wc_.end()) {
        wc_[word] = 1;
      } else {
        wc_[word] += 1;
      }
    }
  }

  ofstream ofs(conf_.resPath_);
  if (!ofs.is_open()) {
    cout << "cannot open " << conf_.resPath_ << endl;
    return;
  }

  for (const auto &p : wc_) {
    ofs << p.first << "\t" << p.second << "\t"
        << static_cast<double>(p.second) / wc_.size() << endl;
  }
}
