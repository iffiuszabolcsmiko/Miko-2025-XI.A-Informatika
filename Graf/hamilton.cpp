#include <iostream>
#include <iomanip>
#include <fstream>

#define N 50

using namespace std;

int graf[N][N] = {0};
int verem[N] = {0};
int n;  //csomopontok szama

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

void kiIrMegoldas()
{
    cout << "Hamilton kor: ";
    for(int i = 0; i < n; i++)
        cout << verem[i] << " ";
    cout << verem[0] << " ";
    cout << endl;
}

bool megoldas(int szint)
{
    return szint == n && graf[verem[szint - 1]][verem[0]] == 1;
}

bool jo(int szint)
{
    //ha tobb mint egy csomopont van az utban
    //es az utolso es az elozo kozt nincs el
    if(szint > 0 && graf[verem[szint - 1]][verem[szint]] == 0)
        return false;

    //ismetlodik valamelyik csomopont
    for(int i = 0; i < szint; i++)
        if(verem[i] == verem[szint])
            return false;

    return true;
}

void backTracking(int szint = 0)
{
    if(megoldas(szint))
    {
        kiIrMegoldas();
    }
    for(int i = 0; i < n; i++)
    {
        verem[szint] = i;
        if(jo(szint))
        {
            backTracking(szint + 1);
        }
    }
}

int main()
{
    n = beOlvas("graf.txt", graf);
    kiIr(graf, n);

    verem[0] = 0;

    backTracking(1);

    return 0;
}


/*
8
0 1
1 2
2 3
3 0
4 5
5 6
6 7
7 4
0 4
1 5
2 6
3 7
*/
