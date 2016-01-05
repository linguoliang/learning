#include "orienteer.h"

#include <climits>
#include <fstream>
#include <iostream>
#include <vector>
#include <utility>

#include "util.h"

using std::cout;
using std::endl;
using std::fstream;
using std::make_pair;
using std::pair;
using std::vector;

class OriGraph {
 public:
  vector<int> p;

  explicit OriGraph(int v) {
    this->vertices = v;
    this->adj = vector<vector<int>>(v, vector<int>(v, INT_MAX));
    this->d = vector<int>(v);
    this->p = vector<int>(v);
  }
  void AddEdge(int v, int w, int c) {
    this->adj[v][w] = c;
    this->adj[w][v] = c;
  }
  bool BellmanFord(int s);

 private:
  int vertices;
  vector<vector<int>> adj;
  vector<int> d;

  void InitSingleSource(int s);
  void Relax(int s, int i, int j);
};

bool OriGraph::BellmanFord(int s) {
  InitSingleSource(s);

  for (int i = 0; i < this->vertices; ++i) {
    for (int j = 0; j < this->vertices; ++j) {
      for (int k = 0; k < this->vertices; ++k) {
        if (this->adj[j][k] != INT_MAX) {
          Relax(s, j, k);
        }
      }
    }
  }

  for (int i = 0; i < this->vertices; ++i) {
    for (int j = 0; j < this->vertices; ++j) {
      if (this->adj[i][j] != INT_MAX) {
        if (d[j] > d[i] + this->adj[i][j]) {
          return false;
        }
      }
    }
  }

  return true;
}

void OriGraph::InitSingleSource(int s) {
  for (int i = 0; i < this->vertices; ++i) {
    d[i] = INT_MAX;
    p[i] = -1;
  }

  d[s] = 0;
}

void OriGraph::Relax(int s, int i, int j) {
  if (d[i] != INT_MAX) {
    if (d[j] > d[i] + this->adj[i][j]) {
      d[j] = d[i] + this->adj[i][j];
      p[j] = i;
    }
  }
}

class Orienteering {
 public:
  void main();

 private:
  int w;
  int h;
  vector<vector<char>> m;
  vector<int> cps;
  int sp;
  int ep;

  void ReadMap();
  void CalDis();
  int getIndex(int i, int j) { return (i - 1) * (this->w - 2) + j - 1; }
  int getDistance(int s, int g, const vector<int>& p) {
    int count = 0;
    int n = g;
    while (n != -1) {
      ++count;
      n = p[n];
    }
    return count - 1;
  }
};

void Orienteering::main() {
  ReadMap();
  CalDis();
}

void Orienteering::ReadMap() {
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
        sp = getIndex(i, j);
      } else if (ch == 'G') {
        ep = getIndex(i, j);
      }
    }
  }
}

void Orienteering::CalDis() {
  OriGraph g((this->w - 2) * (this->h - 2));

  vector<vector<int>> direct{{0, 1}, {0, -1}, {-1, 0}, {1, 0}};

  for (int i = 0; i < this->h; ++i) {
    for (int j = 0; j < this->w; ++j) {
      if (this->m[i][j] != '#') {
        for (int d = 0; d < 4; ++d) {
          int ni = i + direct[d][0];
          int nj = j + direct[d][1];

          if (this->m[ni][nj] != '#') {
            g.AddEdge(getIndex(i, j), getIndex(ni, nj), 1);
          }
        }
      }
    }
  }

  g.BellmanFord(this->sp);
  vector<int> pos = g.p;
  g.BellmanFord(this->ep);
  vector<int> poe = g.p;

  if (this->cps.size() > 1) {
    vector<int> sp_to_cps;
    vector<int> cps_to_ep;
    vector<int> cp_to_cp;

    for (int cp : cps) {
      sp_to_cps.push_back(getDistance(sp, cp, pos));
      cps_to_ep.push_back(getDistance(ep, cp, poe));
    }

    g.BellmanFord(cps[0]);
    vector<int> pocps = g.p;

    PrintArray(pos);
    PrintArray(poe);
    PrintArray(pocps);
    PrintArray(sp_to_cps);
    PrintArray(cps_to_ep);

  } else if (this->cps.size() == 1) {
    int sp_to_cps = getDistance(sp, cps[0], pos);

    int cps_to_ep = getDistance(ep, cps[0], poe);

    cout << sp_to_cps + cps_to_ep << endl;
  } else {
    cout << getDistance(sp, ep, pos) << endl;
  }
}

void Orienteer() {
  Orienteering o;
  o.main();
}
