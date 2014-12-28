//Author: a
//hiho24
#include<algorithm>
#include<cassert>
#include<cstdio>
#include<cmath>
#include<ctime>
#include<cstring>
using namespace std;

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#define N 100005
#define M 3000005
#define inf 1000000
using namespace std;
int src;
int dst;
int n ,m ,dis[N],Index;
struct e
{
       int v,w,next,dis;
       bool operator < (const e &a) const
       {
            return dis > a.dis;
       }
}edge[M];

int start[M];

bool vis[N];
e temp;
priority_queue<e> Q;
void add (int u,int v,int w)
{
     edge[Index].v = v;
     edge[Index].w = w;
     edge[Index].next = start[u];
     start[u] = Index ++;
	 swap(u,v);
	 edge[Index].v = v;
     edge[Index].w = w;
     edge[Index].next = start[u];
     start[u] = Index ++;
}

int dij ()
{
    while (!Q.empty()) Q.pop();
    for (int i = 1;i <= n;i ++) dis[i] = inf;
    dis[src] = 0;
    temp.v = src;
    temp.dis = 0;
    Q.push(temp);
    e tmp;
    while (!Q.empty())
    {
          temp = Q.top();
          Q.pop();
          if (vis[temp.v]) continue;
          vis[temp.v] = true;
          if (temp.v == dst) return dis[dst];
          for (int i = start[temp.v];i != -1;i = edge[i].next)
          {
              if (dis[edge[i].v] > dis[temp.v] + edge[i].w)
              {
                 dis[edge[i].v] = dis[temp.v] + edge[i].w;
                 tmp.v = edge[i].v;
                 tmp.dis = dis[edge[i].v];
                 Q.push(tmp);
              }
          }
    }
}

int main ()
{
    int u,v,w;
          scanf("%d%d%d%d",&n,&m,&src,&dst);
          Index = 0;
        //  if (n == 0) break;
          for (int i = 0;i <= n;i ++)
          {
              start[i] = -1;
              vis[i] = false;
          }
          while (m--)
          {
                scanf("%d%d%d",&u,&v,&w);
                add (u,v,w);
          }
          printf ("%d\n",dij());
return 0;
}

