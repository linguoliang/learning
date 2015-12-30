#ifndef GRAPH_H_
#define GRAPH_H_

#include <list>
#include <vector>

class Graph {
 public:
  explicit Graph(int v) {
    this->vertices = v;
    adj = new std::list<int>[v];
  }
  void AddEdge(int v, int w);
  void BFS(int v);
  void DFSLoop();
  void DFSLoop(int v);
  void DFSRec();
  void DFSRec(int v);
  void DFSColorRec();
  void DFSColorUtil(int v, std::vector<int> &color, std::vector<int> &parents);
  void DFSColorLoop();

 private:
  int vertices;
  std::list<int> *adj;
  void DFSUtil(int v, std::vector<int> &distance, std::vector<int> &parents);
};

#endif
