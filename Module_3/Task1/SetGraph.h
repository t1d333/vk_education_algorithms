#include "IGraph.h"
#include <set>
#include <vector>



class SetGraph : public IGraph {
  private:
    std::vector<std::set<int>> adjList;
    std::vector<std::set<int>> prevAdjList;
  public:

  SetGraph(int k);

  SetGraph(const IGraph& other);
  virtual void AddEdge(int from, int to) override;


  virtual int VerticesCount() const override;

  virtual std::vector<int> GetNextVertices(int vertex) const override;

  virtual std::vector<int> GetPrevVertices(int vertex) const override;
};
