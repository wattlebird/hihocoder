//Author:  Rohan 
#include "stdio.h"
#include "math.h"
#include "stdlib.h"
#include "memory.h"

#define NUM 100010
int N=0;

typedef struct Node
{
	int l;
	int r;
	int val;
	int flag;
}Node;

Node tree[4*NUM]={0, 0, 0, 0};

long long s[2*NUM]={0};
int ind[2*NUM]={0};
int sq[2*NUM]={0};

int res=0;

int Partition(int low, int high)	//类似半导体中一个空穴转移一个电子
{											//取第一个元素把数组分成小于和大于两部分
	// 随机选取中间数
	int p=rand()%(high-low+1)+low;

	long long temp1=s[p];
	s[p]=s[low];
	s[low]=temp1;

	int temp2=ind[p];
	ind[p]=ind[low];
	ind[low]=temp2;

	long long pivotkey=s[low];
	int val=ind[low];
	while (low<high)
	{
		while(low<high && s[high]>=pivotkey)
			high--;
		s[low]=s[high];
		ind[low]=ind[high];
		while(low<high && s[low]<=pivotkey)
			low++;
		s[high]=s[low];
		ind[high]=ind[low];
	}
	s[low]=pivotkey;
	ind[low]=val;
	return low;
}

void Qsort(int low, int high)
{
	if (low<high)
	{
		int pivotloc=Partition(low, high);
		Qsort(low, pivotloc-1);
		Qsort(pivotloc+1, high);
		return;
	}
}


void set_sum(int root, int l, int r, int val)
{

	if (tree[root].r==r && tree[root].l==l)
	{
		tree[root].val=val;
		tree[root].flag=1;
		return;
	}

	if(tree[root].flag==1)
	{
		tree[root].flag=0;
		if(2*root<2*N-1)
		{
			tree[2*root].flag=1;
			tree[2*root+1].flag=1;

			tree[2*root].val=tree[root].val;
			tree[2*root+1].val=tree[root].val;
		}
	}

	int lr=tree[2*root].r;
	if (lr<r && lr>l)
	{
		set_sum(2*root, l, lr, val);
		set_sum(2*root+1, lr, r, val);
	}
	else if (lr<=l)
	{
		set_sum(2*root+1, l, r, val);
	}
	else if(lr>=r)
	{
		set_sum(2*root, l, r, val);
	}
	return;
}

void travel(int root)
{
	if(root>2*N-1)
		return;
	
	if(tree[root].flag==1)
	{
		sq[tree[root].val]=1;
		return;
	}

	travel(2*root);
	travel(2*root+1);
	return;
}

int main()
{
#ifdef DEBUG
	freopen("in.txt", "r", stdin);
#endif

	int i=0;
	long long L=0;
	int n=0;
	scanf("%d %ld", &n, &L);
	
	for (i=0; i<n; i++)
	{
		scanf("%ld %ld", &s[2*i], &s[2*i+1]);
		ind[2*i]=i;
		ind[2*i+1]=i;
	}

	Qsort(0, 2*n-1);

	sq[2*ind[0]]=1;
	N=1;
	for (i=1; i<2*n; i++)
	{
		if (s[i]==s[i-1])
		{
			if (sq[2*ind[i]]==0)
				sq[2*ind[i]]=N;
			else
				sq[2*ind[i]+1]=N;
		}
		else
		{
			N++;
			if (sq[2*ind[i]]==0)
				sq[2*ind[i]]=N;
			else
				sq[2*ind[i]+1]=N;
		}
	}

	N=N-1;
	int h=(int)(log10((float)(2*N-1))/log10(2.0));

	int count=1;
	for (i=(1<<h); i<=2*N-1; i++)
	{
		tree[i].l=count;
		tree[i].r=++count;
	}
	for (i=N; count<=N; i++)
	{
		tree[i].l=count;
		tree[i].r=++count;
	}

	for (i=N-1; i>=1; i--)
	{
		int l=2*i, r=l+1;
		tree[i].val=tree[l].val+tree[r].val;
		tree[i].l=tree[l].l;
		tree[i].r=tree[r].r;
	}

	for (i=0; i<n; i++)
		set_sum(1, sq[2*i], sq[2*i+1], i);

	memset(sq, 0, 2*NUM*sizeof(int));
	travel(1);
	for (i=0; i<n; i++)
	{
		res=res+sq[i];
	}
	printf("%d\n", res);

	return 0;
}