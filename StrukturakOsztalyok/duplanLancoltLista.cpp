#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Node
{
    int adat;
    Node *next;
    Node *prev;
public:
    Node()
    {
        next = 0;
        prev = 0;
    }
    Node(int adat)
    {
        this->adat = adat;
        next = 0;
        prev = 0;
    }
    Node(int adat, Node *next, Node *prev)
    {
        this->adat = adat;
        this->next = next;
        this->prev = prev;
    }
    ~Node()
    {
        if(next) delete next;
    }
    friend class Lista;
};

class Lista
{
    Node *head;
    Node *tail;
public:
    Lista()
    {
        head = 0;
        tail = 0;
    }
    Lista(const Lista &lista)
    {
        head = 0;
        tail = 0;
        for(Node *i =lista.head; i != 0; i = i->next)
        {
            beszur_hatul(i->adat);
        }
    }
    ~Lista()
    {
        if(head) delete head;
    }
    Lista& operator=(const Lista &other){
        if(this != &other)
        {
            //regi lista torlese
            if(head)
                delete head;

            head = 0;
            tail = 0;

            //masolas
            for(Node *i = other.head; i != 0; i = i->next )
            {
                beszur_hatul(i->adat);
            }
        }
        return *this;
    }
    void kiir()
    {
        for(Node *i = head; i != 0; i = i->next)
        {
            cout << i->adat << " ";
        }
        cout << endl;
    }
    void beszur_elol(int adat)
    {
        if(head)
        {
            head->prev = new Node(adat, head, 0);
            head = head->prev;
        }
        else
        {
            head = new Node(adat);
            tail = head;
        }
    }
    void beszur_hatul(int adat)
    {
        if(tail)
        {
            tail->next = new Node(adat, 0, tail);
            tail = tail->next;
        }
        else
        {
            tail = new Node(adat);
            head = tail;
        }
    }
    void rendezett_beszur(int adat)
    {
        //ha nem ures
        if(head)
        {
            Node *i = head;
            //megkeressuk a helyet
            while(i != 0 && i->adat < adat)
            {
                i = i->next;
            }
            //ha nem ertunk a vegere
            if(i != 0)
            {
                Node *uj = new Node(adat, i, i->prev);
                if(i->prev)
                {
                    i->prev->next = uj;
                }
                else
                {
                    head = uj;
                }
                i->prev = uj;
            }
            else
            {
                tail->next = new Node(adat, 0, tail);
                tail = tail->next;
            }
        }
        else
        {
            tail = new Node(adat);
            head = tail;
        }
    }

    void torol(int torlendoElem)
    {
        //kereses
        Node *i = head;
        while(i != 0)
        {
            //torles
            if(i->adat == torlendoElem)
            {
                Node *next = i->next;
                Node *prev = i->prev;

                if(next)
                    next->prev = prev;
                else
                    tail = prev;

                if(prev)
                    prev->next = next;
                else
                    head = next;

                i->next = 0;
                i->prev = 0;
                delete i;

                i = next;
            }
            else
            {
                i = i->next;
            }
        }
    }
    void forEach(int (*func)(int))
    {
        for(Node *i = head; i != 0; i = i->next)
        {
            i->adat = func(i->adat);
        }
    }
    static Lista osszefesul(Lista a, Lista b)
    {
        Node *i = a.head;
        Node *j = b.head;

        Lista c;

        while(i != 0 && j != 0)
        {
            if(i->adat <= j->adat)
            {
                c.beszur_hatul(i->adat);
                i = i->next;
            }
            else
            {
                c.beszur_hatul(j->adat);
                j = j->next;
            }
        }
        while(i != 0)
        {
            c.beszur_hatul(i->adat);
            i = i->next;
        }
        while(j != 0)
        {
            c.beszur_hatul(j->adat);
            j = j->next;
        }
        return c;
    }
};

int negyzet(int x)
{
    return x*x;
}

int GaussOsszeg(int x)
{
    return x * (x - 1) / 2;
}

int main()
{
    int n = 20;
    Lista a, b;
    srand(time(0));
    for(int i=0; i<n; i++)
    {
        a.rendezett_beszur(rand()%100);

    }
    cout << "a:" << endl;
    a.kiir();

    b.beszur_hatul(0);
    b.beszur_hatul(0);
    b.beszur_hatul(0);
    b.beszur_hatul(1);
    b.beszur_hatul(2);
    b.beszur_hatul(3);
    b.beszur_hatul(4);
    b.beszur_hatul(5);
    b.beszur_hatul(0);
    b.beszur_hatul(0);
    b.beszur_hatul(0);
    b.beszur_hatul(6);
    b.beszur_hatul(0);
    b.beszur_hatul(7);
    b.beszur_hatul(8);
    b.beszur_hatul(0);
    b.beszur_hatul(0);
    b.beszur_hatul(0);
    b.beszur_hatul(9);
    b.beszur_hatul(10);
    b.beszur_hatul(11);
    b.beszur_hatul(12);
    b.beszur_hatul(13);
    b.beszur_hatul(0);
    b.beszur_hatul(0);
    b.beszur_hatul(0);
    b.beszur_hatul(14);
    b.beszur_hatul(0);
    b.beszur_hatul(15);
    b.beszur_hatul(16);
    b.beszur_hatul(17);
    b.beszur_hatul(0);
    b.beszur_hatul(0);

    cout << "b:" << endl;
    b.kiir();
    b.torol(0);
    cout << "b torolve az osszes 0:" << endl;
    b.kiir();

    b.forEach(negyzet);
    cout << "b negyzet:" << endl;
    b.kiir();

    cout << "osszefesul:" << endl;
    Lista c = Lista::osszefesul(a, b);
    c.kiir();

    return 0;
}
