#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <unordered_map>
#include <set>

class Graph;

class Edge
{
    friend class Graph;

    double weight;
    int src_index;
    int dest_index;

    Edge(double w, int s, int d);
};

class Vertex
{
    friend class Graph;

    std::string name;
    int index;
    std::vector<Edge*> edges;

    Vertex(const std::string& name, int index);
    ~Vertex();
};

class Matrix
{
    friend class Graph;

    std::vector<std::vector<double>> data;

    Matrix(int n);
    int size() const;
};

class Graph
{
private:
    std::vector<Vertex*> vertices;
    std::unordered_map<std::string,int> name_to_index;

    Matrix* adjacency_matrix;

    int get_or_create_vertex(const std::string& name);
    Vertex* get_vertex_by_index(int index) const;

    void dfs_rec(Vertex* v, std::set<int>& visited);

public:
    Graph();
    ~Graph();

    void read_from_file(const std::string& filename);
    void add_edge(const std::string& from,
                  const std::string& to,
                  double weight);

    void dfs();

    void build_adjacency_matrix();
    void floyd_warshall();
};

#endif
