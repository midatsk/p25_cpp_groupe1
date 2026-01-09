#include <iostream>

//Je travaille sans exceptions pour l'instant

struct IntStack
{

int size; //taille de la pile
int nb; //nombre d'éléments dans le tableau. Est-ce qu'il y a besoin d'utiliser une référence dans ce cas-là ? 
int* tab;  //pointeur vers le tableau 

IntStack(int size) : size(size), nb(0)
{
    tab = new int [size];
}

IntStack(const IntStack &src) : size(src.size), nb(src.nb) 
{
    //Allocation de mémoire pour la nouvelle stack
    tab = new int [size]; 

    //Copie des éléments de la stack source

    for (int i = 0; i<nb; i++)
    {
        tab[i] = (src.tab)[i];
    }

}

~IntStack()
{
    delete[] tab;
}

IntStack& operator=(const IntStack& src)
{
    if(this != &src)
    {
        size = src.size;
        nb = src.nb;
        delete [] tab;
        tab = new int [size];
        for (int i = 0; i<nb; i++)
        {
            tab[i]=src.tab[i];
        }
    }
    return *this;
}

void print()
{
    for (int i=0; i<size; i++)
    {
        std::cout << tab[i] <<" "<< std::endl;
    }
}

bool is_empty()
{
    return (nb<=0);
}

bool is_full()
{
    return (nb == size);
}

void push(int e)
{
    if (is_full() == false) 
    {
        tab[nb] = e;
        nb++ ; 
    }
}

int top()
{
    if (is_empty() == false)
    {
        return tab[nb];
    }
}

int pop()
{
    if (is_empty()==false)
    {
        return tab[nb];
    }
    int* tab_aux = new int [size];

    for (int i = 0; i<nb-1;i++)
    {
        tab_aux[i]=tab[i];
        tab = tab_aux;
    }
    nb = nb-1 ;

}

};

int main()
{

IntStack stack(5);

stack.push(1);
stack.push(2);
stack.push(3);
stack.push(4);
stack.push(5);

stack.print();

IntStack stack2(stack);

stack2.print();

IntStack stack3(7);
stack3.push(-17);
stack3.push(20);
stack3.push(0);
stack3.push(0);
stack3.push(0);
stack3.push(0);
stack3.push(0);

stack2 = stack3;

stack2.print();

return 0;
}