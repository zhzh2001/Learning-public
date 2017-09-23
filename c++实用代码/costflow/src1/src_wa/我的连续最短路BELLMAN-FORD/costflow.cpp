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
bellman_ford()���Ի�ΪSPFA���ٶȿ��ܻ����
ͼ���ڽӱ����ܻ����
��ǰ�㷨����BZOJ1292��10�������У�������Ҫ8���һ��

Task1 [204MS] right
Task2 [281MS] right
Task3 [469MS] right
Task4 [954MS] right
Task5 [1531MS] right
Task6 [2375MS] right
Task7 [3219MS] right
Task8 [4766MS] right
Task9 [6687MS] right
Task10 [8703MS] right

Accepted  10/10
All right task [29189MS]

*/
#include <iostream>
using namespace std;
const int NMAX = 512;
int net[NMAX][NMAX], cost[NMAX][NMAX];
int path[NMAX], dist[NMAX];
int n, m, ans, s, t;	//s:Դ��, t:���
void init()
{
    int i, j, k, c, d;
    scanf("%d%d", &n, &m);
    for (i=1; i<=n; i++)
    {
        for (j=1; j<=n; j++)
          cost[i][j] = INT_MAX;
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
bool bellman_ford()	//���Դ��s�����n�����·
{
    int i,j;
     memset(path,-1,sizeof(path));
     fill(dist, dist+NMAX, INT_MAX);
     dist[s] = 0;

    bool flag = true;		//��־�ܷ��ɳ�
    while(flag) 
	{
        flag = false;
        for(i=1;i<=n;i++) 
		{
            if(dist[i] == INT_MAX)  continue ;
            
            for(j=1;j<=n;j++) 
			{
			    //����в����������ҿ��ɳ�
                if(net[i][j] > 0 && dist[j] > dist[i]+cost[i][j] ) 
				{
                     flag = true;
                     dist[j] = dist[i]+cost[i][j];	//����j�ľ���
                     path[j] = i;					//����j��ǰ��
                }
            }
        }
    }
    return dist[t] != INT_MAX;		//���ػ��n�Ƿ񻹿ɴ�
}

int min_cost_max_flow()
{
    int mincost = 0, maxflow = 0;
    while( bellman_ford() )			//�����ڴ�s��t�����·������·��
	{
        int now = t;
        int neck = INT_MAX;
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
