#include <iostream>

using namespace std;

class Tort{
private:
    int szamlalo;
    int nevezo;

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

    void egyszerusit()
    {
        int lnk = lnko(this->nevezo, this->szamlalo);
        this->nevezo = this->nevezo / lnk;
        this->szamlalo = this->szamlalo / lnk;
    }

public:

    Tort() {
        this->szamlalo = 0;
        this->nevezo = 1;
    }
    Tort(int szamlalo) {
        this->szamlalo = szamlalo;
        this->nevezo = 1;
    }
    Tort(int szamlalo, int nevezo) {
        this->szamlalo = szamlalo;
        this->nevezo = nevezo;
    }

    void setSzamlalo(int szamlalo){
        this->szamlalo = szamlalo;
    }
    int getSzamlalo(){
        return szamlalo;
    }
    void setNevezo(int nevezo){
        this->nevezo = nevezo;
    }
    int getNevezo(){
        return nevezo;
    }

    void kiir()
    {
        cout << this->szamlalo << "/" << this->nevezo << endl;
    }

    Tort szorzas(Tort b)
    {
        Tort c;
        c.szamlalo = this->szamlalo * b.szamlalo;
        c.nevezo = this->nevezo * b.nevezo;
        c.egyszerusit();
        return c;
    }

    Tort osztas(Tort b)
    {
        Tort c;
        c.szamlalo = this->szamlalo * b.nevezo;
        c.nevezo = this->nevezo * b.szamlalo;
        c.egyszerusit();
        return c;
    }

    Tort osszeadas(Tort b)
    {
        Tort c;
        c.szamlalo = this->szamlalo * b.nevezo + b.szamlalo * this->nevezo;
        c.nevezo = this->nevezo * b.nevezo;
        c.egyszerusit();
        return c;
    }

    Tort kivonas(Tort b)
    {
        Tort c;
        c.szamlalo = this->szamlalo * b.nevezo - b.szamlalo * this->nevezo;
        c.nevezo = this->nevezo * b.nevezo;
        c.egyszerusit();
        return c;
    }

    // Overload + operator
    Tort operator+(const Tort &t)
    {
        Tort c;
        c.szamlalo = this->szamlalo * t.nevezo + t.szamlalo * this->nevezo;
        c.nevezo = this->nevezo * t.nevezo;
        c.egyszerusit();
        return c;
    }
    // Overload - operator
    Tort operator-(const Tort &t)
    {
        Tort c;
        c.szamlalo = this->szamlalo * t.nevezo - t.szamlalo * this->nevezo;
        c.nevezo = this->nevezo * t.nevezo;
        c.egyszerusit();
        return c;
    }
    // Overload * operator
    Tort operator*(const Tort &t)
    {
        Tort c;
        c.szamlalo = this->szamlalo * t.szamlalo;
        c.nevezo = this->nevezo * t.nevezo;
        c.egyszerusit();
        return c;
    }
    // Overload / operator
    Tort operator/(const Tort &t)
    {
        Tort c;
        c.szamlalo = this->szamlalo * t.nevezo;
        c.nevezo = this->nevezo * t.szamlalo;
        c.egyszerusit();
        return c;
    }

    // Overload << and >> as friend functions
    friend ostream &operator<<(ostream &out, const Tort &t);
    friend istream &operator>>(istream &in, Tort &t);

};

// Overload << for output
ostream &operator<<(ostream &out, const Tort &t)
{
    out << t.szamlalo << "/" << t.nevezo;
    return out;
}

// Overload >> for input
istream &operator>>(istream &in, Tort &t)
{
    in >> t.szamlalo >> t.nevezo;
    return in;
}


int main()
{
    Tort a(2, 3);
    Tort b(5, 6);
    Tort c;

    cout << "a = ";
    a.kiir();
    cout << "b = ";
    b.kiir();
    cout << "a * b = ";
    c = a.szorzas(b);
    c.kiir();
    cout << "a / b = ";
    c = a.osztas(b);
    c.kiir();
    cout << "a + b = ";
    c = a.osszeadas(b);
    c.kiir();
    cout << "a - b = ";
    c = a.kivonas(b);
    c.kiir();

    cout << "operatorokkal:" << endl;

    cout << a + b << endl << a - b << endl << a * b << endl << a / b << endl;
    return 0;
}
