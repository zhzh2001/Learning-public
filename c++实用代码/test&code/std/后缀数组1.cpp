#include<stdio.h>
#include<string.h>
#include<stdlib.h>
//#include<math.h>
#define MAX 300
int wx[MAX],wy[MAX],bar[MAX],nrank[MAX];
int sa[MAX],height[MAX];
//int query[MAX][30];
int cmp(int *in,int a,int b,int l)
{
	return in[a] == in[b]&&in[a+l] == in[b+l];
}
int min(int x,int y)
{
	return x > y ? y : x;
}
/*void get_query(int *ai,int len)
{
	int i,k;
	for (i = 0; i< len; i++)
		query[i][0] = ai[i];
	for (k = 1;(int)pow(2.0,k) - 1 < len; k++)
		for (i = 0; i < len; i++)
			if (i + (int)pow(2.0,k) - 1 < len)
				query[i][k] = min(query[i][k-1],query[i+(int)pow(2.0,k-1)][k-1]);
			else break;
}*/
void get_sa(char *s,int *sa)
{
	int len = strlen(s)-1,*rank = wx,*sa_y = wy,*t,i,m = 255;
	for (i = 0; i<= m; i++) bar[i] = 0;
	for (i = 0; i< len; i++) bar[rank[i] = s[i]]++;
	for (i = 0; i< m; i++) bar[i+1] += bar[i];
	for (i = len-1; i>= 0; i--)	sa[--bar[rank[i]]] = i;
	//sa���鱣�����ĳ�����ʵĺ�׺����ʼλ�ã���k=1ʱ�������õ���Ͱ������һ��һ����Ͱ��Ȼ���ٵ�����
	for (int p = 1,k = 1; p < len; k *= 2,m = p)
	{
		for (p = 0,i = len-k; i < len; i++) sa_y[p++] = i;
		for (i = 0; i< len; i++) if (sa[i] >= k) sa_y[p++] = sa[i] - k;
		//Ҫ��2k-ǰ׺��sa������k-ǰ׺�����õ�����y���鱣��2k-ǰ׺ʱ�ڶ��ؼ��ֵ�����������k-ǰ׺ʱĳλ��+k��sa����
		//���׵õ�k-ǰ׺ʱĳλ��+k��һЩ�Ѿ�������s�ķ�Χ������һЩλ�ò�����Ϊ�ڶ��ؼ�����ʼλ�ã����Կ��������ǵ���Ŀ����ȵ�
		for (i = 0; i< len; i++) nrank[i] = rank[sa_y[i]];
		for (i = 0; i<= m; i++) bar[i] = 0;
		for (i = 0; i< len; i++) bar[nrank[i]] ++;
		for (i = 0; i< m; i++) bar[i+1] += bar[i];
		for (i = len-1; i>= 0; i--) sa[--bar[nrank[i]]] = sa_y[i];
		//�Թ��ڵڶ��ؼ����ź���������ٰ���һ�ؼ��������õĻ���Ͱ����nrank[i]��¼���ǰ��ڶ��ؼ����ź����Ժ�����еĵ�һ�ؼ�����������
		for (t = sa_y,sa_y = rank,rank = t,p = 1,rank[sa[0]] = 0,i = 1; i < len; i++)
			rank[sa[i]] = cmp(sa_y,sa[i-1],sa[i],k)?p-1:p++;
		//��δ������µ�rank���飬ԭ����rank��sa_y�����棬�Ƚ��������ڵ�������׺�ĵ�һ�͵ڶ��ؼ����Ƿ���ȫһ����ȷ����ͬ��׺����Ŀ����p��¼
	}
}
void get_height(char *s,int *sa,int *height)
{
	int len = strlen(s),*rank = wx,i,j,k = 0;
	for (i = 0; i < len; i++) rank[sa[i]] = i;
	for (i = 0; i < len-1; height[rank[i++]] = k)
		for (k?k--:0,j = sa[rank[i] - 1]; s[i+k] == s[j+k]; k++) printf("%d %d %d\n",k,i,j);
	//����height�õ��˸�������h����δ�����û�б���h��ֻ�ǰ���h��0��len-2��˳�����ģ���δ���ǳ�����forѭ���õĳ����뻯
	//h����Ķ���Ϊh[i] = height[rank[i]],���Դ������ú���ֱ�Ӵ�����ǰ�ߣ�h������һ������ h[i] >= h[i-1] - 1��֤����������
	//���ݹ��ɣ��Ϳ��԰���˳�����h���飬���㷽����������������޵���������
	return;
}
int main()
{
	
	char str[MAX]; int len,i;
	memset(str,0,sizeof(str));
	scanf ("%s",&str);
	len = strlen(str);
	str[len] = '$';str[len+1]='\0';
	get_sa(str,sa);
	 
    //��ӡsa����
	printf ("****sa****\n");
	for (i = 0; i< len; i++)
		printf ("%d %d\n",i,sa[i]);
	printf ("**********\n");

	system("pause");
	get_height(str,sa,height);
	//get_query(height,len);
	for (;;);
	return 0;
}
