#include "detect_cycle_undir.h"

void Graph2::AddEdge(int v, int w) {
  this->adj[v].push_back(w);
  this->adj[w].push_back(v);
}

bool Graph2::isCyclic() {
  for (int v = 0; v < this->vertices; ++v) {
    int x = find(v);
    for (int n : this->adj[v]) {
      // 由于这里无向图的表示中，vw和wv在邻接表里都会有，
      // 因此要避免重复处理。
      if (n > v) {
        int y = find(n);

        if (x == y) {
          return true;
        }

        UnionSet(x, y);
      }
    }
  }

  return false;
}

int Graph2::find(int v) {
  if (this->parents[v] == INT_MIN) {
    return v;
  } else {
    return find(this->parents[v]);
  }
}

void Graph2::UnionSet(int v1, int v2) {
  int p1 = find(v1);
  int p2 = find(v2);

  this->parents[p1] = p2;
}
