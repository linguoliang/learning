#include "orienteer.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <utility>

using std::cout;
using std::endl;
using std::fstream;
using std::make_pair;
using std::pair;
using std::vector;

class Orienteering {
 public:
  void main();

 private:
  vector<vector<char>> m;
  vector<pair<int, int>> checkPoints;
  pair<int, int> startPoint;
  pair<int, int> endPoint;

  void ReadMap();
};

void Orienteering::main() { ReadMap(); }

void Orienteering::ReadMap() {
  fstream fs;
  fs.open("../src/example1.txt", fstream::in);

  int w;
  int h;
  fs >> w >> h;

  this->m = vector<vector<char>>(h, vector<char>(w));

  for (int i = 0; i < h; ++i) {
    for (int j = 0; j < w; ++j) {
      char ch;
      fs >> ch;
      this->m[i][j] = ch;

      if (ch == '@') {
        checkPoints.push_back(make_pair(i, j));
      } else if (ch == 'S') {
        startPoint = make_pair(i, j);
      } else if (ch == 'G') {
        endPoint = make_pair(i, j);
      }
    }
  }
}

void Orienteer() {
  Orienteering o;
  o.main();
}
