//Author: zhjou
#include <iostream>
#include <cstdio>
using namespace std;
#define MM 2000008
#define INF 0x3fffffff
int N,M,s,t;
struct node{
	int to;
	int w;
	int next;
}e[MM];
struct HH{
		int to;
		int w;
	};
struct Heap{
	HH H[MM],tmp;
	int len;
	Heap(){
		len=0;
	}
  void	min_heap(int i){
		int l=i<<1;
		int r=i<<1|1;
		int mm=i;
		if(l<=len&&H[l].w<H[i].w)
			mm=l;
		if(r<=len&&H[r].w<H[mm].w)
			mm=r;
		if(i!=mm){
			tmp=H[mm];
			H[mm]=H[i];
			H[i]=tmp;
			min_heap(mm);
		}
	}
	void	insert(HH &ht){
		len++;
		H[len]=ht;
		int i=len;
		while(i>1&&H[i>>1].w>H[i].w){
			tmp=H[i>>1];
			H[i>>1]=H[i];
			H[i]=tmp;
			i>>=1;
		}
	}
	HH extract(){
		tmp=H[len];
		H[len]=H[1];
		H[1]=tmp;
		len--;
		min_heap(1);
		return H[len+1];
		}
};
int list[100010];
bool f[100010];
void Dijstra(){
	HH tmp,tx;
	tmp.to=s;
	tmp.w=0;
	Heap heap;
	heap.insert(tmp);
	while(heap.len){
		tmp=heap.extract();
		if(tmp.to==t){printf("%d\n",tmp.w); break;}
		f[tmp.to]=1;
		for(int i=list[tmp.to];i;i=e[i].next){
			int to=e[i].to;
			if(!f[to]){
				tx.w=tmp.w+e[i].w;
				tx.to=to;
				heap.insert(tx);
			}
		}
	}
}
int main(int argc, char** argv) {
	int st,to,w;
	scanf("%d %d %d %d",&N,&M,&s,&t);
	for(int i=1;i<=2*M;){
		scanf("%d %d %d",&st,&to,&w);
		e[i].to=to;e[i].w=w;
		e[i].next=list[st];
		list[st]=i++;
		e[i].to=st;e[i].w=w;
		e[i].next=list[to];
		list[to]=i++;
	}
	Dijstra();
	return 0;
}
