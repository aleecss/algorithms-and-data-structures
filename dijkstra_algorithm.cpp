/**
Given an undirected weighted graph with n vertices and m edges, find the minimum cost road from x to all vertices in that graph.

Limits:
-> 1 <= x, y <= n <= 100.000
-> 1 <= m <= 250.000
**/

#include <iostream>
#include <queue>
#include <vector>
#include <bitset>

using namespace std;

const int INF = 0x3f3f3f3f, dim = 100000;

int n, m, x, y, w[dim + 1];

vector < pair < int, int> > G[dim + 1];

bitset < dim + 1 > f;

priority_queue < pair < int, int >,
                 vector < pair < int, int > >,
                 greater < pair < int, int > > > heap;

int main() {
    ios_base :: sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> x;

    for (int i = 1, u, v, t; i <= m; ++ i) {
        cin >> u >> v >> t;
        G[u].push_back({t, v});
        G[v].push_back({t, u});
    }

    for (int i = 1; i <= n; ++ i)
        w[i] = INF;

    w[x] = 0;

    for (int i = 0; i < G[x].size(); ++ i) {
        int cost = G[x][i].first, node = G[x][i].second;

        heap.push({cost, node});
    }

    while (!heap.empty()) {
        int t = heap.top().second;

        if (!f[t]) {
            f[t] = 1;

            for (int i = 0; i < G[t].size(); ++ i) {
                int cost = G[t][i].first, node = G[t][i].second;

                w[t] = min(w[t], w[node] + cost);
            }

            for (int i = 0; i < G[t].size(); ++ i) {
                int cost = G[t][i].first, node = G[t][i].second;

                if (!f[node])
                    heap.push({w[t] + cost, node});
            }
        }

        heap.pop();
    }

    for (int y = 1; y <= n; ++ y)
        if (w[y] == INF)
            cout << "-1" << " ";
        else
            cout << w[y] << " ";

    return 0;
}
