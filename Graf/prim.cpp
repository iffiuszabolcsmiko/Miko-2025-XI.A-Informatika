#include <iostream>
#include <iomanip>
#include <fstream>

#define N 100
using namespace std;

int p[N]; //szulo(parent) vektor, minden csomopont tavolsaga a start csomopont
bool v[N]; //feldolgozott csomopontok
int d[N]; //tavolsag vektor, minden csomopont tavolsaga a start csomopont

//Beolvassa a csomopontok szamat es az elek listajat
//felepit egy adjacencia(szomszedsagi) matrixot)
//visszateriti a csomopontok szamat
int beOlvas(string fileName, int graf[][N])
{
    ifstream f(fileName);
    if(!f)
    {
        cerr << "Hiba: nem sikerult megnyitni: " << fileName << endl;
        return 0;
    }

    int n = 0;   //csomopontok szama
    f >> n;

    int i, j, w;
    while(f >> i >> j >> w)
    {
        graf[i][j] = w;
        graf[j][i] = w;
    }

    return n;
}

//Kiirja a graf adjacencia(szomszedsagi) matrixat
void kiIr(int graf[][N], int n)
{
    cout << "Szomszedsagi matrix:" << endl;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cout << setw(3) << graf[i][j];
        }
        cout << endl;
    }
}

int legkozelebbi(int graf[][N], int n)
{
    int min_dist = INT_MAX;
    int mini = -1;
     for(int i = 0; i < n; i++)
     {
         if(!v[i] && d[i] < min_dist)
         {
             min_dist = d[i];
             mini = i;
         }
     }
     //cout << mini << " " << min_dist << endl;
     return mini;
}

int prim(int graf[][N], int n)
{
    int total_weight=0;
    int start = 0; //kezdo csomopont
    for(int i = 0; i < n; i++)
    {
        v[i] = 0; //nem dolgoztunk fel egyet sem
        p[i] = -1; //nincs szulo
        d[i] = INT_MAX; //minden tavolsag vegtelen
    }
    d[start] = 0;

    cout << "Kivalasztott elek:" << endl;
    for(int i = 0; i < n; i++)
    {
        int u = legkozelebbi(graf, n);
        //ha a legkozelebbi vegtelen tavolsagra van akkor azt jelenti, hogy kulon komponensben van
        if(u == -1)
            break;

        if(p[u] != -1)
        {
            cout << p[u] << " - " << u << endl;
        }

        v[u] = true;
        total_weight += d[u];
        // szomszedok tavolsaganak frissitese
        for(int j = 0; j < n; j++)
        {
            if(!v[j] && graf[u][j] != 0 && graf[u][j] < d[j])
            {
                d[j] = graf[u][j];
                p[j] = u;
            }
        }
    }
    return total_weight;
}

int main()
{
    int graf[N][N] = {0};
    int n = beOlvas("graf.txt", graf);
    kiIr(graf, n);

    int total_weight = prim(graf, n);
    cout << "Prim total weight: " << total_weight << endl;

    return 0;
}
