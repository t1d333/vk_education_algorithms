// g++ -o test.out ArcGraph.cpp ListGraph.cpp MatrixGraph.cpp SetGraph.cpp test.cpp

#include <algorithm>
#include <iostream>
#include <vector>

#include "ArcGraph.h"
#include "ListGraph.h"
#include "MatrixGraph.h"
#include "SetGraph.h"

using std::vector;

void fill(IGraph& graph) {

  for (size_t i = 2; i < 5; ++i) {
    graph.AddEdge(0, i);
  }

  for (size_t i = 0; i < 3; ++i) {
    graph.AddEdge(1, i);
  }

  for (size_t i = 6; i < 8; ++i) {
    graph.AddEdge(2, i);
  }

  for (size_t i = 1; i < 3; ++i) {
    graph.AddEdge(3, i);
  }

  for (size_t i = 7; i < 9; ++i) {
    graph.AddEdge(4, i);
  }

  for (size_t i = 0; i < 8; i += 2) {
    graph.AddEdge(5, i);
  }

  for (size_t i = 0; i < 8; i += 2) {
    graph.AddEdge(6, i);
  }

  for (size_t i = 0; i < 8; i += 3) {
    graph.AddEdge(7, i);
  }

  for (size_t i = 1; i < 8; i += 3) {
    graph.AddEdge(8, i);
  }

  for (size_t i = 0; i < 8; i += 5) {
    graph.AddEdge(9, i);
  }

}

void Test(IGraph& graph) {
  std::cout << "Checking vertices count..." << std::endl;
  if (graph.VerticesCount() != 10) {
    std::cout << "Failed!" << std::endl;
    std::cout << "Expected: 10. Got " << graph.VerticesCount() << std::endl;
    return;
  }
  std::cout << "OK" << std::endl;

  fill(graph); 
  std::cout << "Checking GetNextVertices..." << std::endl; 
  vector<int> test_data0 = graph.GetNextVertices(0); 
  vector<int> expected_data0{2, 3, 4};
  std::cout << "Checking vertex #0 ..." << std::endl; 
  for (int i = 0; i < 3; ++i) {
    if (test_data0[i] != expected_data0[i]) {
     std::cout << "Failed!" << std::endl;
     std::cout << "Expected: "  << expected_data0[i] << ". Got: " << test_data0[i] << std::endl;
    }
  }
  std::cout << "OK" << std::endl;
  vector<int> test_data5 = graph.GetNextVertices(0); 
  std::sort(test_data5.begin(), test_data5.end());
  vector<int> expected_data5{0, 2, 4, 6};
  std::cout << "Checking vertex #5 ..." << std::endl; 
  for (int i = 0; i < 4; ++i) {
    if (test_data0[i] != expected_data0[i]) {
     std::cout << "Failed!" << std::endl;
     std::cout << "Expected: "  << expected_data0[i] << ". Got: " << test_data0[i] << std::endl;
    }
  }
  std::cout << "OK" << std::endl;

  std::cout << "Checking GetPrevVertices..." << std::endl; 

  vector<int> test_data7 = graph.GetPrevVertices(7); 
  vector<int> expected_data7{2, 4, 5, 8};
  std::cout << "Checking vertex #7 ..." << std::endl; 
  for (int i = 0; i < 3; ++i) {
    if (test_data0[i] != expected_data0[i]) {
     std::cout << "Failed!" << std::endl;
     std::cout << "Expected: "  << expected_data0[i] << ". Got: " << test_data0[i] << std::endl;
    }
  }
  std::cout << "OK" << std::endl;

  vector<int> test_data6 = graph.GetNextVertices(6); 
  std::sort(test_data6.begin(), test_data6.end());
  vector<int> expected_data9{2, 5, };
  std::cout << "Checking vertex #6 ..." << std::endl; 
  for (int i = 0; i < 4; ++i) {
    if (test_data0[i] != expected_data0[i]) {
     std::cout << "Failed!" << std::endl;
     std::cout << "Expected: "  << expected_data0[i] << ". Got: " << test_data0[i] << std::endl;
    }
  }
  std::cout << "OK" << std::endl;

}

void TestListGraph() {
  std::cout << "Testing ListGraph" << std::endl;
  ListGraph graph(10);
  Test(graph);
}

void TestMatrixGraph() {
  std::cout << "Testing MatrixGraph" << std::endl;
  MatrixGraph graph(10);
  Test(graph);
}

void TestArcGraph() {
  std::cout << "Testing ArcGraph" << std::endl;
  ArcGraph graph(10);
  Test(graph);
}


void TestSetGraph() {
  std::cout << "Testing SetGraph" << std::endl;
  SetGraph graph(10);
  Test(graph);
}

int main() {
  TestListGraph();
  TestArcGraph();
  TestMatrixGraph();
  TestSetGraph();
}
