#pragma once
#include "IGraph.h"
#include <vector>



class ListGraph : public IGraph {
  private:
    std::vector<std::vector<int>> adjList;
    std::vector<std::vector<int>> prevAdjList;
  public:
  ListGraph(int k);
  ListGraph(const IGraph& other);
  virtual void AddEdge(int from, int to) override;

  virtual int VerticesCount() const  override;

  virtual std::vector<int> GetNextVertices(int vertex) const override;
  virtual std::vector<int> GetPrevVertices(int vertex) const override;
};
