#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>
#include <stack>

#define N 50

using namespace std;

int visited[N]; //hova jutott el a BFS vagy a DFS
int halmaz[N];
int p[N]; //szulo(parent) vektor, minden csomopont tavolsaga a start csomopont

//Beolvassa a csomopontok szamat es az elek listajat
//felepit egy adjacencia(szomszedsagi) matrixot)
//visszateriti a csomopontok szamat
int beOlvas(string fileName, int graf[][N])
{
    ifstream f(fileName);
    int n = 0;   //csomopontok szama
    f >> n;

    int i, j;
    while(f >> i >> j)
    {
        graf[i][j] = 1;
        graf[j][i] = 1;
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

bool paros(int graf[][N], int n)
{
    //nem tartozik egyik halmazba sem
    for(int i = 0; i < n; i++){
        visited[i] = 0;
        halmaz[i] = 0;
    }

    int start = 0;
    halmaz[start] = 1;
    queue<int> sor;
    sor.push(start);
    while(!sor.empty())
    {
        int u = sor.front();
        sor.pop();
        if(!visited[u]) // meg nem latogattuk meg
        {
            visited[u] = true;
            for(int i = 0; i < n; i++)
            {
                if(graf[u][i] != 0)
                {
                    if(halmaz[i] == halmaz[u])
                    {
                        return false;
                    }
                    else
                    {
                        halmaz[i] = -1 * halmaz[u];
                    }
                    if(!visited[i])
                    {
                        sor.push(i);
                    }
                }
            }
        }
    }
    return true;
}

int main()
{
    int graf[N][N] = {0};
    int n = beOlvas("graf.txt", graf);   //csomopontok szama
    kiIr(graf, n);
    if(paros(graf, n))
        cout<<"paros graf";
    else
        cout<<"nem paros";
    return 0;
}
