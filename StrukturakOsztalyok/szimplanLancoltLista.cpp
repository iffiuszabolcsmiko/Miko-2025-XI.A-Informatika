#include <iostream>

using namespace std;

class Node {
    int adat;
    Node *next;
public:
    Node()
    {
        next = 0;
    }
    Node(int adat)
    {
        this->adat = adat;
        next = 0;
    }
    Node(int adat, Node *next)
    {
        this->adat = adat;
        this->next = next;
    }
    ~Node()
    {
        if(next) delete next;
    }
    void felfuz(int adat)
    {
        if(next) next->felfuz(adat);
        else next = new Node(adat);
    }
    friend class Lista;
};

class Lista{
    Node *head;
public:
    Lista(){
        head = 0;
    }
    Lista(const Lista &other){
        head = 0;
        for(Node *i = other.head; i != 0; i = i->next )
        {
            beszur_hatul(i->adat);
        }
    }
    Lista& operator=(const Lista &other){
        if(this != &other)
        {
            //regi lista torlese
            if(head)
                delete head;
            head = 0;

            //masolas
            for(Node *i = other.head; i != 0; i = i->next )
            {
                beszur_hatul(i->adat);
            }
        }
        return *this;
    }
    ~Lista()
    {
        if(head) delete head;
    }
    void beszur_elol(int adat){
        head = new Node(adat, head);
    }
    void beszur_hatul(int adat)
    {
        if(head)
            head->felfuz(adat);
        else
            head = new Node(adat);
    }
    void kiir()
    {
        for(Node *i = head; i != 0; i = i->next)
            cout << i->adat << " ";
        cout << endl;
    }
};

void copy_cotr_test(Lista a){
    a.beszur_hatul(244);
}

int main()
{
    Lista a, b;
    int n = 10;
    for(int i = 0; i < n; i++)
    {
        a.beszur_elol(i);
        b.beszur_hatul(i);
    }
    cout << "a: ";
    a.kiir();
    cout << "b: ";
    b.kiir();
    cout << "masolo konstruktor teszt:" << endl;
    copy_cotr_test(b);
    b.kiir();
    cout << "ertekadas" << endl;
    a = b;
    b.beszur_hatul(1000);
    b.kiir();
    a.kiir();
    return 0;
}
