#include "huffman_coding1.h"

#include <iostream>
#include <algorithm>
#include <queue>
#include <string>
#include <tuple>
#include <vector>

using std::cout;
using std::endl;
using std::find_if;
using std::pair;
using std::queue;
using std::string;
using std::vector;

HuffmanCode1::HuffmanCode1(vector<pair<char, int>> chs) { EnCode(chs); }

HuffmanCode1::~HuffmanCode1() {}

string HuffmanCode1::get_code(char ch) {
  auto ret =
      find_if(codes.begin(), codes.end(),
              [&](const pair<char, string> &c) { return ch == c.first; });
  return ret->second;
}

void HuffmanCode1::EnCode(vector<pair<char, int>> chs) {
  queue<HuffmanNode1> q1;
  queue<HuffmanNode1> q2;

  for (auto ch : chs) {
    q1.push(HuffmanNode1(ch.first, ch.second));
  }

  auto find_smallest = [&]() {
    HuffmanNode1 ret;
    if (!q1.empty() && !q2.empty()) {
      if (q1.front().freq > q2.front().freq) {
        ret = q2.front();
        q2.pop();
      } else {
        ret = q1.front();
        q1.pop();
      }
      return ret;
    }

    if (!q1.empty()) {
      ret = q1.front();
      q1.pop();
    }

    if (!q2.empty()) {
      ret = q2.front();
      q2.pop();
    }
    return ret;
  };

  while (!q1.empty() || q2.size() != 1) {
    auto n1 = new HuffmanNode1(find_smallest());
    auto n2 = new HuffmanNode1(find_smallest());

    q2.push(HuffmanNode1(' ', n1->freq + n2->freq, n1, n2));
  }

  string str;

  GenerateCode(q2.front(), str);
  q2.pop();
}

void HuffmanCode1::GenerateCode(const HuffmanNode1 &hn, string &str) {
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
