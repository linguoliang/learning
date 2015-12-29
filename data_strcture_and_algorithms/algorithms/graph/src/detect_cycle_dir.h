#ifndef DETECT_CYCLE_DIR_H_
#define DETECT_CYCLE_DIR_H_

#include <list>
#include <vector>

class Graph1 {
 public:
  explicit Graph1(int v) {
    this->vertices = v;
    adj = new std::list<int>[v];
  }
  ~Graph1() { delete[] adj; }
  void AddEdge(int v, int w);
  bool isCyclic();
  bool isCyclicUtil(int v, std::vector<bool> &isVisited,
                    std::vector<bool> &rec);

 private:
  int vertices;
  std::list<int> *adj;
};

#endif
