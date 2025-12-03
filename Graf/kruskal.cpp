#include <iostream>
#include <fstream>

#define N 100

using namespace std;

struct edge
{
    int from;
    int to;
    int weight;
};

edge edges[N];
int edge_count;
int node_count;

void beOlvas(string fileName, edge edges[])
{
    ifstream f(fileName);
    if(!f)
    {
        cerr << "Hiba: nem sikerult megnyitni: " << fileName << endl;
        return;
    }

    int i = 0;
    f >> node_count;

    int from, to, weight;
    while(f >> from >> to >> weight)
    {
        edges[i].from = from;
        edges[i].to = to;
        edges[i].weight = weight;
        i++;
    }
    edge_count = i;
}

//Kiirja a graf ellistajat
void kiIr(edge edges[], int edge_count)
{
    cout << "Ellista:" << endl;
    for(int i = 0; i < edge_count; i++){
            cout << edges[i].from << "-";
            cout << edges[i].to << " (";
            cout << edges[i].weight << ")" << endl;
    }
}

void selectionSort(edge edges[], int edge_count)
{
    for(int i = 0; i < edge_count; i++)
    {
        int minIndex = i;
        for(int j = i + 1; j < edge_count; j++)
        {
            if(edges[j].weight < edges[minIndex].weight)
            {
                minIndex = j;
            }
        }
        if(i != minIndex)
        {
            edge tmp = edges[i];
            edges[i] = edges[minIndex];
            edges[minIndex] = tmp;
        }
    }
}

int kruskal(edge edges[], int edge_count, int node_count)
{
    cout << "Kruskal minimalis feszitofa:" << endl;
    selectionSort(edges, edge_count);

    int component[node_count];
    for(int i = 0; i < node_count; i++)
        component[i] = i;

    int chosen_edge_count = 0;
    int total_weight = 0;

    for(int i = 0; i < edge_count && chosen_edge_count < node_count - 1; i++)
    {
        int fromComponent = component[edges[i].from];
        int toComponent = component[edges[i].to];

        if(fromComponent != toComponent)
        {
            chosen_edge_count++;
            total_weight += edges[i].weight;

            // union
            for(int j = 0; j < node_count; j++)
                if(component[j] == toComponent)
                    component[j] = fromComponent;

            //Kiirasok opcionalisak...
            cout << "Kivalasztott el: ";
            cout << edges[i].from << "-";
            cout << edges[i].to << " (";
            cout << edges[i].weight << ")" << endl;

            cout << "Komponensek allapota:" << endl;
            for(int j = 0; j < node_count; j++)
                cout << component[j] << " ";
            cout << endl;
        }
    }
    return total_weight;
}

int main()
{
    beOlvas("graf.txt", edges);
    kiIr(edges, edge_count);
    int total_weight = kruskal(edges, edge_count, node_count);
    cout << endl << "Kruskal Total weight: " << total_weight << endl;
    return 0;
}
/*
9
0 1 4
0 2 3
0 3 2
1 3 5
1 4 1
2 3 6
2 5 2
3 5 3
3 6 7
4 6 4
4 7 6
5 6 5
5 8 7
6 8 3

6
0 1 4
0 2 2
1 2 1
1 3 5
2 3 8
2 4 10
3 4 2
3 5 6
4 5 3
*/
