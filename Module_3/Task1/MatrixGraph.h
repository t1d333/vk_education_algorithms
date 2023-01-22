#pragma once
#include "IGraph.h"
#include "vector"



class MatrixGraph: public IGraph {
public:
  MatrixGraph(int k);

  MatrixGraph(const IGraph& other);

  virtual void AddEdge(int from, int to) override;

  virtual int VerticesCount() const override;

  virtual std::vector<int> GetNextVertices(int vertex) const override;
  virtual std::vector<int> GetPrevVertices(int vertex) const override;

private:
  int vertexesCount;
  std::vector<int> matrix;
};
