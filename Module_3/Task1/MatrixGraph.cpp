#include "MatrixGraph.h"
#include <iostream>
#include <vector>

MatrixGraph::MatrixGraph(const IGraph& other): matrix(other.VerticesCount() * other.VerticesCount()), vertexesCount(other.VerticesCount()) {
  for (int i = 0; i < other.VerticesCount(); ++i) {
    std::vector<int> vertices = other.GetNextVertices(i);
    for (int v : vertices) {
      matrix[i  * vertexesCount + v] += 1;
    }
  }
}

MatrixGraph::MatrixGraph(int k): matrix(std::vector<int>(k * k)), vertexesCount(k) {
  matrix.assign(k * k, 0);
}

void MatrixGraph::AddEdge(int from, int to) {
  matrix[from * vertexesCount + to] += 1;
}

int MatrixGraph::VerticesCount() const {
  return vertexesCount;
}

std::vector<int> MatrixGraph::GetNextVertices(int vertex) const {
  std::vector<int> result;
  for (int k = 0; k < vertexesCount; ++k) {
    if (matrix[vertexesCount * vertex + k] != 0) {
      result.push_back(k);
    }
  }
  return result;
}

std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const {
  std::vector<int> result;
  for (int k = 0; k < vertexesCount; ++k) {
    if (matrix[vertexesCount * k + vertex] != 0) {
      result.push_back(k); 
    }
  }
  return result;
}
