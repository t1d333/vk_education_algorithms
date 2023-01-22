#pragma once
#include "IGraph.h"
#include <vector>

using std::vector;

class ArcGraph: public IGraph {
private:
  struct Edge {
    int from;
    int to;
    Edge(int from, int to): from(from), to(to) {}
  };

  vector<Edge> edges;
  int vertexCount;
public:
  ArcGraph(const IGraph& other);
  ArcGraph(int k);
  virtual void AddEdge(int from, int to) override;

  virtual int VerticesCount() const override;

  virtual std::vector<int> GetNextVertices(int vertex) const override;
  virtual std::vector<int> GetPrevVertices(int vertex) const  override;
};
