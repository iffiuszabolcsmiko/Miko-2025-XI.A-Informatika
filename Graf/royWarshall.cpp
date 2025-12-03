#include <iostream>
#include <fstream>

#define N 50

using namespace std;

bool v[N]; //feldolgozott csomopontok
int d[N]; //tavolsag vektor, minden csomopont tavolsaga a start csomopont
int p[N]; //szulo(parent) vektor, minden csomopont tavolsaga a start csomopont

struct fokszam {
    int be;
    int ki;
};

fokszam fokszamok[N];

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

    int i, j;
    while(f >> i >> j)
    {
        graf[i][j] = 1;
    }

    return n;
}

//Kiirja a graf adjacencia(szomszedsagi) matrixat
void kiIr(int graf[][N], int n)
{
    cout << "Szomszedsagi matrix:" << endl;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
        {
            cout << graf[i][j] << ' ';
        }
        cout << endl;
    }
}

int gyengenOsszeuggoKomponensekSzama(int graf[][N], int n)
{
    return 0;
}

void RoyWarshall(int graf[][N], int n)
{
    for(int k = 0; k < n; k++)
        for(int i = 0; i < n; i++)
            for(int j = 0; j < n; j++)
                if(graf[i][k] && graf[k][j])
                    graf[i][j] = 1;
}

//visszateriti egy graf erosen osszefuggo komponenseinek a szamat
int erosenOsszefuggoKomponensekSzama(int graf[][N], int n)
{
    //komponensek szama
    int k = 0;
    int graf2[N][N];
    //masolat keszitese
    for(int i = 0; i < n; i++)
    {
        graf2[i][i] = 1;
        for(int j = 0; j < n; j++)
            graf2[i][j] = graf[i][j];
    }

    RoyWarshall(graf2, n);

    for(int i = 0; i < n; i++)
        v[i] = 0;

    for(int i = 0; i < n; i++)
    {
        if(!v[i])
        {
            v[i] = 1;
            for(int j = 0; j < n; j++)
            {
                if(graf2[i][j] && graf2[j][i])
                    v[j] = 1;
            }
            k++;
        }
    }
    return k;
}

bool erosenOsszefuggo(int graf[][N], int n)
{
    int graf2[N][N];
    //masolat keszitese
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            graf2[i][j] = graf[i][j];

    RoyWarshall(graf2, n);
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            if(i != j && graf2[i][j] == 0)
                return false;
    return true;
}

void feltoltFokszamok(int graf[][N], int n)
{
    for(int i = 0; i < n; i++)
    {
        fokszamok[i].ki = 0;
        fokszamok[i].be = 0;
        for(int j = 0; j < n; j++)
        {
            if(graf[i][j])
                fokszamok[i].ki++;
            if(graf[j][i])
                fokszamok[i].be++;
        }
    }
}

int main()
{
    int graf[N][N] = {0};
    int n = beOlvas("graf.txt", graf);
    kiIr(graf, n);
    //RoyWarshall(graf, n);
    kiIr(graf, n);
    cout << "erosen osszefuggo komponensek szama ";
    cout << erosenOsszefuggoKomponensekSzama(graf, n) << endl;
    feltoltFokszamok(graf, n);
    for(int i = 0; i < n; i++)
    {
        cout << i << " be: " << fokszamok[i].be << " ki: " << fokszamok[i].ki << endl;
    }
    return 0;
}
