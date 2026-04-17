#include <iostream>
#include <fstream>
using namespace std;
#define N 100
struct Node{
    int adat;
    Node *next;
};

class Lista{
    Node *head;
public:
    Lista(){
        head = 0;
    }
    void beszurElol(int adat){
        Node *a = new Node;
        a->adat = adat;
        a->next = head;
        head = a;
    }
    void kiir(){
        for(Node *p = head; p != 0; p = p->next)
            cout << p->adat << " ";
    }
    friend class SzomszedsagiLista;
};

class SzomszedsagiLista{
    Lista lista[N];
    int n;
public:
    SzomszedsagiLista()
    {
        n = 0;
    }
    void beolvas(char filename[])
    {
        ifstream f;
        f.open(filename);
        if(!f)
        {
            cout << "nem sikerult megnyitni a " << filename << " allomanyt" << endl;
            return;
        }
        f >> n;
        int i, j;
        while(f >> i >> j)
        {
            lista[i].beszurElol(j);
            lista[j].beszurElol(i);
        }
    }
    void kiir(){
        cout << "Szomszedsagi lista:" << endl;
        for(int i = 0;i < n; i++)
        {
            cout << i << ": ";
            lista[i].kiir();
            cout << endl;
        }
    }

    int convert_to_adj_matrix(int graf[][N])
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = i; j < n; j++)
            {
                graf[i][j] = 0;
                graf[j][i] = 0;
            }
        }
        for (int i = 0; i < n; i++)
        {
                for(Node *p = lista[i].head; p != 0; p = p->next)
                {
                    graf[i][p->adat] = 1;
                }
        }
        return n;
    }
};

void kiir(int graf[][N],int n){
    cout << "Szomszedsagi matrix:" << endl;
     for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout<<graf[i][j] <<" ";
            }
            cout<<"\n";
        }

}

int main()
{
    SzomszedsagiLista graf;
    graf.beolvas("graf.txt");
    graf.kiir();

    int matrix_graf[N][N];
    int n = graf.convert_to_adj_matrix(matrix_graf);
    kiir(matrix_graf, n);
    return 0;
}
