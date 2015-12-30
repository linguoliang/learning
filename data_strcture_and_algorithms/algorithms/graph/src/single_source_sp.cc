#include "single_source_sp.h"

#include <climits>
#include <iostream>
#include <queue>
#include <vector>
#include <stack>

#include "util.h"

using std::cout;
using std::endl;
using std::queue;
using std::vector;
using std::stack;

void SP1();
void SP2();
void SP3();
void SP4();
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
  // loop is not permitted and all edges have same weight
  void BFSSP(int s);
  bool BellmanFord(int s);
  void DAGSP(int s);
  void DAGSPUtil(int v, stack<int> &end_seq, vector<int> &color);
  void Dijsktra(int s);

 private:
  int vertices;
  vector<vector<int>> adj;
  vector<int> p;
  vector<int> d;

  void InitSingleSource(int s);
  void Relax(int s, int i, int j);
};

void Graph::BFSSP(int s) {
  InitSingleSource(s);

  queue<int> q;
  q.push(s);

  while (!q.empty()) {
    int cur = q.front();
    q.pop();

    for (int i = 0; i < this->vertices; ++i) {
      if (this->adj[cur][i] != INT_MAX) {
        q.push(i);
        Relax(s, cur, i);
      }
    }
  }

  PrintArray(p);
  PrintArray(d);
}

bool Graph::BellmanFord(int s) {
  InitSingleSource(s);

  for (int i = 0; i < this->vertices; ++i) {
    // process all edge
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

  PrintArray(p);
  PrintArray(d);

  return true;
}

void Graph::DAGSP(int s) {
  InitSingleSource(s);
  stack<int> end_seq;
  vector<int> color(this->vertices, 0);

  for (int i = 0; i < this->vertices; ++i) {
    if (color[i] == 0) {
      DAGSPUtil(i, end_seq, color);
    }
  }

  while (!end_seq.empty()) {
    int cur = end_seq.top();
    end_seq.pop();

    for (int i = 0; i < this->vertices; ++i) {
      if (this->adj[cur][i] != INT_MAX) {
        Relax(s, cur, i);
      }
    }
  }

  PrintArray(p);
  PrintArray(d);
}

void Graph::DAGSPUtil(int v, stack<int> &end_seq, vector<int> &color) {
  color[v] = 1;

  for (int i = 0; i < this->vertices; ++i) {
    if (this->adj[v][i] != INT_MAX) {
      if (color[i] == 0) {
        p[i] = v;
        DAGSPUtil(i, end_seq, color);
      }
    }
  }

  end_seq.push(v);
  color[v] = 2;
}

void Dijsktra(int s) {
}

void Graph::InitSingleSource(int s) {
  for (int i = 0; i < this->vertices; ++i) {
    d[i] = INT_MAX;
    p[i] = -1;
  }

  d[s] = 0;
}

void Graph::Relax(int s, int i, int j) {
  // INT_MAX is used to denote infinity, but may overflow.
  if (d[i] != INT_MAX) {
    if (d[j] > d[i] + this->adj[i][j]) {
      d[j] = d[i] + this->adj[i][j];
      p[j] = i;
    }
  }
}

void SP1() {
  Graph graph(7);
  graph.AddEdge(0, 1, 1);
  graph.AddEdge(1, 2, 1);
  graph.AddEdge(2, 3, 1);
  graph.AddEdge(3, 4, 1);
  graph.AddEdge(4, 5, 1);
  graph.AddEdge(5, 6, 1);
  graph.AddEdge(0, 2, 1);
  graph.AddEdge(2, 4, 1);
  graph.AddEdge(4, 5, 1);

  graph.BFSSP(0);
}

void SP2() {
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
  // positive weight cycle
  graph.AddEdge(5, 3, 2);
  graph.AddEdge(4, 2, 2);

  graph.BellmanFord(0);
}

void SP3() {
  Graph graph(5);

  graph.AddEdge(0, 1, -1);
  graph.AddEdge(0, 2, 4);
  graph.AddEdge(1, 2, 3);
  graph.AddEdge(1, 3, 2);
  graph.AddEdge(1, 4, 2);
  graph.AddEdge(3, 2, 5);
  graph.AddEdge(3, 1, 1);
  graph.AddEdge(4, 3, -3);

  graph.BellmanFord(0);
}

void SP4() {
  Graph graph(6);
  // negative weight cycle
  graph.AddEdge(0, 1, 5);
  graph.AddEdge(0, 3, -2);
  graph.AddEdge(3, 1, 2);
  graph.AddEdge(1, 2, 1);
  graph.AddEdge(2, 3, 2);
  graph.AddEdge(2, 4, -7);
  graph.AddEdge(4, 3, 3);
  graph.AddEdge(2, 5, 3);
  graph.AddEdge(4, 5, 10);

  cout << graph.BellmanFord(0) << endl;
}

void SP5() {
  Graph graph(6);

  graph.AddEdge(0, 1, 5);
  graph.AddEdge(0, 2, 3);
  graph.AddEdge(1, 2, 2);
  graph.AddEdge(1, 3, 6);
  graph.AddEdge(2, 3, 7);
  graph.AddEdge(2, 4, 4);
  graph.AddEdge(2, 5, 2);
  graph.AddEdge(3, 4, -1);
  graph.AddEdge(3, 5, 1);
  graph.AddEdge(4, 5, -2);

  graph.DAGSP(1);

  // test case for topological sort
  // Graph graph(6);

  // graph.AddEdge(5, 2, 1);
  // graph.AddEdge(5, 0, 1);
  // graph.AddEdge(4, 0, 1);
  // graph.AddEdge(4, 1, 1);
  // graph.AddEdge(2, 3, 1);
  // graph.AddEdge(3, 1, 1);
}

void SingleSourceSP() {
  cout << "BFS SP" << endl;
  SP1();

  cout << "Bellman Ford" << endl;
  SP2();
  SP3();
  SP4();

  cout << "DAG SP" << endl;
  SP5();
}
