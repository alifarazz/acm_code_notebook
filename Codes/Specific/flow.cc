#include <bits/stdc++.h>
using namespace std;
#define MAXSIZE 502

#define LL long long

// s-> source, d -> sink, n = |V|, e = |E|
int n, e, s, d, c; // s--, d--

vector<int> graph[MAXSIZE];
LL capacity[MAXSIZE][MAXSIZE];
int parent[MAXSIZE];


inline int bfs(vector<int>& parent) {
    fill(begin(parent), end(parent), -1);
    parent[s] = -2;
    queue<pair<int, LL>> q;
    q.emplace(s, __LONG_LONG_MAX__);

    while (!q.empty()){
        int cur = q.front().first;
        auto flow = q.front().second;
        q.pop();
        
        for (auto v: graph[cur]) {
      if (parent[v] == -1 && capacity[cur][v]) {
        parent[v] = cur;
        LL new_flow = min(flow, capacity[cur][v]);
        if (v == d) return new_flow; // done
        q.emplace(v, new_flow);
      }
        }
    }
    return 0;
}

LL maxFlow(){
  LL flow{0};
  vector<int> parent(n);
  
  while(int new_flow = bfs(parent)) {
    flow += new_flow;
    int cur = d;
    for (int prev; cur != s; cur = prev) {
      prev = parent[cur];
      capacity[prev][cur] -= new_flow;
      capacity[cur][prev] += new_flow;
    }
  }
  return flow;
}

