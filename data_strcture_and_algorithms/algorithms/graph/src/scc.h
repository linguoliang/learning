#ifndef SCC_H_
#define SCC_H_

#include <list>

class Scc {
 public:
  explicit Scc(int v) {
    this->vertices = v;
    this->adj = new std::list<int>[v];
  }
  void AddEdge(int v, int w) { this->adj[v].push_back(w); }
  void GetScc();

 private:
  int vertices;
  std::list<int>* adj;
};

#endif
