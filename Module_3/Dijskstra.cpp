/*
Требуется отыскать самый выгодный маршрут между городами. 
Требования: время работы O((N+M)logN), где N-количество городов, M-известных дорог между ними.
*/
#include <cstdint>
#include <iostream>
#include <cstddef>
#include <utility>
#include <vector>
#include <set>

using std::vector;

class Graph {
private:
  vector<vector<std::pair<int, int>>> adjList;
public:
  Graph(size_t size) : adjList(size) {};
  void addEdge(int from, int to, int weight);
  int getVerticesCount() const;
  vector<std::pair<int, int>> getNextVertices(int vertex) const;
};

void Graph::addEdge(int from, int to, int weight) {
  adjList[from].push_back(std::pair<int, int>(weight, to));
  adjList[to].push_back(std::pair<int, int>(weight, from));
}

vector<std::pair<int, int>> Graph::getNextVertices(int vertex) const {
  return adjList[vertex];
}

int Graph::getVerticesCount() const {
  return adjList.size();
}

bool Relax(std::pair<int, int> u, std::pair<int, int> v, std::vector<int>& distances, std::set<std::pair<int, int>>& q) {
  if (distances[v.second] > distances[u.second] + v.first) {
    q.erase(std::pair<int, int>(distances[v.second], v.second));
    distances[v.second] = distances[u.second] + v.first; 
    return true;
  }
  return false;
} 

int Dijsktra(Graph graph, int from, int to) {
  std::vector<int> distances;
  distances.assign(graph.getVerticesCount(), INT32_MAX);
  distances[from] = 0;
  std::set<std::pair<int, int>> priority_queue;
  priority_queue.insert(std::pair<int, int>(0, from));
  while (priority_queue.size() != 0) {
    std::set<std::pair<int, int>>::iterator it = priority_queue.begin();
    std::pair<int, int> u = *it;
    priority_queue.erase(it);
    for (std::pair<int, int> v : graph.getNextVertices(u.second)) {
      if (distances[v.second] == INT32_MAX) {
        distances[v.second] = distances[u.second] + v.first;
        priority_queue.insert(std::pair<int, int>(distances[v.second], v.second));
      } else if (Relax(u, v, distances, priority_queue)) {
        priority_queue.insert(std::pair<int, int>(distances[v.second], v.second));
      }
    }
  }
  return distances[to];
}

int main (int argc, char *argv[]) {
  size_t n = 0;
  size_t m = 0;
  int v1 = 0;
  int v2 = 0;
  int w = 0;
  std::cin >> n >> m;
  Graph graph(n);
  for (int i = 0; i < m; ++i) {
    std::cin >> v1 >> v2 >> w;
    graph.addEdge(v1, v2, w);
  }
  std::cin >> v1 >> v2;
  std::cout << Dijsktra(graph, v1, v2) << std::endl;
  return 0;
}
