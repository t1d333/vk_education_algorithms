#include "SetGraph.h"
#include <iostream>
#include <vector>
#include <cassert>

SetGraph::SetGraph(int k): adjList(std::vector<std::set<int>>(k)), prevAdjList(std::vector<std::set<int>>(k)) {}

SetGraph::SetGraph(const IGraph& other): adjList(std::vector<std::set<int>>(other.VerticesCount())), prevAdjList(std::vector<std::set<int>>(other.VerticesCount())) {
    for (int i = 0; i < other.VerticesCount(); ++i) {
    std::vector<int> vertices = other.GetNextVertices(i);
    for (int v : vertices) {
      adjList[i].insert(v);
      prevAdjList[v].insert(i);
    }
  }
}

int SetGraph::VerticesCount() const {
  return adjList.size(); 
}

void SetGraph::AddEdge(int from, int to) {
  assert(from >= 0 && (to < adjList.size()));
  adjList[from].insert(to);
  prevAdjList[to].insert(from);
}

std::vector<int> SetGraph::GetNextVertices(int vertex) const {
  assert(vertex >= 0 && (vertex < adjList.size()));
  return std::vector<int>(adjList[vertex].begin(), adjList[vertex].end());
}


std::vector<int> SetGraph::GetPrevVertices(int vertex) const {
  assert(vertex >= 0 && (vertex < adjList.size()));
  return std::vector<int>(prevAdjList[vertex].begin(), prevAdjList[vertex].end());
}
