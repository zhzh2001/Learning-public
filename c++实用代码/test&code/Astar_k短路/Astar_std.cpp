#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define INF 9999999
using namespace std;
const int maxn = 1012;
const int maxm = 200012;
int n,m,s,t,k,cnt,ans;
struct nod
{
	int u,v,w,next;
}e[maxm],e2[maxm];
int head[maxn],head2[maxn];
int d[maxn],vis[maxn],deg[maxn];
typedef struct node	//ע������STL�����������ѹ��ṹ���д����
{
	int v,f,g;
}NODE;
struct cmp
{
	bool operator()(const node&a,const node&b)
	{
		return a.f>b.f;
	}
};
priority_queue<node,vector<node>,cmp>q;
queue<int> p;
inline void addedge(int x,int y,int w)
{
	e[cnt].u = x;e[cnt].v = y;
	e[cnt].w = w;
	e[cnt].next = head[x];
	head[x] = cnt;
	cnt++;
	e2[cnt].u = y;e2[cnt].v = x;
	e2[cnt].w = w;
	e2[cnt].next = head2[y];
	head2[y] = cnt;
	cnt++;
}
void DIJ()  //DIJҪ�����ȶ�����д��
{
	for(int i = 1;i<=n;i++)d[i]=(i==t?0:INF);
	memset(vis,0,sizeof(vis));
	NODE tmp,temp;
	tmp.v = t,tmp.f = 0;
	q.push(tmp);
	//printf("ooo\n");
	while(!q.empty())
	{
		//printf("ac\n");
		temp = q.top();q.pop();
		int x = temp.v;
		vis[x] = 1;
		//if(temp.f>d[x])continue;
		//printf("ac:%d %d\n",temp.v,temp.f);
		for(int i = head2[x];i!=-1;i = e2[i].next)
		{
			int yy = e2[i].v;
			// d[yy] = min(d[yy],d[x]+e2[i].w);
			if(d[yy]>d[x]+e2[i].w)  //�ر�ע����������ȱ�֤d[yy]���С���ɳڣ���
			{
				d[yy] = d[x]+e2[i].w;
				if(vis[yy])continue;
				tmp.v = yy;
				tmp.f = d[yy];
				q.push(tmp);
			}
		}
	}
}
/*AStar�㷨�������ۺ����Ĺ��ѡ�DIJ�������·����˵d[i]���ֻһ�Ρ��������k������
��k��·����������̰�Ĳ����ܱ�֤ȫ�����Ž⣬����˵Ҫ��ǰ���й��ۡ�����t��ʱ�����k��
·��f(s)=g(s)+h(s)��h(s)�ǵ�ǰ״̬����̬����С���ۣ�����������·�����s2��s1��չ
��������ôh(s1)<=h(s2)+V(s1,s2)��*/
void work()
{
	NODE temp,tmp;
	int nx = 0;
	ans = -1;
	temp.v = s;temp.f = temp.g = d[s];
	q.push(temp);
	memset(deg,0,sizeof(deg));
	while(!q.empty())
	{
		//printf("abc\n");
		temp = q.top();q.pop();
		int x = temp.v;
		//if(deg[x]>=k)continue;
		//printf("abcd%d\n",deg[x]);
		deg[x]++;
		if(x==t&&deg[x]==k){ans = temp.f;return ;}
		for(int i = head[x];i!=-1;i = e[i].next)
		{
			int yy = e[i].v;
			if(deg[yy]>=k)continue;
			tmp.v = yy;
			// deg[yy]++;
			int y = temp.f-d[x];
			tmp.f = y+e[i].w+d[yy];
			// if(yy==2)printf("kkk%d %d\n",tmp.v,tmp.f);
			q.push(tmp);
		}
	}
}
int main()
{
	int i,j,x,y,w;
	//freopen("test2.txt","r",stdin);
	//freopen("out2.txt","w",stdout);
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		//scanf("%d%d",&n,&m);
		memset(head,-1,sizeof(head));
		memset(head2,-1,sizeof(head2));
		cnt = 0;
		while(!q.empty())q.pop();
		for(i = 0;i<m;i++)
		{
			scanf("%d%d%d",&x,&y,&w);
			addedge(x,y,w);
		}
		scanf("%d%d%d",&s,&t,&k);
		if(s==t)k++;  //���s==t����ô��Ӵ���Ҫ��һ�Ρ���Ϊs����Դ�����ǻ�㣬�������һ����ӵ�ʱ����뻹δ0��
		DIJ();
		work();
		if(deg[t]<k)printf("-1\n");
		else printf("%d\n",ans);
	}
	return 0;
}

