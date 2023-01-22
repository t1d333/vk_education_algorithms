#include "ArcGraph.h"


ArcGraph::ArcGraph(int k): vertexCount(k) {}

ArcGraph::ArcGraph(const IGraph& other): vertexCount(other.VerticesCount()) {
    for (int i = 0; i < other.VerticesCount(); ++i) {
    std::vector<int> vertices = other.GetNextVertices(i);
    for (int v : vertices) {
      edges.push_back(Edge(i, v));
    }
  }
}

void ArcGraph::AddEdge(int from, int to) {
  edges.push_back(Edge(from, to));
}

int ArcGraph::VerticesCount() const {
  return vertexCount;
}

std::vector<int> ArcGraph::GetNextVertices(int vertex) const {
  std::vector<int> result;
  for (Edge edge : edges) {
    if (edge.from == vertex) {
      result.push_back(edge.to);
    }
  }
  return result;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const {
  std::vector<int> result;
  for (Edge edge : edges) {
    if (edge.to == vertex) {
      result.push_back(edge.from);
    }
  }
  return result;

}
