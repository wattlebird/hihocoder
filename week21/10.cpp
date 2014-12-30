//Author:  coolboy 
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

#define lson o<<1
#define rson o<<1|1
const int maxn = 1e5 + 10;
int setv[maxn<<2];
int x[maxn];
int y[maxn];
int pos[maxn<<2];
int n, L;
int Bin(int key){
    int l = 1, r = n;
    while(l <= r){
        int m = (l + r)>>1;
        if(pos[m] == key)return m;
        if(pos[m] < key) l = m + 1;
        else r = m - 1;
    }
    return -1;
}

void build_tree(int o, int l, int r){
    int m = (l + r)>>1;
    setv[o] = 0;
    if(l == r - 1)return ;
    build_tree(lson, l, m);
    build_tree(rson, m, r);
}

void pushdown(int o, int l, int r){
    if(setv[o]){
        setv[lson] = setv[rson] = setv[o];
        setv[o] = 0;
    }
}
void pushup(int o, int l, int r){
    if(setv[lson] == setv[rson]){
        setv[o] = setv[rson];
    }
}
void update(int x, int y, int c, int o, int l, int r){
    int m = (l + r)>>1;
    if(x == l && y == r){
        setv[o] = c;
        return ;
    }
    if(l == r - 1)return ;
    pushdown(o, l, r);
    if(y <= m)update(x, y, c, lson, l, m);
    else if(x >= m)update(x, y, c, rson, m, r);
    else update(x, m, c, lson, l, m), update(m, y, c, rson, m, r);
    //pushup(o, l, r);
}

set<int>v;
void query(int o, int l, int r, int x, int y){
   // if(x == l && y == r){
        if(setv[o]){
            v.insert(setv[o]); return ;
        }
   // }
    int m = (l + r)>>1;
    if(l == r - 1)return ;
    if(y <= m)query(lson, l, m, x, y);
    else if(x >= m)query(rson, m, r, x, y);
    else query(lson, l, m, x, m), query(rson, m, r, m, y);
}
int main(){
  //  freopen("in", "r", stdin);
    v.clear();
    int k = 0;
    scanf("%d%d", &n, &L);
    int m = n;
    for(int i = 0; i < n; ++i){
        scanf("%d%d", &x[i], &y[i]);
        if(x[i] > y[i])swap(x[i], y[i]);
        if(y[i]>L)y[i] = L;
        pos[++k] = x[i];
        pos[++k] = y[i];
    }
    sort(pos + 1, pos + 2 * n + 1);
    n = unique(pos + 1, pos + 2 * n + 1) - (pos + 1);
//    for(int i = 1; i <= n; ++i){
//        printf("%d ", pos[i]);
//    }*/
//    cout<<n<<endl;
    build_tree(1, 1, n);
    int a, b;
    for(int i = 0; i < m; ++i){
        a = Bin(x[i]), b = Bin(y[i]);
      //  cout<<a<<" "<<b<<endl;
        update(a, b, i + 1, 1, 1, n);
    }
    query(1, 1, n, 1, n);
    int s = v.size();

   /* set<int>::iterator it;
    it = v.begin();
    for(; it != v.end(); ++it){
        printf("%d ", *it);
    }
    printf("\n");*/
    printf("%d\n", s);
    return 0;
}
