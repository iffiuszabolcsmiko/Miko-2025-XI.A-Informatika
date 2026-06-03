#include <iostream>
#include <iomanip>

using namespace std;

enum Szin { PIROS, ZOLD, FEHER, SARGA, KEK };
enum Nemzet { BRIT, SVED, DAN, NORVEG, NEMET };
enum Ital { TEA, KAVE, TEJ, SOR, VIZ };
enum Cigi { PALLMALL, DUNHILL, BLENDS, BLUEMASTER, PRINCE };
enum Allat { KUTYA, MADAR, MACSKA, LO, HAL };

string szinNev[] =
{
    "piros","zold","feher","sarga","kek"
};

string nemzetNev[] =
{
    "brit","sved","dan","norveg","nemet"
};

string italNev[] =
{
    "tea","kave","tej","sor","viz"
};

string cigiNev[] =
{
    "Pall Mall","Dunhill","Blends","Bluemaster","Prince"
};

string allatNev[] =
{
    "kutya","madar","macska","lo","hal"
};

int hol(int t[], int ertek)
{
    for(int i=0;i<5;i++)
        if(t[i]==ertek)
            return i;

    return -1;
}

void kiir(int szin[],
          int nemzet[],
          int ital[],
          int cigi[],
          int allat[])
{
    const int W = 15;

    cout << setw(W) << " ";
    for(int i=1;i<=5;i++)
        cout << setw(W) << i;
    cout << endl;

    cout << setw(W) << "Szin";
    for(int i=0;i<5;i++)
        cout << setw(W) << szinNev[szin[i]];
    cout << endl;

    cout << setw(W) << "Nemzet";
    for(int i=0;i<5;i++)
        cout << setw(W) << nemzetNev[nemzet[i]];
    cout << endl;

    cout << setw(W) << "Ital";
    for(int i=0;i<5;i++)
        cout << setw(W) << italNev[ital[i]];
    cout << endl;

    cout << setw(W) << "Cigaretta";
    for(int i=0;i<5;i++)
        cout << setw(W) << cigiNev[cigi[i]];
    cout << endl;

    cout << setw(W) << "Allat";
    for(int i=0;i<5;i++)
        cout << setw(W) << allatNev[allat[i]];
    cout << endl;

    int halasHaz = hol(allat, HAL);

    cout << endl << "A halat a "
         << nemzetNev[nemzet[halasHaz]]
         << " tartja." << endl;
}

bool kovPerm(int a[], int n){
    int piv;
    int i;
    for(i=n-1; i>0; i--){
        if(a[i]>a[i-1]){
            piv=i - 1;
            break;
        }
    }
    if(i==0)
    {
        int j = n - 1;
        while(i < j)
        {
            swap(a[i++], a[j--]);
        }
        return false;
    }

    for(i=n-1; i>piv; i--){
        if(a[i]>a[piv]){
            swap(a[i], a[piv]);
            break;
        }
    }
    i = piv+1;
    int j = n - 1;
    while(i < j)
    {
        swap(a[i++], a[j--]);
    }

    return true;
}

int main()
{
    int szin[]   = {0,1,2,3,4};
    int nemzet[] = {0,1,2,3,4};
    int ital[]   = {0,1,2,3,4};
    int cigi[]   = {0,1,2,3,4};
    int allat[]  = {0,1,2,3,4};

    do //szin
    {
        int piros = hol(szin, PIROS);
        int zold = hol(szin, ZOLD);
        int feher = hol(szin, FEHER);
        int sarga = hol(szin, SARGA);
        int kek = hol(szin, KEK);

        if(feher-zold!=1)
            continue;

        do //nemzet
        {
            int brit= hol(nemzet, BRIT);
            int dan = hol(nemzet, DAN);
            int sved = hol(nemzet, SVED);
            int norveg = hol(nemzet, NORVEG);
            int nemet = hol(nemzet, NEMET);

            if(norveg!=0)
                continue;
            if(abs(norveg-kek)!=1)
                continue;
            if(brit!=piros)
                continue;

            do //ital
            {
                int tea= hol(ital, TEA);
                int kave= hol(ital, KAVE);
                int viz= hol(ital, VIZ);
                int sor= hol(ital, SOR);
                int tej= hol(ital, TEJ);

                if(dan!=tea)
                    continue;
                if(zold!=kave)
                    continue;
                if(tej!=2)
                    continue;

                do // cigi
                {
                    int pallmall= hol(cigi, PALLMALL);
                    int dunhill= hol(cigi, DUNHILL);
                    int blends= hol(cigi, BLENDS);
                    int prince= hol(cigi, PRINCE);
                    int bluemaster= hol(cigi, BLUEMASTER);

                    if(sarga!=dunhill)
                        continue;
                    if(sor!=bluemaster)
                        continue;
                    if(nemet!=prince)
                        continue;
                    if(abs(blends-viz)!=1)
                        continue;

                    do //allat
                    {
                        int kutya= hol(allat, KUTYA);
                        int macska= hol(allat, MACSKA);
                        int madar= hol(allat, MADAR);
                        int lo= hol(allat, LO);
                        int hal= hol(allat, HAL);

                        if(sved!=kutya)
                            continue;
                        if(pallmall!=madar)
                            continue;
                        if(abs(blends-macska)!=1)
                            continue;
                        if(abs(lo-dunhill)!=1)
                            continue;
                        if(nemet!=prince)
                            continue;

                        kiir(szin, nemzet, ital, cigi, allat);

                    }while(kovPerm(allat, 5));
                }while(kovPerm(cigi, 5));
            }while(kovPerm(ital, 5));
        }while(kovPerm(nemzet, 5));
    }while(kovPerm(szin, 5));

    return 0;
}
