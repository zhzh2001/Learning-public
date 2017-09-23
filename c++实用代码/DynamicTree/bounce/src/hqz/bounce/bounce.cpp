#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define oo (1<<30)
#define maxn 200010
int n,x,y,T;
char str[100];
int edgex[maxn*2],edgey[maxn*2];
struct DynamicTree{
	struct node{
		int size;
		node *l,*r,*p;
		void update(){
             size=l->size+r->size+1;
		}
    };
	node *a,*null;
	int max(int x,int y){return x>y?x:y;}
	int isroot(node *p){return p->p->l!=p&&p->p->r!=p;}
	void clear(){
        null=new node;null->l=null->r=null;
		null->size=0;
    }
    void ini_node(node *p){
        p->l=p->r=p->p=null;
        p->size=1;
    }
	DynamicTree(int n=5){
        n+=5;a=new node[n];
        for (int i=0;i<n;i++)ini_node(a+i);
        clear();
    }
	void zig(node *x){
        node *y=x->p,*z=y->p;
		if (z->l==y) z->l=x;else if (z->r==y)z->r=x;
		x->p=z;y->p=x;
		y->l=x->r;x->r=y;
		y->l->p=y;
		y->update();
	}
    void zag(node *x){
        node *y=x->p,*z=y->p;
		if (z->l==y) z->l=x;else if (z->r==y)z->r=x;
		x->p=z;y->p=x;
		y->r=x->l;x->l=y;
		y->r->p=y;
		y->update();
	}
	void splay(node *x)
	{
        node *y,*z;
        if (x==null) return;
		while (!isroot(x)){
            y=x->p;z=y->p;
			if (isroot(y)) {if (x==y->l)zig(x);else zag(x);}
			else
				if (y==z->l)
					if (x==y->l){zig(y);zig(x);}
					else{zag(x);zig(x);}
				else 
					if (x==y->r){zag(y);zag(x);}
					else{zig(x);zag(x);}
		}
		x->update();
	}
	node *head(node *p){
         for(;p->l!=null;)p=p->l;
         splay(p);return p;
    }
    node *tail(node *p){
         for(;p->r!=null;)p=p->r;
         splay(p);return p;
    }
	node *Expose(node *p){
		node *q=null;
		for (;p!=null;p=p->p){
			splay(p);p->r=q;(q=p)->update();
		}
	    return q;
	}
    node *getnode(int x){return a+x;}
	int getid(node *p){return p-a;}
	int Depth(node *p){Expose(p);splay(p);return p->l->size+1;}
	void Cut(node *p){
		splay(p);p->l->p=p->p;p->l=null;
        p->p=null;p->update();
	}
	void Changefa(node *x,node *y){Cut(x);x->p=y;}
	void Cut(int x){Cut(getnode(x));}
	void Changefa(int x,int y){Changefa(getnode(x),getnode(y));}
};
DynamicTree a(maxn);
void copy(){
	int i;
	for (i=1;i<=n+1;i++)
	{
        a.a[i].l=a.a[i].r=a.null;
    }
    a.a[n+1].p=a.null;
}
void init(){
     int i,x,y,z;
     a.clear();
     scanf("%d",&n);
     for (i=1;i<=n;i++){
         scanf("%d",&x);
         int tmp=i+x;if (tmp>n)tmp=n+1;
         a.a[i].p=a.getnode(tmp);
     }
     copy();
}
int m,ch,i;
int main()
{
	freopen("bounce.in","r",stdin);
	freopen("bounce.out","w",stdout);
	init();
	scanf("%d",&m);
	for (i=1;i<=m;i++){
        scanf("%d",&ch);
        if (ch==1){
                   scanf("%d",&x);x++;
                   printf("%d\n",a.Depth(a.getnode(x))-1);
                   }
        if (ch==2){
                  scanf("%d%d",&x,&y);x++;
                   int tmp=x+y;if (tmp>n)tmp=n+1;
                   a.Changefa(x,tmp);
                   }
        }
	//system("pause");
	//for (;;);
	return 0;
}









