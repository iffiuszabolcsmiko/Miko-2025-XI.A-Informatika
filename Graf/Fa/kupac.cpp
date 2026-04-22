#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int kupac[100];
int n = 0;

void kupacolFel(int k)
{
    int szulo = (k - 1) / 2;
    while(kupac[k] > kupac[szulo])
    {
        swap(kupac[k], kupac[szulo]);
        k = szulo;
        szulo = (k - 1) / 2;
    }
}

void kupacolLe2(int k)
{
    while(true)
    {
        int bal = 2 * k + 1;
        int jobb = 2 * k + 2;
        int nagyobb = k;

        if(bal <n && kupac[nagyobb] > kupac[bal])
            nagyobb = bal;

        if(jobb <n && kupac[nagyobb] > kupac[jobb])
            nagyobb = jobb;

        if(nagyobb = k)
            break;

        swap(kupac[k], kupac[nagyobb]);
        k = nagyobb;
    }
}

void beszur(int x)
{
    if(n >= 100) {
        cout << "Hiba: a kupac megtelt!" << endl;
        return;
    }
    kupac[n] = x;
    kupacolFel(n);
    n++;
}

void felulIr(int k, int x)
{
    kupac[k] = x;
    kupacolFel(k);
    kupacolLe2(k);
}

void printHeap(int i = 0, string prefix = "", bool isLast = true, bool isRoot = true)
{
    if(i >= n) return;

    cout << prefix;

    if(!isRoot)
        cout << (isLast ? "+---" : "|--");

    cout << kupac[i] <<"("<<i<<")"<< endl;

    if(!isRoot)
        prefix += (isLast ? "   " : "|  ");

    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if(left < n)
        printHeap(left, prefix, right >= n, false);

    if(right < n)
        printHeap(right, prefix, true, false);
}

void torol(int k){
    if(k < 0 || k >= n) return;
    kupac[k] = kupac[--n];
    felulIr(k, kupac[k]);
}

int main()
{
    srand(time(0));
    for(int i = 0; i < 10; i++)
    {
        int x = rand() % 100;
        cout << "beszurjuk: " << x << endl;
        beszur(x);
        printHeap();
    }
      felulIr(3, 95);
      cout << "\n--- Toroljuk a 9. indexet! ---" << endl;
      torol(9);
      printHeap();
    return 0;
}
