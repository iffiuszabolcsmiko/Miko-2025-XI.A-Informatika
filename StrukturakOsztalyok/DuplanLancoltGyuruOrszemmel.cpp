#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

class Node{
    int adat;
    Node *next;
    Node *prev;

public:
    Node(int adat = 0, Node *next = 0, Node *prev = 0){
        this->adat = adat;
        this->prev = prev;
        this->next = next;
    }

    friend class Lista;
};

class Lista{
    Node *s; ///sentinel

public:

    Lista(){
        s = new Node();
        s->next = s;
        s->prev = s;
    }
    Lista(const Lista &lista)
    {
        s = new Node();
        s->next = s;
        s->prev = s;
        for(Node *i =lista.s->next; i != lista.s; i = i->next)
        {
            beszur_hatul(i->adat);
        }
    }
    void clear(){
        Node *p = s->next;
        while(p != s){
            Node *tmp = p;
            p = p->next;
            delete tmp;
        }

        s->next = s;
        s->prev = s;
    }
    ~Lista(){
        clear();
        delete s;
    }
    void kiir()
    {
        for(Node *i = s->next; i != s; i = i->next)
        {
            cout << i->adat << " ";
        }
        cout << endl;
    }
    void beszur_elol(int adat)
    {
        Node *uj = new Node(adat, s->next, s);
        s->next->prev = uj;
        s->next = uj;
    }
    void beszur_hatul(int adat)
    {
        Node *uj = new Node(adat, s, s->prev);
        s->prev->next = uj;
        s->prev = uj;
    }
    void rendezett_beszur(int adat)
    {
        Node *i = s->next;
        //megkeressuk a helyet
        while(i != s && i->adat < adat)
        {
            i = i->next;
        }

        Node *uj = new Node(adat, i, i->prev);
        i->prev->next = uj;
        i->prev = uj;
    }
    void torol(int torlendoElem)
    {
        //kereses
        Node *i = s->next;
        while(i != s)
        {
            //torles
            if(i->adat == torlendoElem)
            {
                Node *next = i->next;
                Node *prev = i->prev;

                i->next->prev = prev;
                i->prev->next = next;
                delete i;

                i = next;
            }
            else
            {
                i = i->next;
            }
        }
    }
    Lista& operator=(const Lista& other)
    {
        if(this != &other)
        {
            clear();
            for(Node *i = other.s->next; i != other.s; i = i->next)
            {
                beszur_hatul(i->adat);
            }
        }
        return *this;
    }
};

int main()
{
    int n = 20;
    Lista a, b;
    srand(time(0));
    for(int i=0; i<n; i++)
    {
        a.rendezett_beszur(rand()%100);
        b.beszur_hatul(rand()%3);
    }
    cout << "a:" << endl;
    a.kiir();
    a.torol(0);
    cout << "b:" << endl;
    a.kiir();
    return 0;
}
