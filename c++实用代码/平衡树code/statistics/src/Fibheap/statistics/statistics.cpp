#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 1000005
struct Fibheap{
	#define FHLINkey(_,__) _->r=__,__->l=_
	#define FHINSERT(_,__) _->r=__->r,_->l=__,_->r->l=_,__->r=_
	struct node{
		int key,d,markey;
		node *l,*r,*p,*s;
	};
	static node *buf[66];
	node *nodes,*root; int n,len;
	void resize(int maxlen){maxlen+=2;n=0;root=NULL;nodes=new node[maxlen];}
	Fibheap(int maxlen=0){len=0;resize(maxlen);}
	void insert(node *p){
		p->d=0;p->p=p->s=NULL;p->markey=0;
		if (!root){
			root=p;p->l=p->r=p;
		}else{
			FHINSERT(p,root);
			if (p->key<root->key)root=p;
		}
		++n;
	}
	void unite(Fibheap *h){
		if (!h->n)return;
		if (!n){*this=*h;return;}
		node *p=root->r,*q=h->root->r;
		FHLINkey(root,q); FHLINkey(h->root,p);
		if (h->root->key<root->key)root=h->root;
		n+=h->n;
	}
	node *extractmin(){
		node *z=root,*y;
		if (!z)return z;
		for (y=z->s;y;y=z->s){
			y->p=NULL;
			if (y->r==y)z->s=NULL;
			else{
				y->l->r=y->r,y->r->l=y->l;
				z->s=z->s->r;
			}
			FHINSERT(y,z);
		}
		if (n==1)root=NULL;
		else{
			z->r->l=z->l;z->l->r=z->r;
			root=z->r;
			consolidate();
		}
		--n;return z;
	}
	void consolidate(){
		int i,D=0;node *w,*x,*y;
		while ((1<<D)<n)++D;
		D=D+D+2;
		memset(buf,0,D*4);
		for (w=root;root;w=root){
			if (w->r==w)root=NULL;
			else{
				w->r->l=w->l,w->l->r=w->r;
				root=root->r;
			}
			while (buf[w->d]){
				x=w,y=buf[w->d];
				if (x->key>y->key)w=y,y=x,x=w;
				if (!x->s)x->s=y,y->r=y->l=y;
				else FHINSERT(y,x->s);
				buf[w->d]=NULL;
				y->p=x;x->d++;
				x->markey=0;
			}
			buf[w->d]=w;
		}
		for (i=0;i<D;++i)if (w=buf[i]){
			if (!root)root=w,w->r=w->l=w;
			else{
				FHINSERT(w,root);
				if (w->key<root->key)root=w;
			}
		}
	}
	void cut(node *x,node *y){
		if (x->r==x)y->s=NULL;
		else{
			x->l->r=x->r;x->r->l=x->l;
			if (x==y->s)y->s=x->r;
		}
		y->d--;x->p=NULL;x->markey=0;
		FHINSERT(x,root);
	}
	void cascadingcut(node *y){
		node *z=y->p;
		if (z){
			if (y->markey==0)y->markey=1;
			else{
				cut(y,z);
				cascadingcut(z);
			}
		}
	}
	void decrease(node *p,int keyey){
		p->key=keyey;
		node *y=p->p;
		if (y && p->key<y->key){
			cut(p,y);
			cascadingcut(y);
		}
		if (p->key<root->key)root=p;
	}
	int top(){return root->key;}
	bool empty(){return len==0;}
	void del(node *x){
		decrease(x,-2147483647);
		extractmin();
	}
	void insert(int key){
		++len;nodes[len].key=key;insert(nodes+len);
	}
	void pop(){extractmin();}
};Fibheap::node* Fibheap::buf[66];
Fibheap a1;
struct Random_Heap1{
	#define N 1000005
	struct node{node *l,*r;int key;}nodes[N];
	int ran(){static int x=31253125;x+=(x<<4)+1;x&=(0x7fffffff);return x&(65536);}
	node *M(node *p,node *q){
		return (!p||!q)?(p?p:q):(p->key<q->key?M(q,p):
			((ran()?p->r=M(p->r,q):p->l=M(p->l,q)),p));
	}
	node *root;int len;
	Random_Heap1(){root=NULL;len=0;}
	void insert(int key){
		++len;nodes[len].key=key;nodes[len].l=nodes[len].r=NULL;
		root=M(root,nodes+len);
	}
	bool empty(){return len==0;}
	int top(){return root->key;}
	void pop(){root=M(root->l,root->r);}
	#undef N
};
Random_Heap1 a;
int main()
{
	long long n,A,b,c,key,ans=1;
	freopen("statistics.in","r",stdin);
	freopen("statistics.out","w",stdout);
	scanf("%I64d%I64d%I64d%I64d",&A,&b,&c,&n);
	a1.resize(n*2);a.insert(1);
	for (int i=2;i<=n;++i){
		key=(A*a.top()+b*i+c)%1000000007;
		if (i&1)a.insert(key);
			else a1.insert(key);
		while (a.top()>a1.top()){
			int tmp1=a.top(),tmp2=a1.top();
			a.pop();a1.pop();
			a.insert(tmp2);a1.insert(tmp1);
		}
		ans+=key;
	}
	printf("%I64d\n",ans);
	//system("pause");for (;;);
	return 0;
}


