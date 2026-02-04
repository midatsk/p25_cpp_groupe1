#include <iostream>
#include <stdexcept>

// renvoie true si la pile est vide
bool is_empty(int tab[], int size, int &nb)
{
    return nb == 0;
}

// renvoie true si la pile est pleine
bool is_full(int tab[], int size, int &nb)
{
    return nb == size;
}

void print(int tab[], int size, int &nb)
{
    std::cout << "[ ";
    for (int i = 0; i < nb; i++)
    {
        std::cout << tab[i] << " ";
    }
    std::cout << "]" << std::endl;
}

void push(int tab[], int size, int &nb, int elem)
{
    if (is_full(tab, size, nb))
    {
        throw std::runtime_error("Pile pleine");
    }

    tab[nb] = elem;
    nb++;
}

int top(int tab[], int size, int &nb)
{
    if (is_empty(tab, size, nb))
    {
        throw std::runtime_error("Pile vide");
    }

    return tab[nb - 1];
}

int pop(int tab[], int size, int &nb)
{
    if (is_empty(tab, size, nb))
    {
        throw std::runtime_error("Pile vide");
    }

    nb--;
    return tab[nb];
}

int main()
{
    int size = 5;
    int stack[size];
    int nb = 0;

    print(stack, size, nb);

    push(stack, size, nb, -17);
    std::cout << top(stack, size, nb) << std::endl;

    push(stack, size, nb, 90);
    print(stack, size, nb);

    try
    {
        int e = pop(stack, size, nb);
        std::cout << e << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    try
    {
        push(stack, size, nb, 20);
        push(stack, size, nb, -78);
        push(stack, size, nb, -9);
        push(stack, size, nb, -56);
        push(stack, size, nb, 68); // déclenche exception
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    print(stack, size, nb);
}
