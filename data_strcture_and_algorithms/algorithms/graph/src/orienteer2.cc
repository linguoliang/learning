#include "orienteer2.h"

#include <fstream>
#include <vector>
#include <utility>

using std::fstream;
using std::make_pair;
using std::pair;
using std::vector;

class Orienteering2 {
 public:
  void main();

 private:
  int w;
  int h;
  vector<vector<char>> m;
  vector<int> cps;
  pair<int, int> sp;
  vector<vector<int>> direct{{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

  void ReadMap();
  void CalDis();
  int getIndex(int i, int j) { return i * this->w + j; };
};

void Orienteering2::main() {
  ReadMap();
  CalDis();
}

void Orienteering2::ReadMap() {
  fstream fs;
  fs.open("../src/example2.txt", fstream::in);

  fs >> this->w >> this->h;

  this->m = vector<vector<char>>(h, vector<char>(w));

  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      char ch;
      fs >> ch;
      this->m[i][j] = ch;

      if (ch == '@') {
        cps.push_back(getIndex(i, j));
      } else if (ch == 'S') {
        sp = make_pair(i, j);
      }
    }
  }
}

void Orienteering2::CalDis() {}

void Orienteer2() {
  Orienteering2 o;
  o.main();
}
