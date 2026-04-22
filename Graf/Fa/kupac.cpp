#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int kupac[100];
int n = 0;

void kupacolFel(int k)
{
    if(k < 0 || k >= n) return;
    int szulo = (k - 1) / 2;
    while(kupac[k] > kupac[szulo])
    {
        swap(kupac[k], kupac[szulo]);
        k = szulo;
        szulo = (k - 1) / 2;
    }
}

/*void kupacolLe2(int k)
{
    if(k < 0 || k >= n) return;
    int bal = 2 * k + 1;
    int jobb = 2 * k + 2;
    int nagyobb = k;

    if(bal < n && kupac[nagyobb] < kupac[bal])
        nagyobb = bal;
    }

    if(jobb < n && kupac[nagyobb] < kupac[jobb])
        nagyobb = jobb;
    }

    while(kupac[k] > kupac[nagyobb])
    {
        swap(kupac[k], kupac[nagyobb]);
        k = nagyobb;
        bal = 2 * k + 1;
        jobb = 2 * k + 2;
        nagyobb = k;

        if(bal < n && kupac[nagyobb] < kupac[bal])
            nagyobb = bal;
        }

        if(jobb < n && kupac[nagyobb] < kupac[jobb])
            nagyobb = jobb;
        }
    }
}*/

void kupacolLe(int k)
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

void beszur(int x)
{
    kupac[n] = x;
    n++;
    kupacolFel(n - 1);
}

void felulIr(int k, int x)
{
    if(k < 0 || k >= n) return;
    kupac[k] = x;
    int szulo = (k - 1) / 2;
    if(kupac[k] > kupac[szulo]){
        kupacolFel(k);
    }else{
        kupacolLe(k);
    }
}

void torol(int k)
{
    if(k < 0 || k >= n) return;
    n--;
    felulIr(k, kupac[n]);
}

void printHeap(int i = 0, string prefix = "", bool isLast = true, bool isRoot = true)
{
    if(i >= n) return;

    cout << prefix;

    if(!isRoot)
        cout << (isLast ? "\xc0\xc4\xc4" : "\xc3\xc4\xc4");

    cout << kupac[i] << "(" << i << ")" << endl;

    if(!isRoot)
        prefix += (isLast ? "   " : "\xb3  ");

    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if(left < n)
        printHeap(left, prefix, right >= n, false);

    if(right < n)
        printHeap(right, prefix, true, false);
}
int main()
{
    srand(time(0));
    for(int i = 0; i <= 10; i++)
    {
        int x = rand() % 100;
        cout << "beszurjuk: " << x << endl;
        beszur(x);
        printHeap();
    }
    cout << "felulirjuk a 3. indexen levo elemet 95 ertekkel" << endl;
    felulIr(3, 95);
    printHeap();
    cout << "toroljuk az a 1. indexen levo elemet" << endl;
    torol(1);
    printHeap();
    return 0;
}
