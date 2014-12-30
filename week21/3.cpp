//Author: a
#include<algorithm>
#include<cassert>
#include<cstdio>
#include<cmath>
#include<ctime>
#include<cstring>
using namespace std;

#define minN 1
#define maxN 100000
#define maxL 1000000000
#define mina_i 0
#define maxa_i L
#define minb_i 0
#define maxb_i L

template<typename Type>
struct SBNode{
	int size;
	Type key;
	SBNode<Type>* lchild;
	SBNode<Type>* rchild;
	SBNode(){}
	SBNode(SBNode<Type>*l,SBNode<Type>*r,int s,Type k):
	lchild(l),rchild(r),size(s),key(k) {}
};

template<typename Type>
class SBTree{
 private:
	 SBNode<Type>* root;
	 SBNode<Type>* _null;
	 
	 void left_rotate(SBNode<Type>*& root);
	 void right_rotate(SBNode<Type>*& root);
	 void maintain(SBNode<Type>*& root,bool style);
	 void insert(SBNode<Type>*& root,Type key);
	 void erase (SBNode<Type>*& root,Type key);
	 
 public:
	 SBTree();
	 void insert(Type key);
	 void erase(Type key);
	 Type get_max();
};



template<typename Type>
Type SBTree<Type>::get_max(){
	if(root==_null){
		return Type();
	}
	SBNode<Type>* tmp=root;
	while(tmp->rchild!=_null){
		tmp=tmp->rchild;
	}
	return tmp->key;
}

template<typename Type>
void SBTree<Type>::erase(Type key){
	erase(root,key); }

template<typename Type>
void SBTree<Type>::erase(SBNode<Type>*& root,Type key){
	if(root==_null) return; root->size--;
	if(root->key==key){
		SBNode<Type>* tmp;
		if(root->lchild!=_null && root->rchild==_null){
			tmp=root; root=tmp->lchild; delete tmp; }
		else if(root->lchild==_null && root->rchild==_null){
			tmp=root; root=_null; delete tmp; }
		else {
			tmp=root->rchild; 
			while(tmp->lchild!=_null) tmp=tmp->lchild;
			root->key=tmp->key; erase(root->rchild,tmp->key);}
	}
	else if(key< root->key) erase(root->lchild,key);
	else erase(root->rchild,key);
}

template<typename Type>
void SBTree<Type>::insert(SBNode<Type>*& root,Type key){
	if(root==_null){
		root=new SBNode<Type>(_null,_null,1,key);
		return;
	}
	root->size++;
	if(key < root->key){
		insert(root->lchild,key);
	}
	else{
		insert(root->rchild,key);
	}
	maintain(root,key>=root->key);
}

template<typename Type>
void SBTree<Type>::insert(Type key){
	insert(root,key);
}

template<typename Type>
SBTree<Type>::SBTree(){
	_null=new SBNode<Type>();
	root=_null; 
	root->lchild=root->rchild=_null;
	root->size=0;
}


template<typename Type>
void SBTree<Type>::left_rotate(SBNode<Type>*& root){
	SBNode<Type>* tmp=root->rchild;
	root->rchild=tmp->lchild;
	tmp->lchild=root;
	tmp->size=root->size;
	root->size=root->lchild->size+ root->rchild->size+1;
	root=tmp;
}

template<typename Type>
void SBTree<Type>::right_rotate(SBNode<Type>*& root){
	SBNode<Type>* tmp=root->lchild;
	root->lchild=tmp->rchild;
	tmp->rchild=root;
	tmp->size=root->size;
	root->size=root->lchild->size+ root->rchild->size+1;
	root=tmp;
}

template<typename Type>
void SBTree<Type>::maintain(SBNode<Type>*& root,bool style){
	if(root==_null){
		return;
	}
	if(!style){
		if(root->lchild->lchild->size> root->rchild->size){
			right_rotate(root);
		}
		else if(root->lchild->rchild->size> root->rchild->size){
			left_rotate(root->lchild);
			right_rotate(root);
		}
		else return;
	}
	else {
		if(root->rchild->rchild->size> root->lchild->size){
			left_rotate(root);
		}
		else if(root->rchild->lchild->size> root->lchild->size){
			right_rotate(root->rchild);
			left_rotate(root); 
		}
		else return;
	}
	maintain(root->lchild,false);
	maintain(root->rchild,true);
	maintain(root,false);
	maintain(root,true);
}
struct rec{
	int pos;
	int h;
};
bool operator<(rec l,rec r){
	return l.pos<r.pos;
}
rec r[2*maxN];
bool vis[maxN+1];
int main(){
	int l;
	int n;
	int ptr;
	int ans;
	int L;
	vis[0]=1;
	{
		scanf("%u%u",&n,&L);
		memset(vis+1,0,n);
		
		l=0;
		int id;
		for(id=1;id<=n;id++){
			int Ai;
			int Bi;
			scanf("%u%u",&Ai,&Bi);
			r[l].pos=Ai;
			r[l].h=-id;
			l++;
			r[l].pos=Bi;
			r[l].h=id;
			l++;
		}
		sort(r,r+l);
		ans=0;
		SBTree<int> sbt;
		ptr=0;
		for(;;){
			int mpos;
			mpos=r[ptr].pos;
			if(mpos==r[l-1].pos){
				break;
			}
			do{
				if(r[ptr].h>0){
					sbt.erase(r[ptr].h);
				}
				else{
					sbt.insert(-r[ptr].h);
				}
				ptr++;
			}while(mpos==r[ptr].pos);
			int tmp=sbt.get_max();
			if(!vis[tmp]){
				vis[tmp]=1;
				ans++;
			}
		}
		printf("%u\n",ans);
	}
	return 0;
}
 
