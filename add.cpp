#include <iostream>
#include <cstdlib>



int main(int argc, char* argv[])
{

    
    int somme = 0;
    for (int i = 0; i < argc; i++)
    {
        int num = std::atoi(argv[i]);
        somme = somme + num ;
        
    }
    std::cout << "Résultat " << somme << std::endl;
    
    return 0;
}
