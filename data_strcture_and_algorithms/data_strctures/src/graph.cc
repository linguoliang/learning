#include "graph.h"

#include <climits>
#include <iostream>
#include <list>
#include <queue>
#include <stack>
#include <vector>

using std::cout;
using std::endl;
using std::list;
using std::queue;
using std::stack;
using std::vector;

void Graph::AddEdge(int v, int w) { this->adj[v].push_back(w); }

void Graph::BFS(int v) {
  vector<int> distance(this->vertices, -1);
  vector<int> parents(this->vertices, -1);
  queue<int> q;

  distance[v] = 0;
  q.push(v);

  while (!q.empty()) {
    int cur = q.front();
    q.pop();
    int cur_dis = distance[cur];
    cout << cur << " ";

    for (int n : this->adj[cur]) {
      if (distance[n] == -1) {
        q.push(n);
        distance[n] = cur_dis + 1;
        parents[n] = cur;
      }
    }
  }
  cout << endl;
}

void Graph::DFSLoop() {
  vector<int> distance(this->vertices, -1);
  vector<int> parents(this->vertices, -1);

  for (int i = 0; i < this->vertices; ++i) {
    if (distance[i] == -1) {
      stack<int> s;

      distance[i] = 0;
      s.push(i);

      while (!s.empty()) {
        int cur = s.top();
        s.pop();
        int cur_dis = distance[cur];
        cout << cur << " ";

        for (int n : this->adj[cur]) {
          if (distance[n] == -1) {
            distance[n] = cur_dis + 1;
            parents[n] = cur;
            s.push(n);
          }
        }
      }
    }
  }
  cout << endl;
}

void Graph::DFSLoop(int v) {
  vector<int> distance(this->vertices, -1);
  vector<int> parents(this->vertices, -1);
  stack<int> s;

  distance[v] = 0;
  s.push(v);

  while (!s.empty()) {
    int cur = s.top();
    s.pop();
    int cur_dis = distance[cur];
    cout << cur << " ";

    for (int n : this->adj[cur]) {
      if (distance[n] == -1) {
        distance[n] = cur_dis + 1;
        parents[n] = cur;
        s.push(n);
      }
    }
  }
  cout << endl;
}

void Graph::DFSRec() {
  vector<int> distance(this->vertices, -1);
  vector<int> parents(this->vertices, -1);

  for (int i = 0; i < this->vertices; ++i) {
    if (distance[i] == -1) {
      distance[i] = 0;
      DFSUtil(i, distance, parents);
    }
  }
  cout << endl;
}

void Graph::DFSRec(int v) {
  vector<int> distance(this->vertices, -1);
  vector<int> parents(this->vertices, -1);

  distance[v] = 0;
  DFSUtil(v, distance, parents);
  cout << endl;
}

void Graph::DFSUtil(int v, vector<int> &distance, vector<int> &parents) {
  int cur_dis = distance[v];
  cout << v << " ";

  for (int n : this->adj[v]) {
    if (distance[n] == -1) {
      distance[n] = cur_dis + 1;
      parents[n] = v;
      DFSUtil(n, distance, parents);
    }
  }
}
