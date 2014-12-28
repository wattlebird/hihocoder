//Author: hjqlty
#include <iostream>
#include <cstring>
#include <cstdio>
#include <queue>
using namespace std;
#define Maxn 105000
#define Maxm 1000500
#define INF 0x3f3f3f3f
struct Edge{
	int to;int len;
	int next;
}edge[Maxm*2];
int en,head[Maxn];
inline void add_edge(int u,int v,int len){
	edge[en].to=v;edge[en].len=len;edge[en].next=head[u];head[u]=en++;
}
int dis[Maxn];
bool vis[Maxn];
int spfa(int src,int des){
	memset(vis,false,sizeof(vis));
	memset(dis,0x3f,sizeof(dis));
	queue<int> que;
	que.push(src);vis[src]=true;dis[src]=0;
	while (!que.empty()){
		int u=que.front();que.pop();vis[u]=false;
		for (int p=head[u];~p;p=edge[p].next){
			int v=edge[p].to,len=edge[p].len;
			if (dis[v]>dis[u]+len){
				dis[v]=dis[u]+len;
				if (!vis[v]){
					que.push(v);
					vis[v]=true;
				}
			}
		}
	}
	if (dis[des]>=INF) return -1;
	else return dis[des];
}

int main(){
	int n,m;
	int src,des;
	while (~scanf("%d%d",&n,&m)){
		scanf("%d%d",&src,&des);
		en=0;
		fill(head,head+n+1,-1);
		int u,v;int len;
		for (int i=1;i<=m;i++){
			scanf("%d%d%d",&u,&v,&len);
			add_edge(u,v,len);
			add_edge(v,u,len);
		}
		printf("%d\n",spfa(src,des));
	}
	return 0;
}
