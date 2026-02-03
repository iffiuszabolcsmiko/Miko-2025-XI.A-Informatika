#include <iostream>
#include <cmath>

using namespace std;

class Vektor
{
    float x;
    float y;
public:

    Vektor(float x, float y)
    {
        this -> x = x;
        this -> y = y;
    }

     Vektor()
    {
        this -> x = 0;
        this -> y = 0;
    }

    void szorzas(float skalar)
    {
        x = x * skalar;
        y = y * skalar;
    }

    float hossz()
    {
        return sqrt(x * x + y * y);
    }

    void kiir()
    {
        cout << "(" << x << " , " << y << ")" << endl;
    }

    //szorzas skalarral
    Vektor operator* (const float &skalar)
    {
        return Vektor(x * skalar, y * skalar);
    }

    // Dot product / skalaris szorzat
    float operator* (const Vektor &v)
    {

        return x * v.x + y * v.y;
    }

    Vektor operator+ (const Vektor &v)
    {
        return Vektor(x + v.x, y + v.y);
    }

    Vektor operator- (const Vektor &v)
    {
        return Vektor(x - v.x, y - v.y);
    }

    friend ostream &operator<<(ostream &out, const Vektor &v);


};

ostream &operator<<(ostream &out, const Vektor &v)
{
    out << "(" << v.x << " , " << v.y << ")";
}

//ket vektor kozrezart szoge radianban
float szog(Vektor a, Vektor b)
{
    float t = a * b / a.hossz() / b.hossz();
    if(t > 1) t = 1;
    if(t < -1) t = -1;
    return acos(t);
}

const float PI = 3.141592;

float radToDegree(float rad)
{
    return rad * 180 / PI;
}

int main()
{
    Vektor a(2, 3);
    Vektor c(2, 2);
    Vektor d(0, 2);
    a.kiir();

    a.szorzas(5);
    a.kiir();

    Vektor b = a * 5 ;
    cout << b << endl;

    cout << a + b << endl;

    cout << a * b << endl;


    cout << a * b / a.hossz() / b.hossz() << endl;
    cout << szog(a, b) << endl;
    cout << radToDegree(szog(c, d)) << endl;
    return 0;
}
