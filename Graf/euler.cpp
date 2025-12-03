#include <iostream>
#include <fstream>
#define N 50

using namespace std;

struct fokszam {
    int be;
    int ki;
};

fokszam iranyitott_fokszam[N];
int iranyitatlan_fokszam[N];

int beOlvasIranyitatlan(string fileName, int graf[][N])
{
    ifstream f(fileName);
    if(!f)
    {
        cerr << "Hiba: nem sikerult megnyitni: " << fileName << endl;
        return 0;
    }

    int n = 0;   //csomopontok szama
    f >> n;

    int i, j, elSzam;
    while(f >> i >> j >> elSzam)
    {
        graf[i][j] = elSzam;
        graf[j][i] = elSzam;
    }

    return n;
}

int beOlvasIranyitott(string fileName, int graf[][N])
{
    ifstream f(fileName);
    if(!f)
    {
        cerr << "Hiba: nem sikerult megnyitni: " << fileName << endl;
        return 0;
    }

    int n = 0;   //csomopontok szama
    f >> n;

    int i, j, elSzam;
    while(f >> i >> j >> elSzam)
    {
        graf[i][j] = elSzam;
    }

    return n;
}

void kiIr(int graf[][N], int n)
{
    cout << "Szomszedsagi matrix:" << endl;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cout << graf[i][j] << ' ';
        }
        cout << endl;
    }
}

void feltoltFokszamokIranyitott(int graf[][N], int n)
{
    for(int i = 0; i < n; i++)
    {
        iranyitott_fokszam[i].ki = 0;
        iranyitott_fokszam[i].be = 0;
        for(int j = 0; j < n; j++)
        {
            if(graf[i][j])
                iranyitott_fokszam[i].ki += graf[i][j];
            if(graf[j][i])
                iranyitott_fokszam[i].be += graf[j][i];
        }
    }
}

void feltoltFokszamokIranyitatlan(int graf[][N], int n)
{
    for(int i = 0; i < n; i++)
    {
        iranyitatlan_fokszam[i] = 0;
        for(int j = 0; j < n; j++)
        {
            if(graf[i][j]) iranyitatlan_fokszam[i] += graf[i][j];
        }
    }
}

bool eulerIranyitatlan(int n){
    for(int i = 0; i < n; i++)
    {
        if(iranyitatlan_fokszam[i] % 2 != 0)
        {
            return false;
        }
    }
    return true;
}

bool eulerIranyitott(int n)
{
    for(int i = 0; i < n; i++)
    {
        if(iranyitott_fokszam[i].be != iranyitott_fokszam[i].ki)
        {
            return 0;
        }
    }
    return 1;
}

void kiIrFokszamokIranyitatlan(int n)
{
    for(int i = 0; i < n; i++)
    {
        cout << i << ": " << iranyitatlan_fokszam[i] << endl;
    }
}

void kiIrFokszamokIranyitott(int n)
{
    for(int i = 0; i < n; i++)
    {
        cout << i << ": be:" << iranyitott_fokszam[i].be << " ki: " << iranyitott_fokszam[i].ki << endl;
    }
}

int main()
{
    int graf[N][N] = {0};
    int n = beOlvasIranyitatlan("graf.txt", graf);
    kiIr(graf, n);

    //iranyitatlan
    feltoltFokszamokIranyitott(graf, n);
    kiIrFokszamokIranyitatlan(n);
    if(eulerIranyitott(n))
    {
        cout<<"Van euler vonal" << endl;
    }
    else
    {
        cout<<"Nincs euler vonal" << endl;
    }

    //iranyitott
    feltoltFokszamokIranyitatlan(graf, n);
    kiIrFokszamokIranyitatlan(n);
    if(eulerIranyitatlan(n))
    {
        cout<<"Van euler vonal" << endl;
    }
    else
    {
        cout<<"Nincs euler vonal" << endl;
    }

    return 0;
}
