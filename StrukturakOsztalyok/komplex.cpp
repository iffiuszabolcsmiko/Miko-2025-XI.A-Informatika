#include <iostream>
#include <cmath>

using namespace std;

class Komplex
{
     float real;
     float imag;
public:
    Komplex (float real = 0, float imag = 0)
    {
        this->real = real;
        this->imag = imag;
    }
    float modulusz() const
    {
        return sqrt(real * real + imag * imag);
    }
    Komplex konjugalt() const
    {
        return Komplex(real, -imag);
    }
    //operatorok komplex szammal
    Komplex operator+(const Komplex &x) const
    {
        return Komplex(this->real + x.real, this->imag + x.imag);
    }
    Komplex operator-(const Komplex &x) const
    {
        return Komplex(this->real - x.real, this->imag - x.imag);
    }
    Komplex operator*(const Komplex &x) const
    {
        return Komplex(this->real * x.real - this->imag * x.imag, this->real * x.imag + this->imag * x.real);
    }
    Komplex operator/(const Komplex &x) const
    {
        //return (*this) * x.konjugalt() / (x.real * x.real + x.imag * x.imag);
        float nevezo = x.real * x.real + x.imag * x.imag;

        return Komplex(
            (real * x.real + imag * x.imag) / nevezo,
            (imag * x.real - real * x.imag) / nevezo
        );
    }
    //operatorok valos szammal
    Komplex operator/(const float &x) const
    {
        return Komplex(this->real / x , this->imag / x);
    }
    Komplex operator*(const float &x) const
    {
        return Komplex(this->real * x , this->imag * x);
    }
    friend ostream& operator<<(ostream &out, const Komplex &c);
};

ostream& operator<<(ostream &out, const Komplex &c)
{
    if(c.imag < 0)
    {
        out << c.real << c.imag << "i";
    }
    else
    {
        out << c.real << "+" << c.imag << "i";
    }
    return out;
}

int main()
{
    Komplex c(5, 1), b(4, 3);
    float r = 3.5;
    cout << c << endl;
    cout << b << endl;
    cout << "Modulusz " << c << ": " << c.modulusz() << endl;
    cout << "Konjugalt " << c << ": " << c.konjugalt() << endl;
    cout << c << " + " << b << " = " << c + b << endl;
    cout << c << " - " << b << " = " << c - b << endl;
    cout << c << " * " << b << " = " << c * b << endl;
    cout << c << " / " << b << " = " << c / b << endl;
    cout << "Komplex es valos:" << endl;
    cout << c << " * " << r << " = " << c * r << endl;
    cout << c << " / " << r << " = " << c / r << endl;
    return 0;
}
