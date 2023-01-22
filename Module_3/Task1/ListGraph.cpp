#include "ListGraph.h"
#include <vector>
#include <cassert>

ListGraph::ListGraph(int k): adjList(std::vector<std::vector<int>>(k)), prevAdjList(std::vector<std::vector<int>>(k)) {} 

ListGraph::ListGraph(const IGraph& other): adjList(std::vector<std::vector<int>>(other.VerticesCount())), prevAdjList(std::vector<std::vector<int>>(other.VerticesCount())) {
  for (int i = 0; i < other.VerticesCount(); ++i) {
    std::vector<int> vertices = other.GetNextVertices(i);
    for (int v : vertices) {
      AddEdge(i, v);
    }
  }
}

void ListGraph::AddEdge(int from, int to) {
  assert((from >= 0) && to < adjList.size());
  adjList[from].push_back(to);
  prevAdjList[to].push_back(from);
}

int ListGraph::VerticesCount() const {
  return adjList.size();
}

std::vector<int> ListGraph::GetNextVertices(int vertex) const {
  assert(vertex >= 0 && vertex <= adjList.size());
  return adjList[vertex];
}

std::vector<int> ListGraph::GetPrevVertices(int vertex) const {
  assert(vertex >= 0 && vertex <= adjList.size());
  return prevAdjList[vertex];
}
