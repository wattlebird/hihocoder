//Author: zjsxzy
#include <map>
#include <set>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <bitset>
#include <vector>
#include <cstdio>
#include <string>
#include <cassert>
#include <climits>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define PB push_back
#define MP make_pair
#define SZ(v) ((int)(v).size())
#define abs(x) ((x) > 0 ? (x) : -(x))
#define FOREACH(e,x) for(__typeof(x.begin()) e=x.begin();e!=x.end();++e)
typedef long long LL;

/*
 * SPFA
 */
const int maxn = 100000 + 5;
const int maxm = 1000000 + 5;
const int inf = 1000000000;
struct Edge {
	int v, next, w;
};
struct Graph {

	int N, M;
	Edge edge[maxm * 2];
	int num, Head[maxn];
	int dis[maxn], vis[maxn];

	Graph() {}

	void init(int N, int M) {
		this->N = N;
		this->M = M;
		num = 0;
		memset(Head, -1, sizeof(Head));
	}

	void addEdge(int u, int v, int w) {
		edge[num].v = v;
		edge[num].w = w;
		edge[num].next = Head[u];
		Head[u] = num++;
	}

	int SPFA(int st, int ed) {
		for (int i = 1; i <= N; i++) {
			dis[i] = inf;
			vis[i] = false;
		}
		vis[st] = true;
		dis[st] = 0;
		queue<int> Q;
		Q.push(st);
		while (!Q.empty()) {
			int u = Q.front();
			Q.pop();
			vis[u] = false;
			for (int i = Head[u]; i != -1; i = edge[i].next) {
				int v = edge[i].v;
				if (dis[u] + edge[i].w < dis[v]) {
					dis[v] = dis[u] + edge[i].w;
					if (!vis[v]) {
						vis[v] = true;
						Q.push(v);
					}
				}
			}
		}
		return dis[ed];
	}
}g;
int main() {
#ifndef ONLINE_JUDGE
	freopen("in.txt", "r", stdin);
#endif
    int n, m, S, T;
    scanf("%d%d%d%d", &n, &m, &S, &T);
	g.init(n, m);
	for (int i = 0; i < m; i++) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);
		g.addEdge(a, b, c);
		g.addEdge(b, a, c);
	}
	printf("%d\n", g.SPFA(S, T));
	return 0;
}

