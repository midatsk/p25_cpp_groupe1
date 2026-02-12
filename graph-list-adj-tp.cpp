#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <unordered_map>
#include <set>
#include "Matrix_buffer_2.h"

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

    int get_or_create_vertex(const std::string& name) // Fonction auxiliaire pour la fonction read_triplet
{
    // On recherche dans le dictionnaire du graph l'indice correspondant au nom name
    auto it = name_to_index.find(name);
    // Si l'objet existe déjà, alors on renvoie l'indice qui lui est déjà attribué
    if (it != name_to_index.end())
    {
        return it->second;
    }
    // Sinon, on crée le sommet et il aura l'indice de la taille du 
    int new_index = vertices.size();
    addVertex(name, new_index);
    return new_index;
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
    
    void dfs_rec(Vertex* vertex, std::set<int>&visited)
    {
        // Cas de base : si vertex est le pointeur null ou s'il a déjà été visité
        if (vertex == nullptr || visited.count(vertex->index)==1)
        {
            return ; 
        }
        else
        {
            // On marque le sommet comme visité
            visited.insert(vertex->index);
            std::cout << vertex-> name << " ";
            
            // On lance le parcours récursif de ses voisins
            for (int i = 0; i < vertex->edges.size(); ++i)
        {   
            Edge* e = vertex->edges[i];
            Vertex* next = getVertex_by_ind(e->dest_index);
            dfs_rec(next, visited);
        }


        }
    }

    void dfs()
    {
        std::set<int> visited; // set pour stocker les indices des sommets déjà visités

        for (int i = 0; i < vertices.size(); i++)
        {
            if (visited.count(vertices[i]->index) == 0)
            {
                dfs_rec(vertices[i], visited);
            }
        }
    }

    Matrix adj_mat()
    {
        int n = vertices.size();
        Matrix M = Matrix(n,n); // La matrice est initialisée avec des infinity
        for (Vertex * v : vertices)
        {
            int i = v->index;
            for (Edge* e : v->edges)
            {
                int j = e->dest_index;
                M.set(i,j,e->weight);
            }
        }
        return M ; 
    }


};

Graph read_triplet(const std::string &filename)
{
    Graph g;
    std::cout << "read_triplet(" << filename << ")" << std::endl;

    
    std::ifstream file(filename);

    if (not file.is_open())
    {
        throw std::runtime_error(std::string("file ") + filename + std::string(" not found"));
    }

    std::string from, to;
    double value;

    while (file >> from >> to >> value) 
    {
        std::cout << from << " " << to << " " << value << std::endl;
        // Il faut pouvoir construire le graphe, c'est-à-dire créer d'abord les sommets, 
        // sans créer de doublons lorsque plusieurs arêtes partant d'un sommet sont créées
        // La fonction addVertex a besoin non seulement de la string du sommet, mais aussi de connaître son indice
        // Pour ne pas gérer des indices dans la fonction read_triplet, on crée une fonction auxiliaire dans la classe Graph 
        // qui permet de régler le problème de l'index à chercher pour les sommets
        
        
        int from_id = g.get_or_create_vertex(from);
        int to_id   = g.get_or_create_vertex(to);

        g.add_edge(from_id, to_id, value);

    }
    std::cout << std::endl;

    file.close(); // on ferme le fichier

    return g;
}

int main()
{

    Graph g = read_triplet("graph0.gr");

    g.dfs();

    g.adj_mat().print();

    return 0;
}