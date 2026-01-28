#include <iostream>

using namespace std;

struct Tort{
    int szamlalo;
    int nevezo;
};

void kiir(Tort t)
{
    cout << t.szamlalo << "/" << t.nevezo << endl;
}

int mod(int x){
    if(x < 0) return -x;
    else return x;
}

int lnko(int a, int b)
{
    while(b != 0)
    {
        int maradek = a % b;
        a = b;
        b = maradek;
    }
    return mod(a);
}

Tort egyszerusit(Tort a)
{
    int lnk = lnko(a.nevezo, a.szamlalo);
    a.nevezo = a.nevezo / lnk;
    a.szamlalo = a.szamlalo / lnk;
    return a;
}

Tort szorzas(Tort a, Tort b)
{
    Tort c;
    c.szamlalo = a.szamlalo * b.szamlalo;
    c.nevezo = a.nevezo * b.nevezo;
    return egyszerusit(c);
}

Tort osztas(Tort a, Tort b)
{
    Tort c;
    c.szamlalo = a.szamlalo * b.nevezo;
    c.nevezo = a.nevezo * b.szamlalo;
    return egyszerusit(c);
}

Tort osszeadas(Tort a, Tort b)
{
    Tort c;
    c.szamlalo = a.szamlalo * b.nevezo + b.szamlalo * a.nevezo;
    c.nevezo = a.nevezo * b.nevezo;
    return egyszerusit(c);
}

Tort kivonas(Tort a, Tort b)
{
    Tort c;
    c.szamlalo = a.szamlalo * b.nevezo - b.szamlalo * a.nevezo;
    c.nevezo = a.nevezo * b.nevezo;
    return egyszerusit(c);
}

int main()
{
    Tort a;
    Tort b;
    a.szamlalo = 2;
    a.nevezo = 3;
    b.szamlalo = 5;
    b.nevezo = 6;
    cout << "a = ";
    kiir(a);
    cout << "b = ";
    kiir(b);
    cout << "a * b = ";
    kiir(szorzas(a, b));
    cout << "a / b = ";
    kiir(osztas(a, b));
    cout << "a + b = ";
    kiir(osszeadas(a, b));
    cout << "a - b = ";
    kiir(kivonas(a, b));
    return 0;
}
