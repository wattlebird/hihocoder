//Author: YYOne
#include <bits/stdc++.h>
using namespace std;
typedef map<int,int>::iterator it;
int main() {
    map<int,int> m;
    m[INT_MIN] = -1;
    m[INT_MAX] = -1;
    int n, x, y;
    scanf("%d%*d", &n);
    while(n--) {
        scanf("%d%d", &x, &y);
        it l = m.lower_bound(x);
        it r = m.upper_bound(y);
        it t = r; -- t;
        int p = t->second;
        for(it i=l; i!=r; ) m.erase(i++);
        m[x] = n; m[y] = p;
    }
    set<int> s;
    for(it i=m.begin(); i!=m.end(); ++i) s.insert(i->second);
    printf("%d\n", s.size() - 1);
    return 0;
}
