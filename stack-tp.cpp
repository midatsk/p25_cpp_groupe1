#include <iostream>

// Nous allons implémenter une pile d'entiers de manière très basique.
// Nous la complexifierons par la suite.

// La pile est constituée:
//    - d'un tableau d'entier, avec sa taille et son nombre d'éléments empilés
//    - des quatre fonctions: push, pop, top, print, is_empty et is_full
//      (qui testent si la pile est resp. vide ou pleine)
//      il faut les utiliser dans votre code de push et pop

void print(int tab[], int size, int nb)
{
    for (int i = 0; i < nb; i++)
    {
        std::cout << tab[i] << "  " << std::endl;
    }
}

// renvoie true si la pile est vide, false sinon
bool is_empty(int tab[], int size, int &nb)
{
    if (nb == 0)
    {
        return true;
    }
    return false;
}

// renvoie true si la pile est pleine, false sinon
bool is_full(int tab[], int size, int &nb)
{
    if (nb == size)
    {
        return true;
    }
    return false;
}

void push(int tab[], int size, int &nb, int elem)
{
    try
    {
        if (is_full(tab, size, nb) == false)
        {
            tab[nb] = elem;
            nb++;
        }
        else
        {
            throw(is_full(tab, size, nb));
        }
    }
    catch (bool val)
    {
        std::cout << "Le tableau est plein" << std::endl;
    }
}

int top(int tab[], int size, int &nb) // (cette fonction ne dépile pas)
// cette fonction retourne l'entier en haut de la pile (le dernier empilé)
// à la sortie de cette fonction l'élément retourné reste dans la pile
// elle doit s'assurer que la pile n'est pas vide avant de la dépiler
// elle lance une exception si problème
{
    try
    {
        if (is_empty(tab, size, nb) == false)
        {
            return tab[nb];
        }
        else
        {
            throw(is_empty(tab, size, nb));
        }
    }
    catch (bool val)
    {
        std::cout << "Le tableau est vide" << std::endl;
    }
}

int pop(int tab[], int size, int &nb) // (cette fonction dépile)
// cette fonction retourne l'entier en haut de la pile (le dernier empilé)
// à la sortie de cette fonction l'élément retourné n'est plus compté dans la pile
// elle doit s'assurer que la pile n'est pas vide avant de la dépiler
// elle lance une exception si problème
{

    int tab_aux[size];
    try
    {
        if (is_empty(tab, size, nb) == false)
        {
            return tab[nb];
        }
        else{
            throw(is_empty(tab,size,nb));
        }
    }
    catch(bool val){
        std::cout<<"Le tableau est vide"<<std::endl;
    }

    for (int i = 0; i < nb - 1; i++)
    {
        tab_aux[i] = tab[i];
        int *ptab = tab;
        int *ptab_aux = tab_aux;
        ptab = ptab_aux;
        nb = nb - 1;
    }
}

#include <stdexcept>
    // https://en.cppreference.com/w/cpp/header/stdexcept.html
    // pour un exemple d'exception voir le fichier exception.cpp

    int main()
    {

        // on définit les 3 variables constituant la pile
        int size = 5;
        int stack[size];
        int nb = 0;

        // rajoutez aux blocks catch les erreurs
        // pouvant être déclenchées par les opérations sur la pile
        try
        {
            print(stack, size, nb); // affiche [ [
            push(stack, size, nb, -17);

            // on affiche l'élément en haut de pile
            std::cout << top(stack, size, nb) << std::endl; // affiche -17

            print(stack, size, nb); // affiche [-17 90 [

            int e = pop(stack, size, nb);
            std::cout << e << std::endl;
            print(stack, size, nb); // affiche [-17 [

            push(stack, size, nb, 20);
            push(stack, size, nb, -78);
            push(stack, size, nb, -9);
            push(stack, size, nb, -56);
            push(stack, size, nb, -9);
            push(stack, size, nb, 68);
        }
        catch (bool val)
        {
            std::cout<<"Le tableau est vide"<<std::endl;
        }
    }