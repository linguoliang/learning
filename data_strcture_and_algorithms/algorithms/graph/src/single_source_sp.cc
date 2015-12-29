#include "single_source_sp.h"

#include <climits>
#include <queue>
#include <vector>

#include "util.h"

using std::queue;
using std::vector;

void SP1();
void SP2();
void SingleSourceSP();

class Graph {
 public:
  explicit Graph(int v) {
    this->vertices = v;
    this->adj = vector<vector<int>>(v, vector<int>(v, INT_MAX));
    this->p = vector<int>(v);
    this->d = vector<int>(v);
  }
  void AddEdge(int v, int w, int c) { this->adj[v][w] = c; }
  void BFSSP(int s);
  void BellmanFord(int s);

 private:
  int vertices;
  vector<vector<int>> adj;
  vector<int> p;
  vector<int> d;

  void InitSingleSource(int s);
  void Relax(int s, int i, int j);
};

// loop is not permitted
void Graph::BFSSP(int s) {
  InitSingleSource(s);

  queue<int> q;
  q.push(s);

  while (!q.empty()) {
    int cur = q.front();
    q.pop();

    for (int i = 0; i < this->vertices; ++i) {
      if (adj[cur][i] != INT_MAX) {
        q.push(i);
        Relax(s, cur, i);
  PrintArray(d);
      }
    }
  }

  PrintArray(p);
  PrintArray(d);
}

void Graph::BellmanFord(int s) {}

void Graph::InitSingleSource(int s) {
  for (int i = 0; i < this->vertices; ++i) {
    d[i] = INT_MAX;
    p[i] = -1;
  }

  d[s] = 0;
}

void Graph::Relax(int s, int i, int j) {
  if (d[j] > d[i] + adj[i][j]) {
    d[j] = d[i] + adj[i][j];
    p[j] = i;
  }
}

void SP1() {
  Graph graph(7);
  graph.AddEdge(0, 1, 8);
  graph.AddEdge(1, 2, 8);
  graph.AddEdge(2, 3, 4);
  graph.AddEdge(3, 4, 4);
  graph.AddEdge(4, 5, 2);
  graph.AddEdge(5, 6, 2);
  graph.AddEdge(0, 2, 8);
  graph.AddEdge(2, 4, 4);
  graph.AddEdge(4, 5, 2);

  graph.BFSSP(0);
}

void SP2() {}

void SingleSourceSP() {
  SP1();
  SP2();
}
