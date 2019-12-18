#include<iostream>
#include<utility>
#include<algorithm>
using namespace std;

typedef pair<int, int>             PII;
typedef pair<int, pair<int, int> > EDGE;

constexpr int maxn = 1e4, maxm = 1e4;

EDGE edge[maxm];
int n, m, mcstSize, mcstCost, rankk[maxn], par[maxn];

int ds_find(int u){
    if(par[u] == u) return u;
    return par[u] = ds_find(par[u]);
}

void ds_union(int u, int v){
    int uu = ds_find(u),vv = ds_find(v);
    if(rankk[uu] == rankk[vv]){
        ++rankk[uu];
        par[uu] = vv;
    }
    else if(rankk[uu] < rankk[vv])
        par[vv] = uu;
    else // same height, select one at random
        par[uu] = vv;
}

void kruskal(){
    generate(par, par+n, [n=0]() mutable {return n++;});
    sort(edge, edge+m);
    for(int i=0; i<m && mcstSize<n-1; i++){
        int u = edge[i].second.first, v = edge[i].second.second;
        if(ds_find(u) != ds_find(v)){
            ds_union(u, v);
            mcstCost += edge[i].first;
            ++mcstSize;
        }
    }
}

int main()
{
    cin >> n>> m;
    for(int i=0; i<m; i++){
        cin >> edge[i].second.first
            >> edge[i].second.second
            >> edge[i].first;
        edge[i].second.first--,edge[i].second.second--;
    }


    kruskal();

    cout << mcstCost << endl;
}