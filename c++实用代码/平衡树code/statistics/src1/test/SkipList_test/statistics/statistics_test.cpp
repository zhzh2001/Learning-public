#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#define oo (1<<30)
#define exp 0.5
#define Maxlevel 20
#define Maxp 100005
int s1,s2,s3,s;
struct node{
	node *l,*r,*d;
	int key,size,top;
	void update(){
		size=d->size;
		if (r->top)size+=r->size;
	}
};
node *last[Maxlevel+3],*tmp[Maxlevel+3],*tmp1[Maxlevel+3],*path[Maxp];
node Pool[2000005];int P1=0;
struct SkipList{
	int level,p1;node *root;
	void clear(){
		int lvl=Maxlevel;
		for (int i=0;i<=lvl;++i)tmp[i]=new node,tmp[i]->l=NULL,
		tmp[i]->key=-oo,tmp[i]->size=0,tmp[i]->top=0;
		for (int i=0;i<=lvl;++i)tmp1[i]=new node,tmp1[i]->r=NULL,
			tmp1[i]->key=oo,tmp1[i]->size=0,tmp1[i]->top=0;
		for (int i=0;i<=lvl;++i){
			tmp[i]->r=tmp1[i];tmp1[i]->l=tmp[i];
			if (!i)tmp[i]->d=tmp1[i]->d=NULL;
				else tmp[i]->d=tmp[i-1],tmp1[i]->d=tmp1[i-1];
		}
		root=tmp[lvl];level=lvl;
	}
	SkipList(){clear();}
	int Rand(){++s;
		static int x=12347;
		x=(x<<5)+(x>>2)+1;
		return x&32767;
	}
	int RandLevel(){
		int lvl=1;
		while (Rand()<exp*32768&&lvl<Maxlevel)++lvl,++s;
		return lvl;
	}
	node *find(int key){
		node *x=root;int lvl=level;p1=0;
		while (x){
			path[++p1]=x;// s1+=2;
			if (x->r->key<=key)x=x->r,s1++;
				else last[lvl--]=x,x=x->d,s1++;
		}
		s3+=p1;
		return last[0];
	}
	void update(int lvl){
		for (int i=1;i<=lvl;++i)
			tmp[i]->update(),++s2;
		for (int i=p1-1;i;--i)
			path[i]->update(),++s2;
	}
	void insert(int key){
		find(key);
		int lvl=RandLevel();
		for (int i=0;i<=lvl;++i)tmp[i]=Pool+(++P1),tmp[i]->key=key,tmp[i]->top=0;
		for (int i=0;i<=lvl;++i){
			tmp[i]->r=last[i]->r;last[i]->r->l=tmp[i];
			last[i]->r=tmp[i];tmp[i]->l=last[i];
			if (!i)tmp[i]->d=NULL;
				else tmp[i]->d=tmp[i-1];
		}
		tmp[lvl]->top=1;tmp[0]->size=1;
		update(lvl);
	}
	void del(int key){
		node *x=find(key);
		if (x->key!=key)return;x=NULL;
		for (int i=0;i<=level;++i){
			if (last[i]->d!=x)break;x=last[i];
			x->r->l=x->l;x->l->r=x->r;
		}
		//find(key);
		update(0);
	}
	node *findkth(int k){
		node *x=root;
		while (k){
			if (x->r->top&&x->d->size<k)k-=x->d->size,x=x->r;
				else {if (!x->d)break;x=x->d;}
		}
		return x;
	}
	void print(){
		node *x=root,*y;
		for (int i=0;i<=level;++i){
			y=x;while (y!=NULL)printf("%d %d | ",y->key,y->size),y=y->r;
			printf("\n");x=x->d;
		}
		printf("end\n");
	}
};
SkipList a;
int main()
{
	int t1=clock();
	long long n,A,b,c,m,i,tmp,key,ans=1;
	freopen("statistics.in","r",stdin);
	//freopen("statistics.out","w",stdout);
	scanf("%I64d%I64d%I64d%I64d",&A,&b,&c,&n);
	a.insert(1);
	for (i=2;i<=n;++i){//printf("%d\n",i);
		if ((i-1)&1)tmp=((i-1)>>1)+1;else tmp=(i-1)>>1;
		m=a.findkth(tmp)->key;
		key=(A*m+b*i+c)%17;//%1000000007;
		a.insert((int)key);//a.find(rand()<<15);
		a.del((int)key);a.insert((int)key);
		ans+=key;
	}
	printf("%I64d\n",ans);
	printf("find %d\n",s1);
	printf("update %d\n",s2);
	printf("path %d\n",s3);
	printf("else %d\n",s);
	printf("time=%d\n",clock()-t1);
	system("pause");for (;;);
}




