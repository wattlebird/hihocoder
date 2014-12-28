//Author: IcY_
#include<cstdio>
#include<cstring>
#include<cctype>
#include<queue>
using namespace std;
const int maxn=1e5+10;
const int maxm=1e6+10;
const int inf=0x3f3f3f3f;
int n,m,s,t;
int head[maxn],cnt;
struct ty
{
    int v,w,next;
}arcs[maxm<<1];
void addarc(int u,int v,int w)
{
    arcs[cnt]=(ty){v,w,head[u]};
    head[u]=cnt++;
}
void read(int &x)
{
    char ch;
    x=0;
    while (!isdigit(ch=getchar()));
    do
    {
        x=x*10+ch-'0';
    }while (isdigit(ch=getchar()));
}
queue<int> q;
int d[maxn];
bool inq[maxn];
void spfa()
{
    memset(d,0x3f,sizeof(d[0])*(n+1));
    memset(inq,0,sizeof(inq[0])*(n+1));
    d[s]=0;
    q.push(s);inq[s]=1;
    while (!q.empty())
    {
        int u=q.front();q.pop();inq[u]=0;
        for (int k=head[u];k!=-1;k=arcs[k].next)
        {
            int v=arcs[k].v,w=arcs[k].w;
            if (d[v]>d[u]+w)
            {
                d[v]=d[u]+w;
                if (!inq[v]) q.push(v),inq[v]=1;
            }
        }
    }
}
int main()
{
    while (~scanf("%d%d%d%d",&n,&m,&s,&t))
    {
        memset(head,-1,sizeof(head[0])*(n+1));cnt=0;
        while (m--)
        {
            int u,v,w;
            read(u);read(v);read(w);
            addarc(u,v,w);
            addarc(v,u,w);
        }
        spfa();
        printf("%d\n",d[t]);
    }
    return 0;
}
