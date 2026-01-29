#include <iostream>

using namespace std;

class Allat {
    int labakSzama;
public:
    void setLabakSzama(int labakSzama)
    {
        this->labakSzama = labakSzama;
    }
    int getLabakSzama()
    {
        return labakSzama;
    }

    virtual void hangotAdKi() = 0;
};

class Macska : public Allat {
public:
    void hangotAdKi() {
        cout << "Miau" << endl;
    }
};

class Kutya : public Allat {
public:
    void hangotAdKi() {
        cout << "Vau-Vau" << endl;
    }
};

class Csibe : public Allat {
public:
    void hangotAdKi() {
        cout << "Csip-Csip" << endl;
    }
};

int main()
{
    Macska m;
    m.setLabakSzama(4);
    Kutya k;
    k.setLabakSzama(4);
    Csibe cs;
    cs.setLabakSzama(2);

    Allat *a[10];
    a[0] = &m;
    a[1] = &k;
    a[2] = &cs;

    for(int i = 0; i < 3; i++)
    {
        cout << a[i]->getLabakSzama() << endl;
        a[i]->hangotAdKi();
    }
    return 0;
}
