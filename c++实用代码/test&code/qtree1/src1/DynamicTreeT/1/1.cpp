#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define oo (1<<30)
#define maxn 10010
int n,x,y,T;
char str[100];
int edgex[maxn*2],edgey[maxn*2];
int root;
struct DynamicTree{
	struct node{
		int key,max;
		node *l,*r,*p,*fa;
    };
	node *a,*null;int len;
	int max(int x,int y){return x>y?x:y;}
	void clear(){
        null=new node;null->max=null->key=-oo;
    }
    void ini_node(node *p){
        p->l=p->r=p->p=null;
        p->max=-oo;p->key=-oo;
    }
	DynamicTree(int n=5){
        n+=5;len=n;a=new node[n];
        for (int i=0;i<n;i++)ini_node(a+i);
        clear();
    }
    void inc(node *p,int d){
         if (p==null)return;
         p->key+=d;p->max+=d;
    }
	void update(node *x){
        x->max=x->key;
        if (x->l->max>x->max)x->max=x->l->max;
        if (x->r->max>x->max)x->max=x->r->max;
    }
	void zig(node *x){
        node *y=x->p,*z=y->p;
		if (z->l==y) z->l=x;else z->r=x;
		x->p=z;y->p=x;
		y->l=x->r;x->r=y;
		y->l->p=y;
		update(y);
	}
    void zag(node *x){
        node *y=x->p,*z=y->p;
		if (z->l==y) z->l=x;else z->r=x;
		x->p=z;y->p=x;
		y->r=x->l;x->l=y;
		y->r->p=y;
		update(y);
	}
	void splay(node *x)
	{
        node *y,*z;
        if (x==null) return;
		while (x->p!=null){
            y=x->p;z=y->p;
			if (z==null) {if (x==y->l)zig(x);else zag(x);}
			else
				if (y==z->l)
					if (x==y->l){zig(y);zig(x);}
					else{zag(x);zig(x);}
				else 
					if (x==y->r){zag(y);zag(x);}
					else{zig(x);zag(x);}
		}
		update(x);
	}
	node *head(node *p){
         for(;p->l!=null;)p=p->l;
         splay(p);return p;
    }
    node *tail(node *p){
         for(;p->r!=null;)p=p->r;
         splay(p);return p;
    }
    node *prev(node *p){
		splay(p);
		if (p->l==null)return null;
		node *q=p->l;
		for (;q->r!=null;)q=q->r;
		splay(q);return q;
	}
	node *next(node *p){
		splay(p);
		if (p->r==null)return null;
		node *q=p->r;
		for (;q->l!=null;)q=q->l;
		splay(q);return q;
	}
	node *Expose(node *p){
         node *q=null,*pre=null,*tmp;
         while (p!=null){
             splay(p);p->r->p=null;
             //if (p->r!=null){tmp=head(p->r);tmp->fa=p;}
             p->r=pre;pre->p=p;
             update(p);q=p;pre=head(p);p=pre->fa;
             }
         splay(q);return q;
    }
    node *getnode(int x){return a+x;}
	int getid(node *p){return p-a;}
	int Maxcost(node *p){return Expose(p)->max;}
    void Update(node *p,int d){inc(Expose(p),d);}
	void Change(node *p,int key){
		splay(p);p->key=key;
		update(p);
    }
	node *Parent(node *p){
		splay(p);if (p->l!=null)return prev(p);
		else return p->fa;
	}
	node *Root(node *p){return head(Expose(p));}
	void Cut(node *p){
		splay(p);p->l->p=null;p->l=null;
        update(p);p->fa=null;
	}
	node *LCA(node *p,node *q){
		node *x=Root(p),*y=Expose(q),*z=head(y);
		if (x==z)return y;
		else return null;
	}
	int Query(node *p,node *q){
        int Max;Expose(p);
        node *y=Expose(q);
		Max=y->r->max;
		if (p!=y)splay(p),Max=max(Max,p->max);
		return Max;
	}
	/*int Query(node *p,node *q){
        int Max;Expose(p);
        node *y=Expose(q);
		Max=y->r->max;
		y=Expose(p);
		Max=max(Max,y->r->max);
		return Max;
	}*/
	int Maxcost(int x){return Maxcost(getnode(x));}
    void Update(int x,int d){Update(getnode(x),d);}
    void Change(int x,int key){Change(getnode(x),key);}
	int Parent(int x){return getid(Parent(getnode(x)));}
	int Root(int x){return getid(Root(getnode(x)));}
	void Cut(int x){Cut(getnode(x));}
	int LCA(int p,int q){return getid(LCA(getnode(p),getnode(q)));}
	int Query(int p,int q){return Query(getnode(p),getnode(q));}
};
struct Edge{
	int link[maxn*2],next[maxn*2],cost[maxn*2],son[maxn],l;
	void clear(){l=0;memset(son,0,sizeof(son));}
	void addedge(int x,int y,int z){
		link[++l]=y;cost[l]=z;next[l]=son[x];son[x]=l;
		}
}e;
struct Tree{
	int fa[maxn],dep[maxn],w[maxn];
	void Build(int x,int y,int deep){
         dep[x]=deep;fa[x]=y;
         for (int i=e.son[x];i;i=e.next[i]){
             int j=e.link[i];
             if (j!=y)w[j]=e.cost[i],Build(j,x,deep+1);
        }
    }
};
Tree c;
DynamicTree a(maxn);
void copy(){
	int i;
	for (i=1;i<=n;i++)
	{
        a.a[i].fa=a.getnode(c.fa[i]);
        a.a[i].l=a.a[i].r=a.a[i].p=a.null;
        a.a[i].key=c.w[i];
        a.update(a.getnode(i));
    }
    a.a[root].fa=a.null;
    /*for (int i=1;i<=n;i++)a.a[i].num=i;
    a.a[0].num=1234;
    a.null->num=-1;*/
}
void init(){
     int i,x,y,z;
     a.clear();e.clear();
     scanf("%d",&n);
     for (i=1;i<=n-1;i++){
         scanf("%d%d%d",&x,&y,&z),e.addedge(x,y,z),e.addedge(y,x,z),edgex[i]=x,edgey[i]=y;
     }
     root=rand()%n+1;
     //root=1;
     c.Build(root,0,0);
     copy();//a.null->fa=a.null;
}
int main()
{
	freopen("1.in","r",stdin);
	freopen("1.out","w",stdout);
	srand(1108);
	scanf("%d",&T);
	while (T--){
          init();
          while (1){
                scanf("%s",str);
                if (str[0]=='D')break;
                scanf("%d%d",&x,&y);
                if (str[1]=='H'){
                    int tmp;
                    if (c.dep[edgex[x]]>c.dep[edgey[x]])tmp=edgex[x];
                       else tmp=edgey[x];
                    a.Change(tmp,y);
                    }
                if (str[1]=='U'){
                    printf("%d\n",a.Query(x,y));
                    }
                }
          }
	//system("pause");
	//for (;;);
	return 0;
}














