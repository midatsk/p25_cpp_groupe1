#include <iostream>



struct IntStack
{

int size; //taille de la pile
int nb; //nombre d'éléments dans le tableau.  
int* tab;  //pointeur vers le tableau créé dans le heap


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
    std::cout << "[ ";
    for (int i = 0; i < nb; i++)
    {
        std::cout << tab[i] << " ";
    }
    std::cout << "]" << std::endl;
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
    if (is_full())
    {
        throw std::runtime_error("Pile pleine");
    }

    tab[nb] = e;
    nb++;
}

int top()
{
    if (is_empty())
    {
        throw std::runtime_error("Pile vide");
    }

    return tab[nb - 1];
}

int pop()
{
    if (is_empty())
    {
        throw std::runtime_error("Pile vide");
    }
    nb--;
    return tab[nb];

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