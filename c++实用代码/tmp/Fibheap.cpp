#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctime>
using namespace std;
struct node{
       int k,d,mark;
       node *l,*r,*p,*s;
       };
node *buf[66];
struct fibheap{
    #define FHLINK(_,__) _->r=__,__->l=_
    #define FHINSERT(_,__) _->r=__->r,_->l=__,_->r->l=_,__->r=_
    
	node *nodes,*root;
	int n;
	void resize(int maxlen){maxlen+=2;n=0;root=NULL;nodes=new node[maxlen];}
	fibheap(int maxlen=0){resize(maxlen);}
	void insert(node *p){
		p->d=0;p->p=p->s=NULL;p->mark=0;
		if (!root){
			root=p;p->l=p->r=p;
		}else{
			FHINSERT(p,root);
			if (p->k<root->k)root=p;
		}
		n++;
	}
	void unite(fibheap *h){
		if (!h->n)return;
		if (!n){*this=*h;return;}
		node *p=root->r,*q=h->root->r;
		FHLINK(root,q); FHLINK(h->root,p);
		if (h->root->k<root->k)root=h->root;
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
		n--;return z;
	}
	void consolidate(){
		int i,D=0;node *w,*x,*y;
		while ((1<<D)<n)D++;
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
				if (x->k>y->k)w=y,y=x,x=w;
				if (!x->s)x->s=y,y->r=y->l=y;
				else FHINSERT(y,x->s);
				buf[w->d]=NULL;
				y->p=x;x->d++;
				x->mark=0;
			    }
			buf[w->d]=w;
		}
		for (i=0;i<D;i++)if (w=buf[i]){
			if (!root)root=w,w->r=w->l=w;
			else{
				FHINSERT(w,root);
				if (w->k<root->k)root=w;
			}
		}
	}
	void cut(node *x,node *y){
		if (x->r==x)y->s=NULL;
		else{
			x->l->r=x->r;x->r->l=x->l;
			if (x==y->s)y->s=x->r;
		}
		y->d--;x->p=NULL;x->mark=0;
		FHINSERT(x,root);
	}
	void cascadingcut(node *y){
		node *z=y->p;
		if (z){
			if (y->mark==0)y->mark=1;
			else{
				cut(y,z);
				cascadingcut(z);
			}
		}
	}
	void decrease(node *p,int key){
        p->k=key;
		node *y=p->p;
		if (y && p->k<y->k){
			cut(p,y);
			cascadingcut(y);
		}
		if (p->k<root->k)root=p;
	}
	int min(){return root->k;}
	void del(node *x)
	{
         decrease(x,-(1<<30));
         extractmin();
    }
};
fibheap a;
int n,i;

int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	int x=13251325;
	scanf("%d",&n);
	int t1=clock();
	a.resize(n);
	for (i=1;i<=n;i++)
	{
        a.nodes[i].k=x&0x7fffffff;
        x+=(x<<2)+1;
        a.insert(a.nodes+i);
    }
    /*for (i=1;i<=n;i++)
	{
        a.decrease(a.nodes+i,(a.nodes+i)->k-rand());
    }*/
    for (i=1;i<=n;i++)
	{
        //a.extractmin();
        printf("%d\n",a.extractmin()->k);
    }
    printf("time=%d\n",(int)clock()-t1);
	system("pause");
	return 0;
}


/*
int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	for (int i=0;i<1000000;i++)a[i].resize(3);
	system("pause");
	return 0;
}
*/


/*

int main()
{
	//freopen("a.in","r",stdin);
	//freopen("a.out","w",stdout);
	scanf("%d",&n);
	int t1=clock();
	a.resize(n);
	for (i=1;i<=n;i++)
	{
        a.nodes[i].k=i*2;
        a.insert(a.nodes+i);
    }
    for (i=1;i<=n;i++)
	{
        a.decrease(a.nodes+i,i);
    }
    for (i=1;i<=n;i++)
	{
        printf("%d\n",a.extractmin()->k);
    }
    printf("time=%d\n",(int)clock()-t1);
	system("pause");
	return 0;
}*/














