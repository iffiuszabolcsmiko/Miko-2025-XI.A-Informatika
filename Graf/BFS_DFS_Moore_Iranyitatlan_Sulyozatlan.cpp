#include <iostream>
#include <iomanip>
#include <fstream>
#include <stack>
#include <queue>

#define N 50

using namespace std;

int v[N]; //hova jutott el a BFS vagy a DFS
int d[N]; //tavolsag vektor, minden csomopont tavolsaga a start csomopont
int p[N]; //szulo(parent) vektor, minden csomopont tavolsaga a start csomopont
int fokszam[N]; //csomopontok fokszama

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
        //oda es vissza is bellitjuk az elet, mert iranyitatlan a graf
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

//Depth-first search Melysegi bejaras
//n csomopontok szama
//start kezdo csucs
void dfs(int graf[][N], int n, int start)
{
    //cout << "DFS sorrend: ";
    stack<int> verem;
    verem.push(start);
    while(!verem.empty())
    {
        int u = verem.top();
        verem.pop();
        if(!v[u]) //meg nem latogattuk meg
        {
            v[u] = true;
            //cout << u << " ";
            for(int i = 0; i < n; i++)
            {
                if(!v[i] && graf[u][i])
                {
                    verem.push(i);
                }
            }
        }
    }
    //cout << endl;
}

//rekurziv dfs
void dfs_rekurziv(int graf[][N], int n, int start)
{
    v[start] = true;
    for(int i = 0; i < n; i++)
    {
        if(!v[i] && graf[start][i])
        {
            dfs_rekurziv(graf, n, i);
        }
    }
}

//Breath-first search Szelessegi bejaras
//n csomopontok szama
//start kezdo csucs
void bfs(int graf[][N], int n, int start)
{
    //cout << "BFS sorrend: ";
    queue<int> sor;
    sor.push(start);
    while(!sor.empty())
    {
        int u = sor.front();
        sor.pop();
        if(!v[u]) // meg nem latogattuk meg
        {
            v[u] = true;
            //cout << u << " ";
            for(int i = 0; i < n; i++)
            {
                if(!v[i] && graf[u][i])
                {
                    sor.push(i);
                }
            }
        }
    }
    //cout << endl;
}

//feltolt egy tombot egy ertekkel
void feltolt(int tomb[], int n, int ertek)
{
    for(int i = 0; i < n; i++)
    {
        tomb[i] = ertek;
    }
}

//visszateriti egy graf osszefuggo komponenseinek a szamat
int komponensekSzama(int graf[][N], int n)
{
    int k = 0;

    feltolt(v, n, 0);

    for(int i = 0; i < n; i++)
    {
        if(!v[i])
        {
            k++;
            dfs(graf, n, i);
        }
    }

    return k;
}

//minden csomopont tavolsaga a start csomoponttol
//BFS-en alapul
void MooreTavolsag(int graf[][N], int n, int start)
{
    feltolt(p, n, -1);  //szulo vektor
    feltolt(d, n, -1);  //tavolsag vektor
    d[start] = 0;   //kezdo csomopont tavolsaga onmagatol 0
    queue<int> sor;
    sor.push(start);
    while(!sor.empty())
    {
        int u = sor.front();
        sor.pop();
        for(int i = 0; i < n; i++)
        {
            if(d[i] == -1 && graf[u][i])    // meg nem jartunk ott es van el oda
            {
                d[i] = d[u] +1;
                p[i] = u;
                sor.push(i);
            }
        }
    }
}

//kiirja az utvonalat start es finish kozott forditott sorrendben
void kiirUtvonal(int start, int finish)
{
    if(p[finish] == -1)
    {
        cout<<"Nincs utvonal "<< start << " es " << finish << " kozott!" <<endl;
        return;
    }
    else
    {
        cout<<"Utvonal "<< start << " es " << finish << " kozott: ";
    }
    int via = finish;
    do
    {
        cout << via << "<-";
        via = p[via];
    }
    while(via != start);
    cout << start << endl;
}

//kiir utvonal rekurziv
void kiirUtvonal_r(int start, int finish)
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

    kiirUtvonal_r(start, p[finish]);
    cout<<"->"<<finish;
}

//a fokszam tomb tartalmazza minden csomopont fokszamat
void csomopontokFokszama(int graf[][N], int n)
{
    for(int i = 0; i < n; i++)
    {
        fokszam[i] = 0;
        for(int j = 0; j < n; j++)
        {
            if(graf[i][j]) fokszam[i]++;
        }
    }
}

//eldonti hogy egy graf teljes vagy sem
bool teljesGraf(int graf[][N], int n)
{
    csomopontokFokszama(graf, n);
    for(int i = 0; i < n; i++)
        if(fokszam[i] != n - 1)
            return false;
    return true;
}

// visszateriti az izolalt csomopontok szamat
int izolaltPontokSzama(int graf[][N], int n)
{
    csomopontokFokszama(graf, n);
    int k = 0;
    for(int i = 0; i < n; i++)
    {
        if(fokszam[i] == 0)
        {
            k++;
        }
    }
    return k;
}

//a source graf komplementere a destben grafban lesz
void komplementer(int source[][N], int dest[][N], int n)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(i == j) dest[i][j] = 0;
            else dest[i][j] = !source[i][j];
        }
    }
}

// van-e kor a komponensben
bool kormentesKomponens(int graf[][N], int n, int start)
{
    int p[N];
    int v[N];
    feltolt(v, n, 0);
    feltolt(p, n, -1);
    stack<int> verem;
    verem.push(start);
    p[start] = -1;  //startnak nincs szuloje
    while(!verem.empty())
    {
        int u = verem.top();
        verem.pop();
        v[u] = true;
        for(int i = 0; i < n; i++)
        {
            if (!v[i] && graf[u][i])
            {
                if(p[i] != -1) return true;
                p[i] = u;
                verem.push(i);
            }
        }
    }
    return false;
}

//van-e kor a grafban
bool kormentes(int graf[][N], int n)
{
    feltolt(v, n, 0);
    feltolt(p, n, -1);

    for(int i = 0; i < n; i++)
    {
        if(!v[i])
        {
            dfs(graf, n, i);
            if(kormentesKomponens(graf, n, i))
                return false;
        }
    }

    return true;
}

bool erdo(int graf[][N], int n)
{
    return kormentes(graf, n) && komponensekSzama(graf, n) > 1;
}

bool fa(int graf[][N], int n)
{
    return !kormentesKomponens(graf, n, 0) && komponensekSzama(graf, n) == 1;
}

int main()
{
    int graf[N][N] = {0};
    int n = beOlvas("graf.txt", graf);   //csomopontok szama
    kiIr(graf, n);

    int graf_komplementer[N][N];
    komplementer(graf, graf_komplementer, n);
    cout << "A graf komplementere:" << endl;
    kiIr(graf_komplementer, n);

    int start = 0;

    MooreTavolsag(graf, n, start);
    cout << "Moore tavolsag:" << endl;
    for(int i = 0; i < n; i++)
    {
        cout << start << " - " << i << " : " << d[i] << " tavolsagra van" << endl;
    }

    kiirUtvonal_r(start, 3);

    cout << endl << "Komponensek szama: "<< komponensekSzama(graf, n) << endl;

    cout << "Izolalt pontok szama: " << izolaltPontokSzama(graf, n) << endl;

    if(teljesGraf(graf, n))
        cout << "Teljes graf" << endl;
    else
        cout << "Nem teljes graf" << endl;

    feltolt(p, n, -1);
    feltolt(v, n, 0);
    if(kormentes(graf, n))
        cout << "Nincs benne kor" << endl;
    else
        cout << "Van benne kor" << endl;

    if(fa(graf, n))
        cout << "Ez egy fa" << endl;
    else
        cout << "Nem fa" << endl;

    if(erdo(graf, n))
        cout << "Erdo" << endl;
    else
        cout << "Nem erdo" << endl;

    return 0;
}
