//Author: jiangxiong
#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#include<cstring>

using namespace std;

const int N =100100;

struct node{
    int v,l;
    bool operator < (const node &x) const{
        return l>x.l;
    }
};

struct edge{
    node x;
    int next;
}list[N*10];

int  head[N];
priority_queue<node> pq;
int len[N];

int main() {
    int n,m,s,t;
    int cnt=0;
    while(scanf("%d%d%d%d",&n,&m,&s,&t)!=EOF) {
        for(int i=0;i<=n;i++) head[i]=-1;
        for(int i=0;i<m;i++) {
            int u,v,l;
            scanf("%d%d%d",&u,&v,&l);
            node e1,e2;
            e1.v=v,e1.l=l;
            e2.v=u,e2.l=l;
            list[cnt].x=e1;
            list[cnt].next=head[u];
            head[u]=cnt;
            cnt++;
            list[cnt].x=e2;
            list[cnt].next=head[v];
            head[v]=cnt;
            cnt++;
        }
        memset(len,0x1f,sizeof(len));
        while(!pq.empty()) pq.pop();
        node x;
        x.v=s,x.l=0;
        len[s]=0;
        pq.push(x);
        while(!pq.empty()) {
            x = pq.top();
            pq.pop();
            if(x.v==t) {
                printf("%d\n",x.l);
                break;
            }
            int cur=head[x.v];
            for(;cur!=-1;cur=list[cur].next) {
                node nx=x;
                node e = list[cur].x;
                nx.l=x.l+e.l;
                nx.v=e.v;
                if(nx.l<len[nx.v]) {
                    len[nx.v]=nx.l;
                    pq.push(nx);
                }
            }
        }
    }
    return 0;
}
