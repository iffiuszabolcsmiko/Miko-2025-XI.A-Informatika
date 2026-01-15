#include <iostream>

using namespace std;

int maxHeap[1000] = {0};
int n = 0;

void csere(int &a, int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
}

void maxHeapifyUp(int i)
{
    if(i > 1 && maxHeap[i] > maxHeap[i / 2])
    {
        csere(maxHeap[i], maxHeap[i / 2]);
        maxHeapifyUp(i / 2);
    }
}

void maxHeapifyDown(int i)
{
    int left = 2 * i;
    int right = 2 * i + 1;
    int largest = i;

    if(left <= n && maxHeap[left] > maxHeap[largest])
        largest = left;

    if(right <= n && maxHeap[right] > maxHeap[largest])
        largest = right

    if(largest != i)
    {
        csere(maxHeap[i], maxHeap[largest]);
        maxHeapifyDown(largest);
    }
}

void heapInsert(int x)
{
    n++;
    maxHeap[n] = x;
    maxHeapifyUp(n);
}

int heapExtractRoot()
{
    csere(maxHeap[1], maxHeap[n]);
    n--;
    maxHeapifyDown(1);
    return maxHeap[n];
}

void kiir()
{
    for(int i = 1; i <= n; i++)
        cout << maxHeap[i] << " ";
    cout << endl;
}

void feltolt()
{
    for(int i = 1; i <= 10; i++)
        heapInsert(i);
}

int main()
{
    feltolt();
    kiir();
    return 0;
}
