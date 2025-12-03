#include <iostream>
#include <iomanip>
#include <fstream>

#define N 50

using namespace std;

bool v[N]; //feldolgozott csomopontok
int d[N]; //tavolsag vektor, minden csomopont tavolsaga a start csomopont
int p[N]; //szulo(parent) vektor, minden csomopont tavolsaga a start csomopont

//Beolvassa a csomopontok szamat es az elek listajat
//felepit egy adjacencia(szomszedsagi) matrixot)
//visszateriti a csomopontok szamat
int beOlvas(string fileName, int graf[][N])
{
    ifstream f(fileName);
    int n = 0;   //csomopontok szama
    f >> n;

    while(f)
    {
        int i, j, w;
        f >> i >> j >> w;
        graf[i][j] = w;
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

void FloydWarshall(int graf[][N], int n)
{
    for(int k = 0 ; k < n; k++)
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                if(graf[i][k] && graf[k][j] && (!graf[i][j] || graf[i][j] > graf[i][k] + graf[k][j]))
                    graf[i][j] = graf[i][k] + graf[k][j];
}

int main()
{
    int graf[N][N] = {0};
    int n = beOlvas("graf.txt", graf);
    kiIr(graf, n);
    FloydWarshall(graf, n);
    kiIr(graf, n);

    return 0;
}
