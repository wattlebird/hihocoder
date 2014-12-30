//Author: kphmd
#include <algorithm>
#include <cstdio>

using namespace std;

int rd() {
	int r=0;char c=0;while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9'){r=(r<<3)+(r<<1)+c-'0';c=getchar();}
	return r;
}

const int MN = 1<<19;

int rg[MN],rk[MN];
struct {
	int a,b,c;
} trie[MN]={0};
int tsz = 1;

void add(int x) {
	static int i=0;
	int hd = 0;
	while(x) {
		if(x&1) {
			if(trie[hd].b==0) trie[hd].b = tsz++;
			hd = trie[hd].b;
		} else {
			if(trie[hd].a==0) trie[hd].a = tsz++;
			hd = trie[hd].a;
		}
		x>>=1;
	}
	trie[hd].c = ++i;
}

int get(int x) {
	int hd = 0;
	while(x) {
		if(x&1) {
			if(trie[hd].b==0) printf("err");
			hd = trie[hd].b;
		} else {
			if(trie[hd].a==0) printf("err");
			hd = trie[hd].a;
		}
		x>>=1;
	}
	return trie[hd].c;
}

struct {
	int id,lazyTag;
} tr[MN]={0};

#define L(i) ((i<<dep))
#define R(i) ((i<<dep)+(1<<dep)-1)

void modify(int x,int y,int z,int dep,int i) {
	if(L(i)==x && R(i)==y) {
		tr[i].id = z;
		tr[i].lazyTag = 1;
		return;
	}
	
	int l,r; l = (i<<1); r = l+1;
	if(tr[i].lazyTag) {
		tr[l].id=tr[i].id;tr[l].lazyTag=1;
		tr[r].id=tr[i].id;tr[r].lazyTag=1;
		tr[i].lazyTag = 0;
	}
	
	dep--;
	if(x<=R(l)) modify(x,min(y,R(l)),z,dep,l);
	if(y>=L(r)) modify(max(x,L(r)),y,z,dep,r);
}

int query(int x,int y,int dep,int i) {
	if(L(i)==x&&R(i)==y) return tr[i].id;
	
	int l,r; l = (i<<1); r = l+1;
	if(tr[i].lazyTag) {
		tr[l].id=tr[i].id;tr[l].lazyTag=1;
		tr[r].id=tr[i].id;tr[r].lazyTag=1;
		tr[i].lazyTag = 0;
	}
	
	dep--; int ans = 0;
	if(x<=R(l)) ans = query(x,min(y,R(l)),dep,l);
	if(y>=L(r)) ans = query(max(x,L(r)),y,dep,r);
	return ans;
}

int main()
{
	int N,L;
	N = rd()<<1; L = rd();
	for(int i = 0; i < N; i++) rg[i]=rd();
	for(int i = 0; i < N; i++) rk[i]=rg[i];
	sort(rk,rk+N); add(rk[0]);
	
	int A=0,M=1,dep=0;
	for(int i = 1,j = 0; i < N; i++) if(rk[i]!=rk[j]) {
		rk[++j] = rk[i]; add(rk[i]); M = j+1;
	}
	for(A=1,dep=0;A<M;A<<=1,dep++);
	for(int i = 0; i < N; i++) rg[i] = get(rg[i])-1;
	for(int i = 0; i < N; i+=2) modify(rg[i]+A,rg[i+1]+A-1,i+1,dep,1);
	for(int i = 0; i < M; i++) rk[i] = query(i+A,i+A,dep,1);
	
	sort(rk,rk+M); int ans=0;
	for(int i = 1,j = 0; i < M; i++) if(rk[i]!=rk[j]) {
		rk[++j] = rk[i]; ans = j;
	}
	ans++;
	if(rk[0]==0) ans--;
	printf("%d\n",ans);
	
	return 0;
}

