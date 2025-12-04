#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>

#define N 100

using namespace std;

bool v[N]; //feldolgozott csomopontok
int d[N]; //tavolsag vektor, minden csomopont tavolsaga a start csomopont
int p[N]; //szulo(parent) vektor, minden csomopont tavolsaga a start csomopont
struct Node{
    int dest;
    int weight;
};

//Beolvassa a csomopontok szamat es az elek listajat
int beOlvas(string fileName, vector<vector<Node>> &graf)
{
    ifstream f(fileName);
    if(!f)
    {
        cerr << "Hiba: nem sikerult megnyitni: " << fileName << endl;
        return 0;
    }

    int n = 0;   //csomopontok szama
    f >> n;
    graf.resize(n);

    int i, j, w;
    while(f >> i >> j >> w)
    {
        Node node;
        node.dest = j;
        node.weight = w;
        graf[i].push_back(node);
    }

    return n;
}

//Kiirja a graf adjacencia(szomszedsagi) matrixat
int kiIr(vector<vector<Node>> &graf, int n)
{
    cout << "Szomszedsagi matrix:" << endl;
    for(int i = 0; i < n; i++)
    {
        cout << i << " -> ";
        for(int j = 0; j < graf[i].size(); j++)
        {
            cout << graf[i][j].dest << "(" << graf[i][j].weight << ") ";
        }
        cout << endl;
    }
}

int legkozelebbi(int n)
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

void dijkstra(vector<vector<Node>> &graf, int n, int start)
{
    for(int i = 0; i < n; i++)
    {
        v[i] = 0; //nem dolgoztunk fel egyet sem
        p[i] = -1; //nincs szulo
        d[i] = INT_MAX; //minden tavolsag vegtelen
    }
    d[start] = 0;

    for(int i = 0; i < n; i++)
    {
        int u = legkozelebbi(n);
        //ha a legkozelebbi vegtelen tavolsagra van akkor azt jelenti, hogy kulon komponensben van
        if(u == -1)
            break;
        v[u] = true;
        // szomszedok tavolsaganak frissitese
        for(int j = 0; j < graf[u].size(); j++)
        {
            if(!v[graf[u][j].dest] && d[u] + graf[u][j].weight < d[graf[u][j].dest])
            {
                d[graf[u][j].dest]= d[u] + graf[u][j].weight;
                p[graf[u][j].dest]= u;
            }
        }
    }
}

void kiirUtvonal(int start, int finish)
{
    if(start == finish)
    {
        cout<<"Utvonal "<< start;
        return;
    }
    if(p[finish] == -1)
    {
        cout<<"Nincs utvonal "<< start << " es " << finish << " kozott!" <<endl;
        return;
    }

    kiirUtvonal(start, p[finish]);
    cout<<"->"<<finish;
}

int main()
{
    vector<vector<Node>> graf;
    int n = beOlvas("graf.txt", graf);
    kiIr(graf, n);

    dijkstra(graf, n, 0);
    cout << "p: ";
    for(int i = 0; i < n; i++)
        cout << setw(3) << p[i];
    cout << endl;
    cout << "d: ";
    for(int i = 0; i < n; i++)
        cout << setw(3) << d[i];
    cout << endl;

    kiirUtvonal(0, 3);

    return 0;
}
