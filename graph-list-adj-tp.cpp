#include <iostream>
#include <vector>


struct Vertex
{

    int indice;
    std::vector<Edge *> e;
    Vertex(int ind) : indice(ind)
    {
        for (int i = 0; i < e.size(); i++)
        {
            e[i] = new Edge;
        }
    }

    ~Vertex()
    {
        for (int i = 0; i < e.size(); i++)
        {
            delete e[i];
        }
    }
};

struct Edge
{
    double poids;
    Vertex *begin;
    Vertex *end;

    void print()
    {
        std::cout << begin->indice << "-" << (poids) << "->" << end->indice << std::endl;
    }
};
inline Vertex::Vertex(int ind) : indice(ind)
    {
        for (int i = 0; i < e.size(); i++)
        {
            e[i] = new Edge;
        }
    }

struct Graph
{
    std::vector<Vertex *> v;
    
    ~Graph()
    {
        for (int i = 0; i < v.size(); i++)
        {
            delete v[i];
        }
    }
    // Ajoute le sommet d'indice n
    void addVertex(int n)
    {
        for (int i=v.size(); i<=n; i++)
        {
            Vertex* new_vertex = new Vertex(i);
            v.push_back(new_vertex);
            new_vertex->indice = i;
        }
         
    }
    void addEdge(int i, int j, double weight)
    {
        addVertex(i);
        addVertex(j);
        Edge* edge = new Edge;
        edge->poids = weight;
        edge->begin = v[i] ;
        edge->end = v[j];
        (v[i]->e).push_back(edge);
        (v[j]->e).push_back(edge);
    }
};
