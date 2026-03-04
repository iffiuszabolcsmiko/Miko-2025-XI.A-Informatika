#include <iostream>

using namespace std;

class Tort{
private:
    int szamlalo;
    int nevezo;

    static int mod(int x)
    {
        if(x < 0) return -x;
        else return x;
    }
    //legnagyobb kozos oszto
    static int lnko(int a, int b)
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
        int oszto = lnko(szamlalo, nevezo);
        szamlalo /= oszto;
        nevezo /= oszto;

        if(nevezo < 0) {
            szamlalo = -szamlalo;
            nevezo = -nevezo;
        }
    }
public:
    //Konstruktorok
    Tort()
    {
        szamlalo = 0;
        nevezo = 1;
    }
    Tort(int szamlalo)
    {
        this->szamlalo = szamlalo;
        this->nevezo = 1;
    }
    Tort(int szamlalo, int nevezo)
    {
        //hiba
        if(nevezo == 0)
            nevezo = 1;
        this->szamlalo = szamlalo;
        this->nevezo = nevezo;
        this->egyszerusit();
    }
    //getter setter metodusok
    void setSzamlalo(int szamlalo)
    {
        this->szamlalo = szamlalo;
    }
    int getSzamlalo() const
    {
        return szamlalo;
    }
    void setNevezo(int nevezo)
    {
        this->nevezo = nevezo;
    }
    int getNevezo() const
    {
        return nevezo;
    }
    void kiir() const
    {
        cout << this->szamlalo << "/" << this->nevezo << endl;
    }
    //muveletek
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
    //operator tulterhelesek
    Tort operator+(const Tort &t) const
    {
        Tort c;
        c.szamlalo = this->szamlalo * t.nevezo + t.szamlalo * this->nevezo;
        c.nevezo = this->nevezo * t.nevezo;
        c.egyszerusit();
        return c;
    }
    Tort operator-(const Tort &t) const
    {
        Tort c;
        c.szamlalo = this->szamlalo * t.nevezo - t.szamlalo * this->nevezo;
        c.nevezo = this->nevezo * t.nevezo;
        c.egyszerusit();
        return c;
    }
    Tort operator*(const Tort &t) const
    {
        Tort c;
        c.szamlalo = this->szamlalo * t.szamlalo;
        c.nevezo = this->nevezo * t.nevezo;
        c.egyszerusit();
        return c;
    }
    Tort operator/(const Tort &t) const
    {
        Tort c;
        c.szamlalo = this->szamlalo * t.nevezo;
        c.nevezo = this->nevezo * t.szamlalo;
        c.egyszerusit();
        return c;
    }
    //osszehasonlitas operatorok tulterhelese
    bool operator<(const Tort &t) const
    {
        return this->szamlalo * t.nevezo < t.szamlalo * this->nevezo;
    }
    bool operator>(const Tort &t) const
    {
        return this->szamlalo * t.nevezo > t.szamlalo * this->nevezo;
    }
    bool operator<=(const Tort &t) const
    {
        return this->szamlalo * t.nevezo <= t.szamlalo * this->nevezo;
    }
    bool operator>=(const Tort &t) const
    {
        return this->szamlalo * t.nevezo >= t.szamlalo * this->nevezo;
    }
    bool operator==(const Tort &t) const
    {
        return this->szamlalo == t.szamlalo && this->nevezo == t.nevezo;
    }
    bool operator!=(const Tort &t) const
    {
        return this->szamlalo != t.szamlalo || this->nevezo != t.nevezo;
    }

    // Overload << and >> operators as friend functions
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
    //hiba
    if(t.nevezo == 0)
        t.nevezo = 1;
    t.egyszerusit();
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

    cout << a << " + " << b  << " = " << a + b << endl;
    cout << a << " - " << b  << " = " << a - b << endl;
    cout << a << " * " << b  << " = " << a * b << endl;
    cout << a << " / " << b  << " = " << a / b << endl;

    if(a < b)
        cout << a << " a kisebb" << endl;
    else
        cout << b << " a kisebb" << endl;

    if(a == b)
        cout << "egyenlo" << endl;
    else
        cout << "NEM egyenlo" << endl;

    return 0;
}
