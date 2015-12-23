#include "graph.h"
#include "heap.h"

#include <iostream>

using std::cout;
using std::endl;

int main() {
  // MinHeap heap(20);

  // heap.InsertKey(3);
  // heap.InsertKey(2);
  // heap.InsertKey(1);
  // heap.InsertKey(15);
  // heap.InsertKey(5);
  // heap.InsertKey(4);
  // heap.InsertKey(45);
  // cout << heap.GetMin() << endl;
  // cout << heap.ExtractMin() << endl;
  // cout << heap.ExtractMin() << endl;
  // cout << heap.ExtractMin() << endl;
  // cout << heap.ExtractMin() << endl;
  // cout << heap.ExtractMin() << endl;
  // cout << heap.ExtractMin() << endl;
  // cout << heap.ExtractMin() << endl;

  Graph graph(4);
  graph.AddEdge(0, 1);
  graph.AddEdge(0, 2);
  graph.AddEdge(1, 2);
  graph.AddEdge(2, 0);
  graph.AddEdge(2, 3);
  graph.AddEdge(3, 3);

  graph.BFS(2);
  graph.DFSLoop();
  graph.DFSLoop(2);
  graph.DFSRec();
  graph.DFSRec(2);
  return 0;
}
