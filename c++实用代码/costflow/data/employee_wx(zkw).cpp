/*
PROG:NOI2008 ־Ը����ļemployee
ALGO:minimum cost maximum flow(ʵ�ֲ�������SAP���㷨)
STAT:AC(total test time 0.72s)
MEMO:����Ĺؼ��ڹ�ͼ���������Լ�ΪʲôҪ�������ο�CMYK�Ľ��ⱨ�档��һ���ؼ���ʵ�֣����
     ֱ������SPFA����С����������ͨ��ֻ�ܹ�8�����ݡ���������SAP���㷨����������AC��
	 �㷨˼�����£�BY ZKW����
	 ����d[i]Ϊ��i�ľ�����, c[i][j]Ϊ��edge(i,j)��Ȩ
	 �κ�һ�����·�㷨��֤���㷨����ʱ�������edge(i,j)����:
            d[i] <= d[j] + c[i][j]	         ������1��
	 �Ҷ���ÿ��i�����ٴ���һ��jʹ�õȺų���  ������2��
     ���仰˵���κ�һ���������������������㷨�����Խ������·������������SPFA��Dijkstra.
	 �㷨������ǡ�����·�ϵı�����d[i]=d[j]+c[i][j]
     
	 ����С�������ļ����У�����ÿ����d[i]=d[j]+c[i][j]��·������󶼲����ƻ�����1��
	 ���ǿ����ƻ�������2��(����۶��ǲ�����Ҫ�����ʼ��d[i]�Ǻܴ�ģ�)
	 ����������2�ĺ����ʲô�أ�ʹ�����Ҳ���ÿ���߶�����d[i]=d[j]+c[i][j]���µ�����·��
	 �������ʹ��Dijkstra��SPFA�ȵ��㷨������С��������
	 ֻ��ÿ����������¼����µ���������2�ľ����š���������һ���˷ѣ�
	 ���ǿ��Բ�������SAP�����������˼�룬��ʼ����������1�ľ������ϲ����޸ģ�
	 ֱ�����Լ������㣨��������2���� 
     �������һ��Ѱ������·���ɹ���DFS���ҵ�
	 t = min{d[j]+c[i][j]-d[i]} (visit[i]==true && visit[j]==false && cap[i][j]>0)
	 Ȼ�����з��ʹ��ĵ�(visit[i]==true)�ľ�����d[i]����t
	 ����֤�������������ƻ�����1������������һ���µı߽�����d[i]=d[j]+c[i][j]����ͼ
	 
	 �㷨�Ĳ�����ǳ�ʼ�����Ϊ0 ���������㣬����������㣬�޸ı�ż������㣬
	 ֱ�����ײ������㣺Դ��ı���Ѿ����ӵ���+�ޡ� 
     
	 ���������SAP��DFS������·�Ĺ����У������ִ���취��
	 (1)�ҵ�һ������·�������˳�DFS���̣���������
	 (2)�ҵ�һ������·�����˳����ۼӵ�ǰ·���Ŀ����������ٴӵ�ǰ��������µ�����·
	 ������������⣬��ǰ��(2)�ַ������ٶȸ��죬�����븴�Ӷȸ�Щ
	 ������С���������⣬���ھ�������c[i][j]Ӱ���һ��һ������S-T֮������·ֻ��һ��
	 ������(1)�ķ���������Ѿ��ǳ�����
	 ��һ�����ҵ���ʶ������

LAST MODI��2009/5/31 

*/
#include <iostream>
using namespace std;
const int MAXN = 1248;
const int BIG  = 99999999;
struct node {
  int v, w, c;     		//v:adj vetex, c:capacity, w:cost
  node *next, *back;
};
node *g[MAXN];			//ajacent list to store the flow network
int n, m, cost;
int S, T;				//S: source node, T: sink node
int dist[MAXN];			//dist: shortest distance
bool visit[MAXN];

inline void addedge(int u, int v, int w, int c = BIG)
{
  node nu = {v, w, c, g[u], NULL}, nv = {u, -w, 0, g[v], NULL};
  g[u] = new node(nu);
  g[v] = new node(nv);
  g[u]->back = g[v];
  g[v]->back = g[u];
}
void init()
{
  int i, j, k, t;
  freopen("employee.in","r",stdin);
  freopen("employee.out","w",stdout);
  scanf("%d%d", &n, &m);
  n++;
  for (i=1; i<n; i++)
  {
    scanf("%d", &t);
	addedge(n+1, i, 0, t);
	addedge(i+1, 0, 0, t);
  }
  for (i=1; i<=m; i++)
  {
    scanf("%d%d%d", &j, &k, &t);
	addedge(j, k+1, t);
  }
  for (i=1; i<n; i++)
    addedge(i+1, i, 0);
  S = n+1;    T = 0;
}

int aug(int i, int lim)   //recursively find the shortest augmenting path
{
  node *p;
  int d, nlim;
  if (i==T)					//�ҵ����
  {
    cost += dist[S] * lim;	//�ۼӱ�������ķ��ô���
	return lim;				//������������
  }
  visit[i] = true;
  for (p = g[i]; p != NULL; p = p->next)
    if ( !visit[p->v] && (p->c > 0) && (p->w + dist[p->v] == dist[i])) //can go to p->v
	{
	   nlim = lim < p->c ? lim : p->c;		//�µĿ���������
	   d = aug(p->v, nlim);					//��·���ݹ�
	   if (d > 0)							//����ɴ��㣬���ҵ�һ��������·
	   {
	     p->c -= d;							//��������
	     p->back->c += d;
	     return d;
	   }
	}
  return 0;		  //can not find a augmenting path
}

bool modlabel()		//�޸ľ�����
{
  int d = BIG, t, i;
  node *p;
  for (i = 0; i<= n+1; i++)
    if (visit[i])
	  for (p = g[i]; p ; p = p->next)
	    if (!visit[p->v] && p->c > 0)
		{
		  t = dist[p->v] + p->w - dist[i];
		  if (t < d) d = t;
		}
  if (d == BIG) return false;
  for (i=0; i<= n+1; i++)
    if (visit[i])
	  dist[i] += d;
  return true;
}

int main()
{
  init();
  do {
    do
	  memset(visit, 0, sizeof(visit));
	while(aug(S, BIG));
  }while(modlabel());
  printf("%d\n", cost);
  return 0;
}


