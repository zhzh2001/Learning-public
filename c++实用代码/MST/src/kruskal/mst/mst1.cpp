#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<algorithm>
#define N 1000005
#define M 5000005
#define ll long long
struct edge{int x,y,z,id;}e[M];
bool cmp(const edge &x,const edge &y){return x.z<y.z;}
int f[N],choose[M];
int find(int x){
	if (f[x]==x)return x;
	else return f[x]=find(f[x]);
}
int main()
{
	freopen("mst.in","r",stdin);
	freopen("mst.out","w",stdout);
	int n,m;ll ans=0;scanf("%d%d",&n,&m);
	for (int i=1;i<=m;++i)scanf("%d%d%d",&e[i].x,&e[i].y,&e[i].z),e[i].id=i;
	std::sort(e+1,e+1+m,cmp);
	for (int i=1;i<=n;++i)f[i]=i;
	for (int i=1;i<=m;++i){
		int f1=find(e[i].x),f2=find(e[i].y);
		if (f1!=f2)choose[e[i].id]=1,f[f1]=f2,ans+=e[i].z;
		else choose[e[i].id]=0;
	}
	printf("%I64d\n",ans);
	//for (int i=1;i<=m;++i)if (choose[i])printf("%d\n",i);
	//system("pause");for (;;);
	return 0;
}


