#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define N 1000005
struct Treap{
	struct node{
		int key,fix,size;
		node *l,*r;
		node(int _key,int _fix,node *_l,node *_r,int _size):
			key(_key),fix(_fix),l(_l),r(_r),size(_size){}
		void update(){
			size=1;
			if (l)size+=l->size;
			if (r)size+=r->size;
		}
	};
	node *root;
	Treap():root(NULL){srand(time(0));}
	node *newnode(int key){
		return new node(key,rand(),NULL,NULL,1);
	}
	node *merge(node *x,node *y){
		node *tmp=(!x||!y)?(x?x:y):
			(x->fix<y->fix?new node(x->key,x->fix,x->l,merge(x->r,y),0):
				new node(y->key,y->fix,merge(x,y->l),y->r,0));
		if (tmp) tmp->update();
		return tmp;
	}
	node *split_l(node *x,int key){
		node *tmp=!x?NULL:(x->key<=key?
			new node(x->key,x->fix,x->l,split_l(x->r,key),0):
			split_l(x->l,key));
		if (tmp) tmp->update();
		return tmp;
	}
	node *split_r(node *x,int key){
		node *tmp=!x?NULL:(x->key>key?
			new node(x->key,x->fix,split_r(x->l,key),x->r,0):
			split_r(x->r,key));
		if (tmp) tmp->update();
		return tmp;
	}
	/*node *del(node *x,int key){
		node *L=split_l(x,key),*tmp=merge(L?L->l:NULL,split_r(x,key));
		if (tmp) tmp->update();
		return tmp;
	}*/
	node *insert(node *x,int key){
		node *tmp=merge(merge(split_l(x,key),newnode(key)),split_r(x,key));
		if (tmp) tmp->update();
		return tmp;
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
		printf("%d\n",x->key);
		print(x->r);
	}
};
Treap a;
int T[N];
int main(){
	long long n,A,b,c,m,tmp,key,ans=1;
	freopen("statistics.in","r",stdin);
	freopen("statistics.out","w",stdout);
	scanf("%I64d%I64d%I64d%I64d",&A,&b,&c,&n);
	a.root=a.insert(a.root,1);
	for (int i=2;i<=n;++i){
		if ((i-1)&1)tmp=((i-1)>>1)+1;else tmp=(i-1)>>1;
		m=a.findkth(a.root,tmp)->key;
		key=(A*m+b*i+c)%1000000007;
		a.root=a.insert(a.root,(int)key);
		ans+=key;
	}
	printf("%I64d\n",ans);
	//system("pause");for (;;);
	return 0;
}


