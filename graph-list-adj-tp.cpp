#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <unordered_map>
#include <set>
class Edge
{
    friend class Graph;
    double weight;  // poids de l'arête
    int src_index;  // indice du sommet de départ
    int dest_index; // indice du sommet d'arrivée

    Edge() {} // constructeur par défaut

    Edge(int weight, int src_index, int dest_index) : weight(weight), src_index(src_index), dest_index(dest_index) {} // constructeur avec arguments
};
class Vertex
{
    friend class Graph;
    std::string name;          // nom du sommet
    int index;                 // indice du sommet
    std::vector<Edge *> edges; // vecteur des arêtes dont il est le départ

    Vertex() : name(""), index(0) {} // constructeur par défaut

    ~Vertex()
    {
        for (int i = 0; i < edges.size(); i++)
        {
            delete edges[i];
        }
    }

public:
    Vertex(std::string name, int index) : name(name), index(index) {} // constructeur avec arguments
};

class Graph
{

    std::unordered_map<std::string, int> name_to_index; // Dictionnaire pour garder la correspondance entre le nom et l'indice du sommet
    public:
    std::vector<Vertex *> vertices; // vecteur des sommets du graphe

    ~Graph()
    {
        for (int i = 0; i < vertices.size(); i++)
        {
            delete vertices[i];
        }
    }

    bool vertex_in_graph(int v_index)
    {
        for (int i = 0; i < vertices.size(); i++)
        {
            if (vertices[i]->index == v_index)
            {
                return true;
            }
        }
        return false;
    }

    void addVertex(const std::string &name, int index)
    {
        if (vertex_in_graph(index) == true)
        {
            std::cout << "Le sommet " << name << " existe déjà" << std::endl;
        }
        else
        {
            vertices.push_back(new Vertex(name, index));
            name_to_index[name] = index ; // Mise à jour du dictionnaire
            std::cout << "Sommet " << name <<" ajouté avec succès"<< std::endl;
        }
    }

    Vertex *getVertex_by_ind(int id)
    {
        for (int i = 0; i < vertices.size(); i++)
        {
            if (vertices[i]->index == id)
            {
                return vertices[i];
            }
        }
        return nullptr;
    }

    Vertex* getVertex_by_name(const std::string& name)
    {
    auto it = name_to_index.find(name);
    if (it == name_to_index.end())
        return nullptr;

    return getVertex_by_ind(it->second);
    }

    bool edge_in_graph(int id1, int id2) // vérifie si l'arête existe déjà ou non
    {
        Vertex *v1 = getVertex_by_ind(id1);  
        std::vector<Edge*> edges1 = v1->edges; 
        Vertex *v2 = getVertex_by_ind(id2);  
        std::vector<Edge*> edges2 = v2->edges; 

        if (v1 == nullptr || v2 == nullptr) // Si un des deux sommets n'existe pas
        {
            return false;
        }

        for (int i = 0; i < edges1.size(); i++) // test d'existence pour une arête orientée id1 -> id2
        {
            if (edges1[i]->dest_index == id2)
            {
                return true;
            }
        }

        for (int i = 0; i < edges2.size(); i++) // test d'existence pour une arête orientée id2 -> id1
        {
            if (edges2[i]->dest_index == id1)
            {
                return true;
            }
        }

        return false;
    }

    void add_edge(int id1, int id2, double w) // crée un sommet orienté id1 -> id2
    {
        bool check1 = vertex_in_graph(id1);
        bool check2 = vertex_in_graph(id2);

        Vertex* v1 = getVertex_by_ind(id1);

        if ((check1 && check2) == true)
        {
            bool check3 = edge_in_graph(id1, id2);
            if (check3 == true)
            {
                std::cout << "L'arête existe déjà" << std::endl;
            }
            else
            {
                
                v1->edges.push_back(new Edge(w, id1, id2));
                std::cout << "Arête ajoutée avec succès" << std::endl;
            }
        }
        else
        {
            std::cout << "Un des sommets n'existe pas" << std::endl;
        }
    }

public:
    void add_edge(const std::string &begin, const std::string &end, double value)
    {
        auto it1 = name_to_index.find(begin);
        auto it2 = name_to_index.find(end);

    if (it1 == name_to_index.end() || it2 == name_to_index.end())
    {
        std::cout << "Un des sommets n'existe pas"<< std::endl;
        return;
    }

    add_edge(it1->second, it2->second, value);
    }
    
    void dfs() {}


};

int main()
{

    Graph g;
    g.add_edge(0, 1, 500);
    g.addVertex("Truc", 0);
    g.addVertex("Muche", 1);
    g.add_edge("Truc", "Muche", 500);
    g.add_edge("Truc", "Muche", 500);

    return 0;
}