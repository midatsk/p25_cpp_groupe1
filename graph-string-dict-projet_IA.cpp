#include "graph_IA.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <stdexcept>

using namespace std;

static const double INF = numeric_limits<double>::infinity();

//////////////////// EDGE ////////////////////

Edge::Edge(double w, int s, int d)
    : weight(w), src_index(s), dest_index(d) {}

//////////////////// VERTEX ////////////////////

Vertex::Vertex(const string& name, int index)
    : name(name), index(index) {}

Vertex::~Vertex()
{
    for (Edge* e : edges)
        delete e;
}

//////////////////// MATRIX ////////////////////

Matrix::Matrix(int n)
{
    data.resize(n, vector<double>(n, INF)); // Je ne connais pas la méthode resize pour les vecteurs 
    // Explication IA : La méthode resize de std::vector permet de modifier dynamiquement la taille logique du vecteur.
    // Elle ne change pas nécessairement la capacité (capacity()), mais elle change le nombre d’éléments accessibles (size()).

    for (int i = 0; i < n; ++i)
        data[i][i] = 0.0;
}

int Matrix::size() const
{
    return data.size();
}

//////////////////// GRAPH ////////////////////

Graph::Graph() : adjacency_matrix(nullptr) {}

Graph::~Graph()
{
    for (Vertex* v : vertices)
        delete v;

    delete adjacency_matrix;
}

Vertex* Graph::get_vertex_by_index(int index) const
{
    return vertices[index];
}

int Graph::get_or_create_vertex(const string& name)
{
    auto it = name_to_index.find(name);
    if (it != name_to_index.end())
        return it->second;

    int new_index = vertices.size();
    Vertex* v = new Vertex(name, new_index);

    vertices.push_back(v);
    name_to_index[name] = new_index;

    return new_index;
}

void Graph::add_edge(const string& from,
                     const string& to,
                     double weight)
{
    int src = get_or_create_vertex(from);
    int dst = get_or_create_vertex(to);

    Vertex* v = get_vertex_by_index(src);

    Edge* e = new Edge(weight, src, dst);
    v->edges.push_back(e);
}

//////////////////// READ FILE ////////////////////

void Graph::read_from_file(const string& filename)
{
    ifstream file(filename);
    if (!file)
        throw runtime_error("Cannot open file");

    string from, to;
    double weight;

    while (file >> from >> to >> weight)
        add_edge(from, to, weight);

    file.close();
}

//////////////////// DFS ////////////////////

void Graph::dfs_rec(Vertex* v, set<int>& visited)
{
    if (!v || visited.count(v->index)) // Je ne connais pas la syntaxe !v. Explication IA : ! est l’opérateur logique NOT. 
                                        // Dans le cadre d'un pointeur, permet de tester s'il est nullptr. 
        return;

    visited.insert(v->index);
    cout << v->name << " ";

    for (Edge* e : v->edges)
        dfs_rec(get_vertex_by_index(e->dest_index), visited);
}

void Graph::dfs()
{
    set<int> visited;

    for (Vertex* v : vertices)
        if (!visited.count(v->index))
            dfs_rec(v, visited);

    cout << endl;
}

//////////////////// ADJ MATRIX ////////////////////

void Graph::build_adjacency_matrix()
{
    delete adjacency_matrix;

    int n = vertices.size();
    adjacency_matrix = new Matrix(n);

    for (Vertex* v : vertices)
    {
        for (Edge* e : v->edges)
        {
            adjacency_matrix->data[e->src_index][e->dest_index] = e->weight;
        }
    }
}

//////////////////// FLOYD WARSHALL ////////////////////

void Graph::floyd_warshall()
{
    if (!adjacency_matrix)
        build_adjacency_matrix();

    int n = adjacency_matrix->size();

    for (int k = 0; k < n; ++k)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                double through_k =
                    adjacency_matrix->data[i][k] +
                    adjacency_matrix->data[k][j];

                if (through_k < adjacency_matrix->data[i][j])
                {
                    adjacency_matrix->data[i][j] = through_k;
                }
            }
        }
    }
}
