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

void beszur(int x)
{
    kupac[n] = x;
    kupacolFel(n);
    n++;
}

void printHeap(int i = 0, string prefix = "", bool isLast = true, bool isRoot = true)
{
    if(i >= n) return;

    cout << prefix;

    if(!isRoot)
        cout << (isLast ? "\xc0\xc4\xc4" : "\xc3\xc4\xc4");

    cout << kupac[i] << endl;

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
    return 0;
}
