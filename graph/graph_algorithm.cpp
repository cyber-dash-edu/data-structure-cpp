//
// Created by cyberdash@163.com(抖音id:cyberdash_yuan) on 2021/2/4.
//

#include "graph_algorithm.h"
#include <iostream>


template<class T, class E>
void DFS(Graph<T, E>& graph, const T& vertex) {

  set<T> visited_vertex_set;

  DFSOnVertex(graph, vertex, visited_vertex_set);
}


template<class T, class E>
void DFSOnVertex(Graph<T, E>& graph, T vertex, set<T>& visited_vertex_set) {

  cout<<"Vertex: "<<vertex<<endl;

  visited_vertex_set.insert(vertex);

  T neighbor_vertex;
  bool done = graph.GetFirstNeighbor(neighbor_vertex, vertex);

  while (done == true) {
    if (visited_vertex_set.find(neighbor_vertex) == visited_vertex_set.end()) {
      DFSOnVertex(graph, neighbor_vertex, visited_vertex_set);
    }

    T next_neighbor_vertex;
    done = graph.GetNextNeighbor(next_neighbor_vertex, vertex, neighbor_vertex);
    neighbor_vertex = next_neighbor_vertex;
  }
}


template<class T, class E>
void BFS(Graph<T, E>& graph, const T& vertex) {

  set<T> visited_vertex_set;
  visited_vertex_set.insert(vertex);

  queue<T> vertex_queue;
  vertex_queue.push(vertex);

  cout<<"Vertex "<<vertex<<endl;

  while (!vertex_queue.empty()) {
    T front_vertex = vertex_queue.front();
    vertex_queue.pop();

    T neighbor_vertex;
    bool done = graph.GetFirstNeighbor(neighbor_vertex, vertex);

    while (done) {
      if (visited_vertex_set.find(neighbor_vertex) == visited_vertex_set.end()) {
        cout<<"Vertex "<<neighbor_vertex<<endl;

        visited_vertex_set.insert(neighbor_vertex);

        vertex_queue.push(neighbor_vertex);
      }

      T next_neighbor_vertex;
      done = graph.GetNextNeighbor(next_neighbor_vertex, vertex, neighbor_vertex);
      neighbor_vertex = next_neighbor_vertex;
    }
  }
}


template<class T, class E>
void Components(Graph<T, E>& graph) {

  int vertices_num = graph.NumberOfVertices();
  set<T> visited_vertex_set;

  int component_index = 1;

  for (int i = 0; i < vertices_num; i++) {
    T vertex;
    bool done = graph.GetVertexValue(vertex, i);

    if (done) {
      if (visited_vertex_set.find(vertex) == visited_vertex_set.end()) {
        cout<<"Component "<<component_index<<":"<<endl;
        DFSOnVertex(graph, vertex, visited_vertex_set);

        component_index++;
        cout<<endl;
      }
    }
  }
}


// todo
/*
template<class T, class E>
void Kruskal(Graph<T, E>& graph, MinSpanTree<T, E>& min_span_tree) {
}
 */


template<class T, class E>
void Prim(Graph<T, E>& graph, T vertex, MinSpanTree<T, E>& min_span_tree) {

  MSTEdgeNode<T, E> edge_node;

  int count = 1;
  int vertex_num = graph.NumberOfVertices();
  int edge_num = graph.NumberOfEdges();

  MinHeap<MSTEdgeNode<T, E> > min_heap(edge_num);

  set<T> vertex_set; // Vmst
  vertex_set.insert(vertex);

  do {
    T neighbor_vertex;
    bool done = graph.GetFirstNeighbor(neighbor_vertex, vertex);

    while (done) {
      if (vertex_set.find(neighbor_vertex) == vertex_set.end()) {

        edge_node.tail = vertex;
        edge_node.head = neighbor_vertex;
        graph.GetWeight(edge_node.weight_, vertex, neighbor_vertex);

        min_heap.Insert(edge_node);
      }

      T next_neighbor_vertex;
      done = graph.GetNextNeighbor(next_neighbor_vertex, vertex, neighbor_vertex);

      neighbor_vertex = next_neighbor_vertex;
    }

    while (min_heap.IsEmpty() == false && count < vertex_num) {

      min_heap.RemoveMin(edge_node);

      if (vertex_set.find(edge_node.head) == vertex_set.end()) {
        min_span_tree.Insert(edge_node);

        vertex = edge_node.head;
        vertex_set.insert(vertex);
        count++;

        break;
      }
    }
  } while (count < vertex_num);
}


template<class T, class E>
void ShortestPath(Graph<T, E>& graph, T vertex, E dist[], int path[]) {

  int vertex_num = graph.NumberOfVertices();

  set<T> vertex_set;

  for (int i = 0; i < vertex_num; i++) {
    T cur_vertex;
    graph.GetVertexValue(cur_vertex, i);

    bool get_weight_done = graph.GetWeight(dist[i], vertex, cur_vertex);

    if (cur_vertex != vertex && dist[i] < (E)MAX_WEIGHT && get_weight_done) {
      path[i] = graph.GetVertexIndex(vertex);
    } else {
      path[i] = -1;
    }
  }

  vertex_set.insert(vertex);
  dist[vertex] = 0;

  for (int i = 0; i < vertex_num - 1; i++) {
    E min = (E)MAX_WEIGHT;

    T src_vertex = vertex;
    for (int j = 0; j < vertex_num; j++) {
      T cur_vertex;
      graph.GetVertexValue(cur_vertex, j);
      if (vertex_set.find(cur_vertex) == vertex_set.end() && dist[cur_vertex] < min) {
        src_vertex = cur_vertex;
        min = dist[cur_vertex];
      }
    }

    vertex_set.insert(src_vertex);

    for (int j = 0; j < vertex_num; j++) {
      T cur_vertex;
      graph.GetVertexValue(cur_vertex, j);

      E weight;
      bool get_weight_done = graph.GetWeight(weight, src_vertex, cur_vertex);

      if (vertex_set.find(cur_vertex) == vertex_set.end()
        && weight < (E)MAX_WEIGHT
        && dist[src_vertex] + weight < dist[cur_vertex]
        && get_weight_done
        )
      {
        dist[cur_vertex] = dist[src_vertex] + weight;
        path[j] = graph.GetVertexIndex(src_vertex);
      }
    }
  }
}


template<class T, class E>
void PrintShortestPath(Graph<T, E>& graph, T vertex, E dist[], int path[]) {
  cout<<"从顶点"<<vertex<<"到其他各顶点的最短路径为: "<<endl;

  int vertex_num = graph.NumberOfVertices();
  int vertex_index = graph.GetVertexIndex(vertex);

  int* d = new int[vertex_num];

  for (int i = 0; i < vertex_num; i++) {
    if (i != vertex_index) {
      int j = i;
      int k = 0;

      while (j != vertex_index) {
        d[k++] = j;
        j = path[j];
      }

      T cur_vertex;
      graph.GetVertexValue(cur_vertex, i);
      cout<<"顶点"<<cur_vertex<<"的最短路径为:"<<vertex<<" ";
      while (k > 0) {
        graph.GetVertexValue(cur_vertex, d[--k]);
        cout<<cur_vertex<<" ";
      }

      cout<<"最短路径长度为:"<<dist[i]<<endl;
    }
  }

  delete[] d;
}


