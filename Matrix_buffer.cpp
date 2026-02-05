#include <iostream>

class Buffer
{
    friend class Matrix;
    int size = 0;
    double *t;
    int cpt = 1;

public:
    Buffer(int s, double v = 0.0) : size(s)
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
    Matrix(int i, int j, double val = 0) : lignes(i), cols(j)
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

int main()
{

    Matrix m1(4, 3);
    m1.set(0, 0, 17.2);
    m1.print();

    {
        Matrix m2 = m1.reshape(2, 6);
        m2.set(1, 1, 2025);
        m2.print();
        m1.print();
    }
    Matrix m3 = m1.reshape(6, 2);
    m3.set(0, 0, 2026);

    Matrix m4(2, 4);
    Matrix m5(m4);

    Matrix m6(4, 6);
    Matrix m7(2, 3);
    m6 = m7;

    return 0;
}
