//Author:  tiabph 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(x,y) (((x)<=(y))?(x):(y))
#define MAX(x,y) (((x)>=(y))?(x):(y))

#define MAX_N 200002
#define MAX_L 2000000002

int postBuf[MAX_N][2], postNum;
int tbuf[MAX_N*2], tnum;
int treeBuf[MAX_N][6], root;//start, end, ch1, ch2, parent, value(empty=1)

int cmp(const void *a,const void *b)
{
    return *(int *)a-*(int *)b;
}

void initTree(){
	int m,n,ts, te;
	root=0;
	for(m=0;m<tnum;m++){
		treeBuf[root][0] = tbuf[m];
		treeBuf[root][1] = tbuf[m];
		treeBuf[root][2] = -1;
		treeBuf[root][3] = -1;
		treeBuf[root][4] = -1;
		treeBuf[root][5] = 1;
		root++;
		treeBuf[root][0] = tbuf[m]+1;
		treeBuf[root][1] = tbuf[m]+1;
		treeBuf[root][2] = -1;
		treeBuf[root][3] = -1;
		treeBuf[root][4] = -1;
		treeBuf[root][5] = 1;
		root++;
	}
	root--;
	ts=0;
	te=root;
	while(te-ts > 1){
		for(m=ts; m<root; m+=2){
			if(m+1 < root){
				treeBuf[te][0] = treeBuf[m][0];
				treeBuf[te][1] = treeBuf[m+1][1];
				treeBuf[te][2] = m;
				treeBuf[te][3] = m+1;
				treeBuf[te][4] = -1;
				treeBuf[te][5] = 1;

				treeBuf[m][4] = te;
				treeBuf[m+1][4] = te;
			}
			else{
				treeBuf[te][0] = treeBuf[m][0];
				treeBuf[te][1] = treeBuf[m][1];
				treeBuf[te][2] = m;
				treeBuf[te][3] = m;
				treeBuf[te][4] = -1;
				treeBuf[te][5] = 1;

				treeBuf[m][4] = te;
			}
			te++;
		}
		ts = root;
		root = te;
	}
	root--;
}

int checkPoster(int s, int e, int r){
	int cs,ce,cv,result=0,nr1,nr2,re1=-1,re2=-1;

	cs = treeBuf[r][0];
	ce = treeBuf[r][1];
	cv = treeBuf[r][5];
	nr1 = treeBuf[r][2];
	nr2 = treeBuf[r][3];
	
	if(s>e || cv==0){
		return 0;
	}

	if(cs==s && ce==e){
		treeBuf[r][5] = 0;
		return cv;
	}

	if(nr1==-1){
		if(cs>=s && cs<=e){
			treeBuf[r][5] = 0;
			return cv;
		} else{
			return 0;
		}
	}

	re1 = checkPoster(MAX(s,treeBuf[nr1][0]) , MIN(e, treeBuf[nr1][1]),nr1);
	re2 = checkPoster(MAX(s,treeBuf[nr2][0]) , MIN(e, treeBuf[nr2][1]),nr2);
	if(treeBuf[nr1][5]==0 && treeBuf[nr2][5]==0){
		treeBuf[r][5]=0;
	}
	if(re1>0 || re2>0){
		return 1;
	} else{
		return 0;
	}
}

int fun(){
	int result = 0, m,n;
	initTree();
	for(m=postNum-1; m>=0; m--){
		n=checkPoster(postBuf[m][0], postBuf[m][1], root);
		if(n>0){
			result++;
		}
		if(treeBuf[root][5]==0){
			break;
		}
	}
	return result;
}

int main(){
	int L,N;
	int m, p,q, ps,pe;
	scanf("%d %d",&N, &L);
	for(m=0;m<N;m++){
		scanf("%d %d", &ps, &pe);
		ps*=2;
		pe*=2;
		postBuf[m][0] = ps;
		postBuf[m][1] = pe;
		tbuf[m * 2] = ps;
		tbuf[m * 2 + 1] = pe;
	}
	postNum = N;

	qsort(tbuf,postNum*2,sizeof(tbuf[0]),cmp);
	ps=0;
	pe=1;
	while(pe < postNum*2){
		if(tbuf[ps] != tbuf[pe]){
			ps++;
			tbuf[ps]=tbuf[pe];
		} 
		pe++;
	}
	tnum = ps+1;

	printf("%d\n", fun());

    return 0;
}