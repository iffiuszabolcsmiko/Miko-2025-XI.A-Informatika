#include <iostream>
#include <bitset>

using namespace std;
/*
0   x      (4 byte)
4   x2     (4 byte)
8   y      (2 byte)
10  c      (1 byte)
11  padding (1 byte)
4 + 4 + 2 + 1 + 1 = 12 byte
*/
struct valami{
    int x;     // 4 byte
    int x2;    // 4 byte
    short y;   // 2 byte
    char c;    // 1 byte
};

//gyors egesz kitevoju hatvanyozas
long long hatvany(long long alap, int kitevo){
    long long eredmeny = 1;
    while(kitevo){
        if(kitevo % 2){
            eredmeny *= alap;
        }
        alap *= alap;
        kitevo /= 2;
    }
    return eredmeny;
}

int main(){
    int byteSize;

    long long ll = -1;
    byteSize = sizeof(long long);
    cout << "long long: " << byteSize << " byte" <<  endl;
    cout << "-2^" << 8 * byteSize - 1 << " <-> " << "2^" << 8 * byteSize - 1 << "-1 : ";
    cout << hatvany(2, 8 * byteSize - 1) << " <-> " << hatvany(2, 8 * byteSize - 1) - 1 << endl;
    cout << bitset<64>(ll) << endl;

    int i = -1;
    byteSize = sizeof(int);
    cout << "int: " << byteSize << " byte" << endl;
    cout << "-2^" << 8 * byteSize - 1 << " <-> " << "2^" << 8 * byteSize - 1 << "-1 : ";
    cout << (int)hatvany(2, 8 * byteSize - 1) << " <-> " << hatvany(2, 8 * byteSize - 1) - 1 << endl;
    cout << bitset<32>(i) << endl;

    short s = -1;
    byteSize = sizeof(short);
    cout << "short: " << byteSize << " byte" << endl;
    cout << "-2^" << 8 * byteSize - 1 << " <-> " << "2^" << 8 * byteSize - 1 << "-1 : ";
    cout << (short)hatvany(2, 8 * byteSize - 1) << " <-> " << hatvany(2, 8 * byteSize - 1) - 1 << endl;
    cout << bitset<16>(s) << endl;

    char c = -1;
    byteSize = sizeof(char);
    cout << "char: " << byteSize << " byte" << endl;
    cout << "-2^" << 8 * byteSize - 1 << " <-> " << "2^" << 8 * byteSize - 1 << "-1 : ";
    cout << -hatvany(2, 8 * byteSize - 1) << " <-> " << hatvany(2, 8 * byteSize - 1) - 1 << endl;
    cout << bitset<8>(c) << endl;

    bool b = true;
    byteSize = sizeof(bool);
    cout << "bool: " << byteSize << " byte" << endl;
    cout << "flase <-> true" << endl;
    cout << bitset<8>(b) << endl;

    long long *plonglong = &ll;
    int *pint = &i;
    short *pshort = &s;
    char *pchar = &c;
    bool *pbool = &b;

    cout << "pointer int " << sizeof(pint) << " byte" << endl;
    cout << "pointer char " << sizeof(pchar) << " byte" << endl;
    cout << "pointer bool " << sizeof(pbool) << " byte" << endl;

    valami v;
    valami *pvstruct = &v;
    valami &rstruct = v;

    cout << "struct " << sizeof(v) << " byte" << endl;
    cout << "pointer struct " << sizeof(pvstruct) << " byte" << endl;
    cout << "reference struct " << sizeof(rstruct) << " byte" << endl;
    cout << "pointer struct erteke " << pvstruct << endl;
    cout << "pointer int erteke " << pint << endl;
    cout << "pointer char erteke " << (void *)pchar << endl;

    return 0;
}
