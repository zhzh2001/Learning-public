#include <cstdio>
#include <cstring>
const int MAXN=1511,INF=(1<<30)-1;
int c[MAXN][MAXN];			//��������
int d[MAXN],vd[MAXN];		//d[]:������, vd[]:���Ϊi�Ľ�����
int n,m,flow;
inline int min(int x,int y){return x<y?x:y;}
void init()
{
	scanf("%d%d",&m,&n);
	for(int i=1;i<=m;i++)
	{
		int j,k,wt;
		scanf("%d%d%d",&j,&k,&wt);
		c[j][k]+=wt;
	}
}
int Min(int a,int b) {return a<b?a:b;}
int aug(int i,int augco)   //i:����, augco:��iΪ���������������     
{
	int j, augc = augco, mind = n-1, delta;
	if(i==n) 			   //������
	  return augco;
	
	for(j = 1;j <= n; j++) //ö��i���ڽӵ�
		if(c[i][j]>0)	   //����бߵ�j	
		{
			if(d[i]==d[j]+1)  //(i,j)Ϊ�ɽ��뻡
			{
				delta = min(augc,c[i][j]);  //�����(i,j)�Ŀ��������ֵ
				delta = aug(j,delta);       //�ݹ����㣬������(i,j)��ʵ��������
				c[i][j] -= delta;			//���²�������
				c[j][i] += delta;			
				augc -= delta;				//augc��¼ʣ�µ���Ҫ�������
				if(d[1]>=n)					//����������һ�㷵�ؾ���i��ʵ��������
					return augco-augc;
				if(augc == 0) break;        //�Ѿ�����������Ͻ磬��ǰ����
			}
			if (mind<d[j])  mind = d[j];    //������С���ڽӵ���
		}
	if(augco==augc)                         //�����i���޷����� 
	{
		vd[d[i]]--;							//���Ϊd[i]�Ľ����-1
		if(vd[d[i]] ==0 )					//GAP�Ż�
    		d[1] = n;
		d[i] = mind + 1;					//���±��
		vd[d[i]]++;							//�±�ŵĽ����+1
    }
	return augco-augc;			//����һ�㷵�ؾ���i��ʵ��������					
}
void sap()
{
	memset(d,0,sizeof(d));
	memset(vd,0,sizeof(vd));
	vd[0] = n;
	while(d[1] < n)
		flow+=aug(1,INF);
}
int main()
{
	freopen("ditch.in","r",stdin);
    freopen("ditch.out","w",stdout);
	init();
	sap();
	printf("%d\n",flow);
	return 0;
}
