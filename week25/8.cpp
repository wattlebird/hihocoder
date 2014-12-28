//Author: zzyzzy12
#include<iostream>
#include<stdio.h>
#include<cstring>
#include<queue>
#define MAXN 100002
using namespace std;
struct Edge
{
        int v,l,next;
}edge[MAXN*20];
int _next[MAXN],En,dis[MAXN];
queue<int> Q;
bool inQ[MAXN];
void addedge(int u,int v,int l)
{
        edge[++En].next=_next[u],_next[u]=En;
        edge[En].v=v,edge[En].l=l;
}
int SPFA(int s,int t)
{
        int u,v,l,k;
        memset(inQ,false,sizeof(inQ));
        memset(dis,0x7f,sizeof(dis));
        Q.push(s),dis[s]=0;
        while (Q.size())
        {
                u=Q.front(),inQ[u]=false,Q.pop();
                for (k=_next[u];k;k=edge[k].next)
                {
                         v=edge[k].v,l=edge[k].l;
                         if (dis[v]-dis[u]<=l) continue;
                         dis[v]=dis[u]+l;
                         if (!inQ[v])
                             Q.push(v),inQ[v]=true;
                }
        }
        return dis[t];
}
int main()
{
        int n,m,s,t,u,v,l;
        scanf("%d%d%d%d",&n,&m,&s,&t);
        memset(_next,0,sizeof(_next)),En=0;
        while (m--)
        {
                 scanf("%d%d%d",&u,&v,&l);
                 addedge(u,v,l),addedge(v,u,l);
        }
        printf("%d\n",SPFA(s,t));
        return 0;
}
