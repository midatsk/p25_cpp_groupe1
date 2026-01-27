/*

implement a hierarchy of classes for arithmetic expression manipulations:
    - the classes holds, evaluates and prints arithmetic expressions
    - print in infix, prefix or postfix notation

Additional work:
   - note that the postfix notation is also called Reverse Polish notation (RPN)
   - it is a mathematical notation in which operators follow their operands
   - this notation does not need any parentheses i.e. this notation is non ambigu
   - => you can read (easily) RPN expressions using a stacks
  implement a code to read RPN expression and store them with your class objects
  RPN arithmetic expression are passed as main command-line arguments

./main 87 12 - + 75 -
*/

#include <iostream>
#include <vector>

class Expression
{
public:
 virtual void print()=0;
 virtual double eval()=0;

};

class Constant : public Expression
{

    int valeur;
public:
    
    Constant(int i) : valeur(i){}

    void print()
    {
        std::cout<<" "<<valeur<<std::endl;
    }
git
    }
};

class UnaryMinus : public Expression
{
    
    Expression& expr;
    public:
    UnaryMinus(Expression& expr) : expr(expr){}

    void print()
    {
        expr.print();
        std::cout <<" -"<< std::endl;
    }

    double eval()
    {
        return -expr.eval();
    }



};

class Plus : public Expression
{

    Expression& expr1;
    Expression& expr2;
    public:
    Plus(Expression& expr1, Expression& expr2): expr1(expr1), expr2(expr2){}

    void print()
    {
        expr1.print();
        std::cout<<" "<<std::endl;
        expr2.print();
        std::cout<<" +"<<std::endl;
    }

    double eval()
    {
        return expr1.eval() + expr2.eval();
    }

};

class Minus : public Expression
{
    Expression& expr1;
    Expression& expr2;
    public:
    Minus(Expression& expr1, Expression& expr2): expr1(expr1), expr2(expr2){}

    void print()
    {
        expr1.print();
        std::cout<<" "<<std::endl;
        expr2.print();
        std::cout<<" -"<<std::endl;
    }

    double eval()
    {
        return expr1.eval() - expr2.eval();
    }
};

class Divide : public Expression
{
    Expression& expr1;
    Expression& expr2;
    public:
    Divide(Expression& expr1, Expression& expr2): expr1(expr1), expr2(expr2){}

    void print()
    {
        expr1.print();
        std::cout<<" "<<std::endl;
        expr2.print();
        std::cout<<" ÷"<<std::endl;
    }

    double eval()
    {
        if(expr2.eval()==0)
        {
            throw std::invalid_argument(std::string("Division par 0 "));
        }
        else return expr1.eval()/expr2.eval();
    }
};


int main()
{
    try
    {
        // Constant c1(12), c2(-87), c3(23); // try it (-87 is not an unsigned int)
        Constant c1(12), c2(87), c3(75);

        c1.print(); // affiche 12
        std::cout << std::endl;
        std::cout << "eval " << c1.eval() << std::endl; // affiche 12

        UnaryMinus u1(c1);
        u1.print(); // affiche 12 -
        std::cout << std::endl;
        std::cout << "eval " << u1.eval() << std::endl; // affiche -12

        Plus p1(c2, u1);
        p1.print(); // affiche 87 12 -+
        std::cout << std::endl;
        std::cout << "eval " << p1.eval() << std::endl; // affiche 75

        Minus m1(p1, c3);
        m1.print(); // 87 12 -+75 -
        std::cout << std::endl;
        std::cout << "eval " << m1.eval() << std::endl; // affiche 0

        Divide d1(p1, m1);
        std::cout << std::endl;
        std::cout << d1.eval() << std::endl; // throws an instance of 'std::runtime_error'

        // std::vector<Expression&> expr;
        // expr.push_back(c1);
        // expr.push_back(u1);
        // parcourez le vecteur
        //Le code ne compile pas quand j'essaie de faire les lignes en commentaire juste au-dessus. 

    }
    catch (std::runtime_error &e)
    {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
