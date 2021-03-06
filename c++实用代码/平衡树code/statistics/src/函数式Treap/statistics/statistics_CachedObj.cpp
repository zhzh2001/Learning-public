#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<iostream>
#include<algorithm>
using namespace std;
template<class T> class CachedObj{
	public:
	void *operator new(size_t s){
		if (!head){
			T *a=new T[SIZE];
			for (size_t i=0;i<SIZE;++i)add(a+i);
		}
		T *p=head;head=head->CachedObj<T>::next;return p;
	}
	void operator delete(void *p,size_t){if (p)add(static_cast<T*>(p));}
	virtual ~CachedObj(){}
	protected:T *next;
	private:
	static T *head;static const size_t SIZE;
	static void add(T *p){p->CachedObj<T>::next=head;head=p;}
};
template<class T> T *CachedObj<T>::head=0;
template<class T> const size_t CachedObj<T>::SIZE=100000;
struct Treap{
	struct node:CachedObj<node>{
		int key,fix,size;
		node *l,*r;
		node(int _key,int _fix,node *_l,node *_r):
			key(_key),fix(_fix),l(_l),r(_r){update();}
		node(){}
		void update(){
			size=1;
			if (l)size+=l->size;
			if (r)size+=r->size;
		}
	};
	node *New(int _key,int _fix,node *_l,node *_r){
		//++a1;if (a1==BUFFER_SIZE){A=new node[BUFFER_SIZE];a1=0;}
		node *tmp=new node;tmp->key=_key;tmp->fix=_fix;tmp->l=_l;tmp->r=_r;
		tmp->update();return tmp;
	}
	node *root;
	Treap():root(NULL){srand(time(0));}
	node *newnode(int key){
		return New(key,(rand()<<15)+rand(),NULL,NULL);
	}
	node *merge(node *x,node *y){
		return (!x||!y)?(x?x:y):
			(x->fix<y->fix?New(x->key,x->fix,x->l,merge(x->r,y)):
				New(y->key,y->fix,merge(x,y->l),y->r));
	}
	node *split_l(node *x,int key){
		return !x?NULL:(x->key<=key?
			New(x->key,x->fix,x->l,split_l(x->r,key)):
			split_l(x->l,key));
	}
	node *split_r(node *x,int key){
		return !x?NULL:(x->key>key?
			New(x->key,x->fix,split_r(x->l,key),x->r):
			split_r(x->r,key));
	}
	node *insert(node *x,int key){
		return merge(merge(split_l(x,key),newnode(key)),split_r(x,key));
	}
	node *find(node *x,int key){
		if (x==NULL)return NULL;
		if (key<x->key)return find(x->l,key);
		else if (key>x->key)return find(x->r,key);
		else return x;
	}
	node *del(node *x,int key){
		if (x==NULL)return NULL;
		if (key<x->key)return New(x->key,x->fix,del(x->l,key),x->r);
		else if (key>x->key)return New(x->key,x->fix,x->l,del(x->r,key));
		else return merge(x->l,x->r);
	}
	node *findkth(node *root,int k){
		node *x=root;int S;
		while (k){
			S=x->l?x->l->size:0;
			if (k==S+1) break;
			if (k<=S) x=x->l;
				else k-=S+1,x=x->r;
		}
		return x;
	}
	node *fmin(node *x){while (x->l)x=x->l;return x;}
	node *fmax(node *x){while (x->r)x=x->r;return x;}
	void print(node *x){
		if (x==NULL)return;
		print(x->l);
		printf("nie %d\n",x->key);
		print(x->r);
	}
};
Treap a;
int main(){
	long long n,A,b,c,m,tmp,key,ans=1;
	int t1=clock();
	freopen("statistics.in","r",stdin);
	freopen("statistics.out","w",stdout);
	scanf("%I64d%I64d%I64d%I64d",&A,&b,&c,&n);
	a.root=a.insert(a.root,1);
	for (int i=2;i<=n;++i){
		if ((i-1)&1)tmp=((i-1)>>1)+1;else tmp=(i-1)>>1;
		m=a.findkth(a.root,tmp)->key;
		key=(A*m+b*i+c)%1000000007;
		a.root=a.insert(a.root,(int)key);
		//a.root=a.del(a.root,(int)key);
		//a.root=a.insert(a.root,(int)key);
		ans+=key;
	}
	printf("%I64d\n",ans);
	//printf("%d\n",clock()-t1);
	return 0;
}


