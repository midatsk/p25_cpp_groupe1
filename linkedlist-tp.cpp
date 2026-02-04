#include <iostream>

struct Cell
{
    int donnee;
    Cell *next;

    Cell(int donnee) : donnee(donnee), next(nullptr) {}
};

struct LinkedList
{
    Cell *head;

    LinkedList() : head(nullptr) {}

    ~LinkedList()
    {
        // Parcours des cellules que l'on supprime au fur et à mesure
        while (head != nullptr)
        {
            Cell *temp = head;
            head = head->next; // On désigne la nouvelle tête de liste
            delete temp; // On supprime la cellule qui était head précédemment
        }
    }

    void push_front(int val)
    {
        Cell *new_cell = new Cell(val);
        new_cell->next = head;
        head = new_cell;
    }

    bool find(int valeur)
    {
        Cell *elem = head;
        while (elem != nullptr && elem->donnee != valeur)
        {
            elem = elem->next;
        }
        return elem != nullptr; 
    }

    Cell *find_elem(int valeur)
    {
        Cell *elem = head;
        while (elem != nullptr && elem->donnee != valeur)
        {
            elem = elem->next;
        }
        return elem;
    }

    void remove(int valeur)
    {
        // Disjonction de cas

        // Si la liste est vide
        if (head == nullptr)
            return;

        // Si l'élément à supprimer est le premier de la liste
        if (head->donnee == valeur)
        {
            Cell *temp = head;
            head = head->next; // On désigne la nouvelle tête
            delete temp; // Suppression de la cellule dans le tas
            return;
        }

        // Si l'élément à supprimer est au milieu de la liste, il faut accéder au pointeur de l'élément le précédant
        Cell *prev = head;
        // Parcours de liste jusqu'à trouver la cellule précédente
        while (prev->next != nullptr && prev->next->donnee != valeur)
        {
            prev = prev->next;
        }

        if (find(valeur)==false)
            return;

        Cell *to_del = prev->next; // On récupère le pointeur de l'élément à supprimer
        prev->next = to_del->next; 
        delete to_del;
    }

    void print()
    {
        Cell *elem = head;
        while (elem != nullptr)
        {
            std::cout << elem->donnee << " ";
            elem = elem->next;
        }
        std::cout << std::endl;
    }

    bool is_empty()
    {
        return head == nullptr;
    }
};



int main()
{
  LinkedList list;

  list.push_front(45);
  list.push_front(12);
  list.push_front(42);
  list.push_front(33);
  list.push_front(17);

  list.print(); // Affiche: 17 33 42 12 45
  //  oui l'ordre est inversé car on ajoute en tête de liste...

  list.remove(88); // Ne fait rien (et pas d'exception à générer)
  list.remove(17); // Attention on supprime la tête de liste !!
  list.remove(45); // Attention on supprime la queue de liste !!
  list.remove(42); // Supprime un élément du milieu de liste
  //  que de cas à gérer... que de pointeurs à mettre à jour...

  list.print();

  return 0;
}