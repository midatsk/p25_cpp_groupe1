#include <iostream>

class Buffer
{
    friend class Matrix;
private:
    
    int size = 0;
    double *t;
    int cpt = 1;

public:
    Buffer(int s, double v = 0) : size(s)
    {
        t = new double[size];
        for (int i = 0; i < size; i++)
        {
            t[i] = v;
        }
    }

    ~Buffer()
    {
        delete[] t;
    }

    void set(int h, double val)
    {
        t[h] = val;
    }
    double get(int h)
    {
        return t[h];
    }
};

class Matrix
{
    int lignes = 0;
    int cols = 0;
    Buffer *pbuf;

    int flatten_index(int i, int j)
    {
        return (i * cols + j);
    }

public:
    Matrix(int i, int j, double val = std::numeric_limits<double>::infinity()) : lignes(i), cols(j)
    {
        if (i * j == 0)
        {
            pbuf = nullptr;
        }
        else
        {
            pbuf = new Buffer(i * j, val);
        }
    }

    Matrix(int i, int j, Buffer *b) : lignes(i), cols(j), pbuf(b)
    {
        b->cpt = b->cpt + 1;
    }

    void set(int i, int j, double val)
    {
        pbuf->set(flatten_index(i, j), val);
    }

    double get(int i, int j)
    {
        return pbuf->get(flatten_index(i, j));
    }

    void print()
    {
        for (int i = 0; i < lignes; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                std::cout << get(i, j) << " ";
            }
            std::cout << " " << std::endl;
        }
        std::cout << " " << std::endl;
    }

    Matrix reshape(int l, int c)
    {
        pbuf->cpt += 1;
        Matrix h(0, 0);
        h.cols = c;
        h.lignes = l;
        h.pbuf = pbuf;
        return h;
    }

    Matrix operator+(Matrix &B)
    {
        Matrix Sum(lignes, cols);
        for (int h = 0; h < lignes * cols; h++)
        {
            (Sum.pbuf->t)[h] = (pbuf->t)[h] + (B.pbuf->t)[h];
        }
        return Sum;
    }

    Matrix operator*(double l)
    {
        Matrix Prod(lignes, cols);
        for (int h = 0; h < lignes * cols; h++)
        {
            (Prod.pbuf->t)[h] = l * (pbuf->t)[h];
        }
        return Prod;
    }

    ~Matrix()
    {
        pbuf->cpt -= 1;
        if (pbuf->cpt == 0)
        {
            delete pbuf;
        }
    }
};


