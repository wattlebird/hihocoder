//Author:  zhoutongsjtu 
#include <stdio.h>
#include <algorithm>

using namespace std;
const int INF = 100000+10;
int N,L,index;
bool poster[INF];

struct Interval
{
	int left;
	int right;
} intervals[INF];

struct Point
{
	int num;
	int idx;
} points[INF<<1];

struct Node
{
	int left;
	int right;
	int set;
	//int sum;
} nodes[INF<<2];

void build(int idx,int l,int r)
{
	nodes[idx].left = l;
	nodes[idx].right = r;
	nodes[idx].set = 0;
	if (l<r)
	{
		int mid = (l+r)/2;
		build(idx<<1,l,mid);
		build(idx<<1|1,mid+1,r);
	}
}

void pushdown(int idx)
{
	if (nodes[idx].set)
	{
		nodes[idx<<1].set = nodes[idx].set;
		nodes[idx<<1|1].set = nodes[idx].set;
		nodes[idx].set = 0;
	}
}

void update(int idx,int l, int r, int v)
{
	if (nodes[idx].left>=l && nodes[idx].right<=r)
	{
		nodes[idx].set = v;
	}
	else
	{
		pushdown(idx);
		int mid = (nodes[idx].left+nodes[idx].right)/2;
		if (l<=mid)
		{
			update(idx<<1,l,r,v);
		}
		if (mid<r)
		{
			update(idx<<1|1,l,r,v);
		}
	}
}

void query(int idx, int l, int r)
{
	if (nodes[idx].set)
	{
		poster[nodes[idx].set] = true; 
	}
	else if ( nodes[idx].left<nodes[idx].right )
	{
		int mid = (nodes[idx].left+nodes[idx].right)/2;
		if (l<=mid)
		{
			query(idx<<1,l,r);
		}
		if (mid<r)
		{
			query(idx<<1|1,l,r);
		}
	}
}

bool cmp(const Point &a, const Point &b)
{
	return a.num<b.num;
}

void init()
{
	scanf("%d%d",&N,&L);
	for (int i=1; i<=N; i++)
	{
		poster[i] = false;
	}
	for (int i=1; i<=2*N; i++)
	{
		int x;
		scanf("%d",&x);
		points[i].idx = i;
		points[i].num = x;
	}
	sort(points+1,points+2*N+1,cmp);
	int number = -1;
	index = 0;
	for (int i=1; i<=2*N; i++)
	{
		if (points[i].num!=number)
		{
			number = points[i].num;
			index ++;
		}
		if (points[i].idx%2)
		{
			intervals[(points[i].idx+1)/2].left = index;
		}
		else{
			intervals[(points[i].idx+1)/2].right = index-1;
		}
	}
}

int main(int argc, char *argv[])
{
	
	init();
	build(1,1,index-1);
	for (int i=1; i<=N; i++)
	{
		update(1,intervals[i].left,intervals[i].right,i);
	}
	query(1,1,index-1);
	int sum = 0;
	for (int i=1; i<=N; i++)
	{
		if (poster[i])
			sum++;
	}
	printf("%d\n",sum);
	return 0;
}
