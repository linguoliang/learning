#include "detect_cycle_undir2.h"

#include <vector>

using std::vector;

void Graph3::AddEdge(int v, int w) {
  this->adj[v].push_back(w);
  this->adj[w].push_back(v);
}

bool Graph3::isCyclic() {
  vector<bool> isVisited(this->vertices, false);

  for (int i = 0; i < this->vertices; ++i) {
    // 避免重复访问，思想类似使用union-find的那个方法。
    if (!isVisited[i] && isCyclicUtil(i, isVisited, -1)) {
      return true;
    }
  }

  return false;
}

bool Graph3::isCyclicUtil(int v, vector<bool>& isVisited, int parent) {
  isVisited[v] = true;

  for (int n : this->adj[v]) {
    if (!isVisited[n]) {
      if (isCyclicUtil(n, isVisited, v)) {
        return true;
      }
    } else if (n != parent) {
      return true;
    }
  }
  return false;
}
