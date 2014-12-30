//Author: n+e
#include<cstdio>
#include<algorithm>
int aa;char ch;int F(){
	while(ch=getchar(),ch<'0'||ch>'9');aa=ch-'0';
	while(ch=getchar(),ch>='0'&&ch<='9')aa=aa*10+ch-'0';return aa;
}
#define N 100010
int n,a[N],b[N],i,j,x,y,cnt,t[N<<4],vis[N];
struct D{int x,n;}d[N<<1];
bool cmp(const D&i,const D&j){return i.x<j.x;}
void update(int o,int l,int r)
{
	if(x<=l&&r<=y)
	{
		t[o]=i;return;
	}
	if(t[o])t[o<<1]=t[o<<1|1]=t[o],t[o]=0;
	int mid=l+r>>1;
	if(x<mid)update(o<<1,l,mid);
	if(mid<y)update(o<<1|1,mid,r);
}
void pd(int o,int l,int r)
{
	if(l+1==r){vis[t[o]]=1;return;}
	if(t[o])t[o<<1]=t[o<<1|1]=t[o],t[o]=0;
	int mid=l+r>>1;pd(o<<1,l,mid);pd(o<<1|1,mid,r);	
}
int main()
{
	for(n=F(),F(),i=1;i<=n;i++)
	d[++x]=(D){F(),i},d[++x]=(D){F(),i+n};
	std::sort(d+1,d+1+x,cmp);
	for(i=cnt=1;i<=x;i++)
	{
		if(d[i].n>n)b[d[i].n-n]=cnt;
		else a[d[i].n]=cnt;
		if(d[i].x!=d[i+1].x)cnt++;
	}
	for(i=1;i<=n;i++)x=a[i],y=b[i],update(1,1,cnt);
	for(pd(1,1,cnt),i=1,j=0;i<=n;i++)if(vis[i])j++;printf("%d\n",j);
} 
