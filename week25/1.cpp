//Author: n+e
#include<cstdio>
#include<cstring>
int aa;char ch;int F(){
    while(ch=getchar(),ch<'0'||ch>'9');aa=ch-48;
    while(ch=getchar(),ch>='0'&&ch<='9')aa=aa*10+ch-48;return aa;
}
#define N 100010
int n,m,s,t,et,la[N],d[N],q[1<<23],l,r,x,y,v,i;bool in[N];
struct E{int to,v,nxt;}e[1<<21];
#define add(x,y,v) e[++et]=(E){y,v,la[x]},la[x]=et
int main(){
    for(n=F(),m=F(),s=F(),t=F();m--;x=F(),y=F(),v=F(),add(x,y,v),add(y,x,v));
    for(memset(d,60,sizeof(d)),q[0]=s,in[s]=1,d[s]=0;l<=r;in[q[l++]]=0)
    for(i=la[q[l]];i;i=e[i].nxt)if(d[e[i].to]>d[q[l]]+e[i].v)
    d[e[i].to]=d[q[l]]+e[i].v,!in[e[i].to]?in[q[++r]=e[i].to]=1:1;
    printf("%d",d[t]);
}
