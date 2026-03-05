#include <iostream>

using namespace std;

template <typename T>
T nagyobb(T a, T b)
{
    if(a >= b)
        return a;
    else
        return b;
}

int main()
{
    int a = 5, b = 2;
    cout << nagyobb<int>(a, b) << endl;
    float f1 = 5.5, f2 = 2.2;
    cout << nagyobb<float>(f1, f2) << endl;
    double d1 = 5.5, d2 = 2.2;
    cout << nagyobb<double>(d1, d2) << endl;
    char c1 = 'a', c2 = 'b';
    cout << nagyobb<char>(c1, c2) << endl;
    return 0;
}
