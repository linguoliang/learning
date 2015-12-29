#include "detect_cycle_dir.h"

#include <climits>
#include <iostream>
#include <stack>
#include <vector>

using std::cout;
using std::endl;
using std::stack;
using std::vector;

void Graph1::AddEdge(int v, int w) { this->adj[v].push_back(w); }

bool Graph1::isCyclic() {
  vector<bool> isVisited(this->vertices, false);
  // 这里rec的作用一开始不是很好理解，可以把rec看做一个stack，记录遍历的路径，
  // 遍历的时候，把路径上的每一个node都push到rec里面，如果下一次遇到的node在rec里面出现，那么就有cycle。
  // 只是用stack不方便查找node是否在rec里面，因此改用vector。
  vector<bool> rec(this->vertices, false);

  for (int i = 0; i < this->vertices; ++i) {
    if (isCyclicUtil(i, isVisited, rec)) {
      return true;
    }
  }

  return false;
}

bool Graph1::isCyclicUtil(int v, vector<bool>& isVisited, vector<bool>& rec) {
  if (!isVisited[v]) {
    isVisited[v] = true;
    rec[v] = true;

    for (int n : this->adj[v]) {
      if (!isVisited[n] && isCyclicUtil(n, isVisited, rec)) {
        return true;
      } else if (rec[n]) {
        return true;
      }
    }
  }

  rec[v] = false;
  return false;
}
