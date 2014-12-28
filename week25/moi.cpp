#include <cstdio>
#include <map>
#include <queue>
#include <vector>

typedef int vertice_no_t;
typedef int edge_weight_t;

typedef struct{
    vertice_no_t nv;
    int ne;
    std::map<vertice_no_t, edge_weight_t> m[100001];
}graph_t;

graph_t G;
std::map<vertice_no_t, edge_weight_t> dist;
std::queue<vertice_no_t> Q;

int main(){
    int ne, nv, s, d;
#ifndef ONLINE_JUDGE
    std::freopen("testcase","r",stdin);
#endif
    scanf("%d%d%d%d",&nv,&ne,&s,&d);
    std::vector<bool> qmask(nv+1,false);
    G.nv=nv, G.ne=0;
    vertice_no_t v1, v2;
    edge_weight_t w;
    for(int i=0; i!=ne; i++){
        scanf("%d%d%d",&v1,&v2,&w);
        if(G.m[v1].count(v2) && G.m[v1][v2]<w) continue;
        G.m[v1][v2]=w;
        G.m[v2][v1]=w;
        G.ne++;
    }
    Q.push(s);
    dist[s]=0;

    typedef std::map<vertice_no_t, edge_weight_t>::const_iterator mptr;
    while(!Q.empty()){
        vertice_no_t cur = Q.front();
        Q.pop();
        qmask[cur]=false;
        for(mptr itr=G.m[cur].begin(); itr!=G.m[cur].end(); itr++){
            bool b=false;
            if(dist.count(itr->first)){
                if(dist[itr->first]>dist[cur]+itr->second){
                    b=true;
                    dist[itr->first]=dist[cur]+itr->second;
                }
            }else{
                b=true;
                dist[itr->first]=dist[cur]+itr->second;
            }
            if(b){
                if(!qmask[itr->first]){
                    Q.push(itr->first);
                    qmask[itr->first]=true;
                }
            }
        }
    }
    printf("%d\n",dist[d]);
    return 0;
}
