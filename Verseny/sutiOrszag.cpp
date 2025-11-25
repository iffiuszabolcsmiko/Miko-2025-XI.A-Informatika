#include <iostream>
#include <vector>

using namespace std;

long long S(long long i);

long long S1_55(long long i)
{
    return (1003 * i - 2003 * i * i + 3007 * i * i * i) % 10000;
}

long long S55_inf(long long i)
{
    return (S(i - 24) + S(i - 55)) % 10000;
}

long long S(long long i)
{
    if(i <= 55)
        return S1_55(i);
    return S55_inf(i);
}

vector<int> sorozat(1000001);

void feltolt(int n)
{
    for(int i = 1; i <= n; i++)
        if(i <= 55)
            sorozat[i] = (1003 * i - 2003 * i * i + 3007 * i * i * i) % 10000;
        else
            sorozat[i] = (sorozat[i - 24] + sorozat[i - 55]) % 10000;
}

long long sum(int n)
{
    long long ossz = 0;
    for(int i = 1; i <= n; i++)
        ossz += sorozat[i];
    return ossz;
}

int haztartasok_x_sutivel(int n, int x)
{
    int haztartas = 0;
    for(int i = 1; i <= n; i++)
        if(sorozat[i] == x)
            haztartas++;
    return haztartas;
}

//tul lassu
long long kivalaszt2OsszegNagyonLassu(int n, int x)
{
    long long k = 0;
    for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            if(sorozat[i] + sorozat[j] == x)
                k++;
    return k;
}

vector<int> sutiErtekek(10000, 0);

void feltoltSutiErtekek(int n)
{
    for(int i = 1; i <= n; i++)
        sutiErtekek[sorozat[i]]++;
}

void kiirSutiErtekek()
{
    for(int i = 0; i < 10000; i++)
        cout << i << ". " << sutiErtekek[i] << endl;
}

//Kombinacio
//C(n, k) = (n - k + 1) / k * C(n, k - 1)
long long C(int n, int k)
{
    // C(n, k) = C(n, n - k)
    if(k > n - k)
        k = n - k;
    long long res = 1;
    for (int i = 1; i <= k; ++i) {
        res = res * (n - i + 1) / i;
    }
    return res;
}

long long kivalaszt2OsszegLassu(int n, int x)
{
    long long ossz = 0;
    for (int i = 0; i < 10000; i++)
        for (int j = i ; j < 10000; j++)
            if(i + j == x)
                if(i == j)
                    ossz += C(sutiErtekek[i], 2);
                else
                    ossz += sutiErtekek[i]*sutiErtekek[j];
    return ossz;
}

long long kivalaszt3OsszegLassu(int n, int x)
{
    long long ossz = 0;
    for (int i = 0; i < 10000; i++)
        for (int j = i ; j < 10000; j++)
            for (int k = j ; k < 10000; k++)
            if(i + j + k == x)
                if(i == j && i == k)
                    ossz += C(sutiErtekek[i], 3);
                else if(i == j)
                    ossz += C(sutiErtekek[i], 2)*sutiErtekek[k];
                else if(j == k)
                    ossz += C(sutiErtekek[k], 2)*sutiErtekek[i];
                else if(i == k)
                    ossz += C(sutiErtekek[i], 2)*sutiErtekek[j];
                else
                    ossz += sutiErtekek[i]*sutiErtekek[j]*sutiErtekek[k];
    return ossz;
}

long long kivalaszt2Osszeg(int x)
{
    long long ossz = 0;
    for (int i = 0; i < 10000 && i <= x / 2; i++)
    {
        int j = x - i;
        // 0 <= i <= j < 10000
        if(j < i) break;
        if(j >= 10000) continue;
        if(i == j)
            ossz += C(sutiErtekek[i], 2);
        else
            ossz += sutiErtekek[i]*sutiErtekek[j];
    }
    return ossz;
}

long long kivalaszt3Osszeg(int x)
{
    long long ossz = 0;
    for(int i = 0; i < 10000 && i <= x / 3; i++)
    {
        for(int j = i; j < 10000 && j <= (x - i) / 2; j++)
        {
            int k = x - i - j;
            // 0 <= i <= j <= k < 10000
            if(k < j) break;
            if(k >= 10000) continue;
            if(i == j && j == k)
                ossz += C(sutiErtekek[i], 3);
            else if(i == j)
                ossz += C(sutiErtekek[i], 2) * sutiErtekek[k];
            else if(j == k)
                ossz += C(sutiErtekek[j], 2) * sutiErtekek[i];
            else
                ossz += sutiErtekek[i] * sutiErtekek[j] * sutiErtekek[k];
        }
    }
    return ossz;
}

int main(){
    //cout << "Si(2)=" << S(2) << endl;
    //cout << "Si(70)=" << S(70) << endl;
    //cout << "Si(999999)=" << S(999999) << endl;

    int n = 1000000;
    feltolt(n);
    cout << "Si(2)=" << sorozat[2] << endl;
    cout << "Si(70)=" << sorozat[70] << endl;
    cout << "Si(999999)=" << sorozat[999999] << endl;
    cout << "SUM_i:1-" << n << "(Si)=" << sum(n) << endl;
    //cout << "0 suti haztartasban=" << haztartasok_x_sutivel(n, 0) << endl;
    feltoltSutiErtekek(n);
    //kiirSutiErtekek();
    cout << "0 sutis haztartasok szama=" << sutiErtekek[0] << endl;

    cout << "hanyfele keppen lehet 2 haztartast kivalasztani ahol osszesen 6666 suti van:"<< endl;
    cout << kivalaszt2Osszeg(6666)<< endl;
    cout << "hanyfele keppen lehet 3 haztartast kivalasztani ahol osszesen 9999 suti van:"<< endl;
    cout << kivalaszt3Osszeg(9999)<< endl;

    return 0;
}

