#include "huffman_coding.h"

#include <algorithm>
#include <string>
#include <tuple>
#include <vector>

using std::find_if;
using std::pair;
using std::string;
using std::vector;

HuffmanCode::HuffmanCode(vector<pair<char, int>> chs) { EnCode(chs); }

HuffmanCode::~HuffmanCode() {}

string HuffmanCode::get_code(char ch) {
  auto ret =
      find_if(codes.begin(), codes.end(),
              [&](const pair<char, string> &c) { return c.first == ch; });
  return ret->second;
}

void HuffmanCode::EnCode(vector<pair<char, int>> chs) {
  MinHeap<HuffmanNode> mh_;

  for (auto ch : chs) {
    mh_.InsertKey(HuffmanNode(ch.first, ch.second));
  }

  while (mh_.size() != 1) {
    // must use the new to create object on the heap.
    auto hn1 = new HuffmanNode(mh_.ExtractMin());
    auto hn2 = new HuffmanNode(mh_.ExtractMin());
    mh_.InsertKey(HuffmanNode(' ', hn1->freq + hn2->freq, hn1, hn2));
  }

  auto min = mh_.ExtractMin();
  string str;

  GenerateCode(min, str);
}

void HuffmanCode::GenerateCode(const HuffmanNode &hn, string &str) {
  if (hn.left != nullptr) {
    str.push_back('0');
    GenerateCode(*hn.left, str);
    str.pop_back();
  }

  if (hn.right != nullptr) {
    str.push_back('1');
    GenerateCode(*hn.right, str);
    str.pop_back();
  }

  if (is_leaf(hn)) {
    codes.push_back({hn.data, str});
  }
}
