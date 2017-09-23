#include<iostream>
using namespace std;
const int MAXN = 110;
typedef int AdjTable[MAXN] ; // �ڽӱ�����
int n;
int intm[MAXN] ; // ��ǽ��붥��ʱ��
int belg[MAXN] ; // �洢ǿ��ͨ���� , ���� belg[i] ��ʾ���� i ���ڵ� belg[ i] ��ǿ��ͨ����
int stk1[MAXN] ; // ������ջ
int stk2[MAXN] ; // ������ջ
AdjTable adj[MAXN] ; // �ڽӱ�
// ���ѹ��� , ���㷨�����嶼������
void Visit(int cur, int &sig, int &scc_num)
{
	int i;
	intm[cur ] = ++sig;
	stk1[++stk1[0]] = cur ;
	stk2[++stk2[0]] = cur ;
	for ( i = 1; i <= adj[cur][0]; ++i )
	{
		if ( 0 == intm[adj[cur][ i] ] )
		{
			Visit(adj[cur ][i], sig, scc_num);
		}
		else if ( 0 == belg[adj[cur][ i]] )
		{
			while ( intm[stk2[stk2[0] ]] > intm[adj[cur][ i]] )
			{
				-- stk2[0];
			}
		}
	}
	if ( stk2[stk2[0] ] == cur )
	{
		-- stk2[0];
		++ scc_num;
		do
		{
			belg[stk1[stk1[0] ]] = scc_num;
		}
		while ( stk1[stk1[0]--] != cur );
	}
}
//Gabow �㷨,��� belg[1..n],�ҷ���ǿ��ͨ��������
int Gabow_StronglyConnectedComponent()
{
	int i, sig, scc_num;
	memset(belg + 1, 0, sizeof(int)*n) ;
	memset( intm + 1, 0, sizeof(int)*n) ;
	sig = 0;
	scc_num = 0;
	stk1[0] = 0;
	stk2[0] = 0;
	for ( i = 1; i <= n; ++i )
	{
		if ( 0 == intm[i] )
		{
			Visit(i, sig, scc_num) ;
		}
	}
	return scc_num;
}
int main(){
	system("pause");
	return 0;
}


