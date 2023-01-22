#include <cstddef>
#include <cstdint>
#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

class Graph {
private:
  vector<vector<int>> adjList;
public:
  Graph(size_t size) : adjList(size) {};
  void addEdge(int from, int to);
  int getVerticesCount() const;
  vector<int> getNextVertices(int vertex) const;
};

void Graph::addEdge(int from, int to) {
  adjList[from].push_back(to);
  adjList[to].push_back(from);
}

vector<int> Graph::getNextVertices(int vertex) const {
  return adjList[vertex];
}

int Graph::getVerticesCount() const {
  return adjList.size();
}

int BFS(const Graph& graph, int from, int to) {
  vector<int> minRouts;
  vector<int> minRoutsCount;
  minRoutsCount.assign(graph.getVerticesCount(), 0);
  minRouts.assign(graph.getVerticesCount(), INT32_MAX);
  minRoutsCount[from] = 1;
  minRouts[from] = 0;
  queue<int> q;
  q.push( from );

  while( !q.empty() ) {
    int v = q.front();
    q.pop();
    for( int w: graph.getNextVertices(v)) {
      if( minRouts[w] > minRouts[v] + 1 ) {
        minRouts[w] = minRouts[v] + 1;
        minRoutsCount[w] = minRoutsCount[v];
        q.push( w );
      } else if (minRouts[v] + 1 == minRouts[w]) {
        minRoutsCount[w] += minRoutsCount[v];
      }
    }
  }
  return minRoutsCount[to];
}

int main (int argc, char *argv[]) {
  size_t n = 0;
  size_t m = 0;
  int v1 = 0;
  int v2 = 0;
  std::cin >> n >> m;
  Graph graph(n);
  for (int i = 0; i < m; ++i) {
    std::cin >> v1 >> v2;
    graph.addEdge(v1, v2);
  }
  std::cin >> v1 >> v2;
  std::cout << BFS(graph, v1, v2) << std::endl; 
  return 0;
}
