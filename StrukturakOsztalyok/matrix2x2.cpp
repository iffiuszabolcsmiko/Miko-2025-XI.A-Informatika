#include <bits/stdc++.h>
using namespace std;

class Matrix
{
    float a, b, c, d;

public:
    //konstructor
    Matrix (float a, float b, float c, float d)
    {
        this->a = a;
        this->b = b;
        this->c = c;
        this->d = d;
    }
    void kiir()
    {
        cout << "| " << a << " " << b << " |" << endl;
        cout << "| " << c << " " << d << " |" << endl;
    }
    float determinans()
    {
        return a * d - c * b;
    }
    Matrix transzponalt()
    {
        return Matrix(a, c, b, d);
    }
    Matrix operator+(const Matrix &B)
    {
        return Matrix(a + B.a, b + B.b, c+ B.c, d + B.d);
    }
    Matrix operator-(const Matrix &B)
    {
        return Matrix(a - B.a, b - B.b, c - B.c, d - B.d);
    }
    Matrix operator*(const float &s)
    {
        return Matrix(a * s, b * s, c * s, d * s);
    }
    Matrix operator/(const float &s)
    {
        return Matrix(a / s, b / s, c / s, d / s);
    }
    Matrix operator*(const Matrix &M)
    {
        return Matrix(a * M.a + b * M.c, a * M.b + b * M.d,
                      c * M.a + d * M.c, c * M.b + d * M.d );
    }
    friend ostream& operator<<(ostream &out, const Matrix &m);
};

ostream& operator<<(ostream &out, const Matrix &m)
{
    out << "| " << m.a << " " << m.b << " |" << endl;
    out << "| " << m.c << " " << m.d << " |" << endl;
    return out;
}

int main()
{
    Matrix A(1, 5, 6, 9);
    Matrix B(1, 8, 3, 7);
    cout << "A:" << endl << A;
    cout << "B:" << endl << B;
    cout << "Determinans A " << A.determinans() << endl;
    cout << "Transzponalt A " << endl << A.transzponalt();
    cout << "A + B = " << endl << A + B;
    cout << "A - B = " << endl << A - B;
    float s = 2;
    cout << s << " * A =" << endl << A * s;
    cout << "A * B = " << endl << A * B;
    return 0;
}
