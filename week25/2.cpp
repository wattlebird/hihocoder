//Author: LiaoPengyu
#include <cstdio>
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
int const N = 1e5 + 10, M = 1e6 + 10, inf = 1e9;
typedef pair<int, int> pii;
int u, v, w, cnt, h[N], n, m, s, t;
struct Edge {
    int t, n, l;
} g[M << 1];
void insert(int f, int t, int l) {
    g[cnt].t = t;
    g[cnt].l = l;
    g[cnt].n = h[f];
    h[f] = cnt++;
    g[cnt].t = f;
    g[cnt].l = l;
    g[cnt].n = h[t];
    h[t] = cnt++;
}
bool relax(int &a, int b) { return a > b ? (a = b, true) : false; }
int disj(int s, int t) {
    priority_queue<pii> que;
    int dis[N], d; fill(dis, dis + n + 1, inf);
    for (que.push(pii(dis[s] = 0, s)); !que.empty();) {
        s = que.top().second, d = -que.top().first; que.pop();
        if (d > dis[s]) continue;
        if (s == t) return d;
        for (int i = h[s], t; ~i; i = g[i].n)
            if (relax(dis[t = g[i].t], d + g[i].l))
                que.push(pii(-dis[t], t));
    }
    return dis[t];
}
int main() {
    cin >> n >> m >> s >> t;
    memset(h, -1, sizeof(h));
    for (int i = 0; i < m; i++) {
        scanf("%d%d%d", &u, &v, &w);
        insert(u, v, w);
    }
    cout << disj(s, t) << endl;
    return 0;
}
