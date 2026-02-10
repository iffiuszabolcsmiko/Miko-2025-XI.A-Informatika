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
     ~Lista()
     {
         if(head) delete head;
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
            Node *uj = new Node(adat, head, 0);
            head->prev = uj;
            head = uj;
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
    void rendezettbeszur(int adat){
        //ha nem ures
        if(head)
        {
            Node *i = head;
            //megkeressuk a helyet
            while(i != 0 && i->adat < adat)
            {
                i=i->next;
            }
            //ha nem ertunk a vegere
            if(i != 0){
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
                Node *next = i->next, *prev = i->prev;
                if(next)
                    next->prev = prev;
                else
                    tail = prev;
                if(prev)
                    prev->next = next;
                else
                    head = next;

                i->next=0;
                i->prev=0;
                delete i;

                i = next;
            }
            else
            {
                i = i->next;
            }
        }
    }
};

int main()
{
    int n=20;
    Lista lista;
    srand(time(0));
    /*for(int i=0; i<n; i++)
    {
        //lista.rendezettbeszur(rand()%5);
        lista.beszur_hatul(rand()%5);
    }*/
    //lista.beszur_elol(67);
    //lista.beszur_hatul(167);

    lista.beszur_hatul(0);
    lista.beszur_hatul(0);
    lista.beszur_hatul(0);
    lista.beszur_hatul(5);
    lista.beszur_hatul(4);
    lista.beszur_hatul(3);
    lista.beszur_hatul(2);
    lista.beszur_hatul(1);
    lista.beszur_hatul(0);
    lista.beszur_hatul(0);
    lista.beszur_hatul(0);
    lista.beszur_hatul(1);
    lista.beszur_hatul(0);
    lista.beszur_hatul(1);
    lista.beszur_hatul(2);
    lista.beszur_hatul(3);
    lista.beszur_hatul(0);
    lista.beszur_hatul(0);

    lista.kiir();
    lista.torol(0);
    lista.kiir();
    return 0;
}
