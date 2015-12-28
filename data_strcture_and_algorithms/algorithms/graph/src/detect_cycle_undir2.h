#ifndef DETECT_CYCLE_UNDIR2_H_
#define DETECT_CYCLE_UNDIR2_H_

#include <list>
#include <vector>

class Graph3 {
 public:
  explicit Graph3(int v) {
    this->vertices = v;
    adj = new std::list<int>[v];
  }
  ~Graph3() { delete[] adj; }
  void AddEdge(int v, int w);
  bool isCyclic();

 private:
  int vertices;
  std::list<int>* adj;
  bool isCyclicUtil(int v, std::vector<bool>& isVisited, int parent);
};

#endif
