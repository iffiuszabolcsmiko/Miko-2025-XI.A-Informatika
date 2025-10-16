#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stack>

using namespace std;

short N;  // csucsok szama
short K;  // start
int M;    // elek szama

vector<vector<short>> graf;
vector<vector<short>> revGraf;  //graf forditott iranyu elekkel

void beolvas(ifstream &in){
    in >> N >> M >> K;

    //1 tol indexelem mert ugy vannak megadva a bemenetben
    graf.assign(N + 1, vector<short>()); // letrehozza az N darab ures vektort
    revGraf.assign(N + 1, vector<short>()); // letrehozza az N darab ures vektort

    for(int i = 0; i < M; i++) {
        short a, b;
        in >> a >> b;
        graf[a].push_back(b); // iranyitott el: a -> b
        revGraf[b].push_back(a); // iranyitott el: b -> a
    }
}

void kiir(vector<vector<short>> &g){
    cout << "Graf tartalma:" << endl;

    for(short i = 1; i <= N; i++){
        cout << i << ": ";
        for(short szomszed : g[i])
            cout << szomszed << " ";
        cout << endl;
    }
}

bool visited[10001] = {0};
bool revVisited[10001] = {0};

void dfs(vector<vector<short>> &g, bool v[]){
    stack<short> verem;
    verem.push(K);
    while(!verem.empty()){
        short u = verem.top();
        verem.pop();
        if(!v[u]){
            v[u] = true;
            for(short i : g[u])
                if(!v[i]) verem.push(i);
        }
    }
}

void kiirVisited(bool v[]){
    for(int i = 1; i <= N; i++)
        if(v[i]) cout << i << " ";
    cout << endl;
}

//visitedben lesznek azok a csomopontok ahova el lehet jutni es vissza es lehet terni K-ba
void intersect(){
    for(int i = 1; i <= N; i++)
        visited[i] = visited[i] && revVisited[i];
}

void nullaz(bool v[])
{
    for(int i = 1; i <=N; i++) v[i] = 0;
}

//visitedben levo csomopontok leszarmazottai a revVisitedben lesznek
void leszarmazottak(){
    nullaz(revVisited);
    for(int i = 1; i <= N; i++)
        if(visited[i])
            for(short j : graf[i])
                revVisited[j] = true;
}

int szamol(){
    int k = 0;
    for(int i = 1; i <= N; i++)
        if(revVisited[i]) k++;
    return k;
}

int main()
{
    ifstream f("bemenet.txt");
    if (!f.is_open()) {
        cerr << "Error opening file";
        return 1;
    }

    beolvas(f);   // f vagy cin
    f.close();
    //kiir(graf);

    //cout << K <<"-bol elerheto csomopontok" << endl;
    dfs(graf, visited);
    //kiirVisited(visited);

    //cout << K <<" elerheto ezekbol a csomopontokbol" << endl;
    dfs(revGraf, revVisited);
    //kiirVisited(revVisited);

    //cout << "el lehet jutni es vissza is lehet jonni " << K << "-ba" << endl;
    intersect();
    //kiirVisited(visited);

    //cout << "Megoldas: " << endl;
    leszarmazottak();
    revVisited[K] = 0;  // a kezdo csucs nem szerepelhet a megoldasban
    cout << szamol() << endl;
    kiirVisited(revVisited);
    return 0;
}
