#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>

using namespace std;

void kiir(int tomb[], int n)
{
    for(int i = 0; i < n; i++)
        cout << setw(2) << i << ". ";
    cout << endl;
    for(int i = 0; i < n; i++)
        cout << setw(3) << tomb[i] << " ";
    cout << endl;
}

void feltolt(int tomb[], int n)
{
    for(int i = 0; i < n; i++)
        tomb[i] = rand() % 100;
}

void kupacolLe(int kupac[], int n, int k)
{
    if(k < 0 || k >= n) return;
    while(true)
    {
        int bal = 2 * k + 1;
        int jobb = 2 * k + 2;
        int nagyobb = k;

        if(bal < n && kupac[nagyobb] < kupac[bal])
            nagyobb = bal;

        if(jobb < n && kupac[nagyobb] < kupac[jobb])
            nagyobb = jobb;

        if(kupac[k] >= kupac[nagyobb])
            break;

        swap(kupac[k], kupac[nagyobb]);
        k = nagyobb;
    }
}

void heapSort(int tomb[], int n)
{
    //epitsunk egy kupacot
    for(int i = n / 2 - 1; i >= 0; i--)
        kupacolLe(tomb, n, i);

    //csereljuk a gyokeret az utolso elemmmel
    //es kupacoljuk le minden ertek eseten
    for(int i = n - 1; i > 0; i--)
    {
        swap(tomb[i], tomb[0]);
        kupacolLe(tomb, i, 0);
    }
}

int main()
{
    int tomb[100];
    int n = 20;
    srand(time(0));

    feltolt(tomb, n);
    kiir(tomb, n);
    heapSort(tomb, n);
    kiir(tomb, n);
    return 0;
}
