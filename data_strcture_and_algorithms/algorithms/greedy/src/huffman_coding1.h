#ifndef HUFFMAN_CODING1_H_
#define HUFFMAN_CODING1_H_

#include <vector>
#include <tuple>

struct HuffmanNode1 {
  char data;
  int freq;
  struct HuffmanNode1 *left;
  struct HuffmanNode1 *right;

  HuffmanNode1() : left(nullptr), right(nullptr) {}
  HuffmanNode1(char d, int f, struct HuffmanNode1 *l, struct HuffmanNode1 *r)
      : data(d), freq(f), left(l), right(r) {}
  HuffmanNode1(char d, int f)
      : data(d), freq(f), left(nullptr), right(nullptr) {}
  bool operator<(const HuffmanNode1 &rhn) { return freq < rhn.freq; }
  bool operator>(const HuffmanNode1 &rhn) { return freq > rhn.freq; }
};

class HuffmanCode1 {
 public:
  explicit HuffmanCode1(std::vector<std::pair<char, int>> chs);
  ~HuffmanCode1();

  std::string get_code(char ch);

 private:
  void EnCode(std::vector<std::pair<char, int>> chs);
  void GenerateCode(const HuffmanNode1 &hn, std::string &str);
  bool is_leaf(const HuffmanNode1 &hn) { return hn.data != ' '; }

  std::vector<std::pair<char, std::string>> codes;
};

#endif
