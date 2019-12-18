#include <bits/stdc++.h>
using namespace std;
#define MaxSize 10001

vector <int> graph[MaxSize];
bool visited[MaxSize];
vector<int> art_point;
int low[MaxSize],disc[MaxSize],parent[MaxSize];
int timeii = 0;

void dfs_art_point(int v) {
    int ch = 0; visited[v] = true;
    disc[v] = low[v] = ++timeii;
    for (auto c: graph[v]) {
        if (!visited[c]) {
            ch++;
            parent[c] = v;
            dfs_art_point(c);
            low[v] = min(low[c], low[v]);

            if (parent[v] == -1 && ch > 1)art_point.push_back(v);
            if (parent[v] != -1 && low[c]>=disc[v])art_point.push_back(v);
        }
        else if (c != parent[v])
            low[v] = min(low[v], disc[c]);
    }
}

int main() {
    int n, m; cin >> n >> m;

    fill(parent, parent+n+2, -1);
    fill(disc, disc+n+2, -1);
    fill(low, low+n+2, -1);

    for (int j = 0;j<m; j++) {
        int a, b; cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    for (int j = 1; j <= n; j++)
        if (!visited[j])dfs_art_point(j);
    for(auto a: art_point)cout << a << " ";
}