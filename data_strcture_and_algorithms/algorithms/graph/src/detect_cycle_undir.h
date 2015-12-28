#ifndef DETECT_CYCLE_UNDIR_H_
#define DETECT_CYCLE_UNDIR_H_

#include <climits>
#include <list>
#include <vector>

class Graph2 {
 public:
  explicit Graph2(int v) {
    this->vertices = v;
    adj = new std::list<int>[v];
    parents = std::vector<int>(v, INT_MIN);
  }
  ~Graph2() { delete[] adj; }
  void AddEdge(int v, int w);
  bool isCyclic();

 private:
  int vertices;
  std::vector<int> parents;
  std::list<int> *adj;
  int find(int v);
  void UnionSet(int v1, int v2);
};

#endif
