#include <bits/stdc++.h>

using namespace std;
const int N = 8;
const int MH = 8;
const int LE = 8;
int grid[N][N] = {0};
int K=1;

void kiir(int szint=0)
{
    cout<<K<<":"<<'\n';
    for (int i = 0; i < LE; i++)
    {
        for (int j = 0; j < LE; j++)
        {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
    cout<<endl;
    K++;
}

bool megoldas(int szint)
{
    return true;
}

bool jo(int i,int j)
{
    for(int k=0; k<LE; k++){
        if(k!=i && grid[k][j] ){
            return false;
        }
        if(k>0 && i-k >=0 && j-k>=0 && grid[i-k][j-k] ){
            return false;
        }
        if(k> 0 && i-k >=0 &&  j+k<LE && grid[i-k][j+k] ){
            return false;
        }
    }
    return true;
}

void backtracking(int szint = 0)
{
    if (szint == MH)
    {
        if (megoldas(szint))
            kiir(szint);
        return;
    }
    for (int i = 0; i < LE; i++)

    {
        grid[szint][i] = 1;
        if (jo(szint,i))
            backtracking(szint + 1);
        grid[szint][i] = 0;
    }
}

int main()
{
 backtracking();
    return 0;
}