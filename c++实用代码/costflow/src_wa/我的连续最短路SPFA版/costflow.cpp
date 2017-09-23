/*
��������С���������:
�����ʽ����
��1�У�2���ո�ֿ�������N��M��N�ǽڵ�����M�Ǳ�����N��500��M��N^2/2 
��2..M+1�У�ÿ��4���ո�ֿ�������A��B��C��D����ʾ��һ�������A-B���ߵ�����ΪC������ΪD 
�����ʽ��
��1�У�1����������ʾ��Դ��1�����N����С���������

��������:     n���������е��ܽڵ��������1��n
              net[][]�����������
              cost[][]������۾���
              path[]��������·��
              dist[]Դ�㵽��������·
�㷨:��ʼ��С���ú��������Ϊ��Ѱ�ҵ�λ�������·
�����·��������������Ϊ����·�����޸�ʣ�����磬ֱ���޿�����·Ϊֹ
����ֵ:
              ��С���ã��������
˼����
�����·��ΪSPFA���ٶȸ���! SPFA������ڽӾ��󣬻᲻����죿
��BZOJ1292��10�������У�������Ҫ4���һ��

Task1 [187MS] right
Task2 [250MS] right
Task3 [344MS] right
Task4 [547MS] right
Task5 [844MS] right
Task6 [1281MS] right
Task7 [1750MS] right
Task8 [2594MS] right
Task9 [3375MS] right
Task10 [4672MS] right

Accepted  10/10
All right task [15844MS]

*/
#include <iostream>
using namespace std;
const int NMAX = 512;
const int BIG = 99999999;
int net[NMAX][NMAX], cost[NMAX][NMAX];
int path[NMAX], dist[NMAX];
int n, m, ans, s, t;	//s:Դ��, t:���
int q[NMAX*1024];		//SPFAҪ�Ķ���
bool visit[NMAX];		//SPFAҪ�ı�־����
void init()
{
    int i, j, k, c, d;
    scanf("%d%d", &n, &m);
    for (i=1; i<=n; i++)
    {
        for (j=1; j<=n; j++)
          cost[i][j] = BIG;
        cost[i][i] = 0;
    }
    for (i=1; i<=m; i++)
    {
        scanf("%d%d%d%d", &j, &k, &c, &d);
        net[j][k] = c;
        cost[j][k] = d;
    }
	s = 1;    t = n;
}
bool SPFA()
{
	int i, j, f=0, r=1;
	memset(path, -1, sizeof(path));
	memset(visit, 0, sizeof(visit));
	fill(dist, dist+NMAX, BIG);
	dist[s] = 0;
	q[r] = s;
	visit[s] = true;
	while (f < r)
	{
		f++;
		i = q[f];	visit[i] = false;
		for (j=1; j<=n; j++)
			if (net[i][j] > 0 && dist[j] > dist[i] + cost[i][j])
			{
				if (!visit[j])
				{
					r++;
					q[r] = j;
					visit[j] = true;
				}
				dist[j] = dist[i] + cost[i][j];
				path[j] = i;
			}
	}
	return dist[t] != BIG;
}

int min_cost_max_flow()
{
    int mincost = 0, maxflow = 0;
    while( SPFA() )			//�����ڴ�s��t�����·������·��
	{
        int now = t;
        int neck = BIG;
        while(now != s) 			//�������·���ϵ���С��������
		{
            int pre = path[now];
            neck = min(neck, net[pre][now]);
            now = pre;
        }
        maxflow += neck;			//���������
        now = t;
        while(now != s) 			//����
		{
            int pre = path[now];
             net[pre][now] -= neck;					//�᲻����ɸ��������ᣡ
             net[now][pre] += neck;					//������
             cost[now][pre] = - cost[pre][now];		//���·���ߵĴ���
             mincost += cost[pre][now] * neck;		//������С����
             now = pre;
        }
    }
    return mincost;
}
int main()
{
    freopen("costflow.in","r",stdin);
    freopen("costflow.out","w",stdout);
    init();
    ans = min_cost_max_flow();
    printf("%d\n",ans);
    return 0;
}
