void CutBlock(int v)
{
	dfn[v] = low[v] = ++cnt;
	st[++top] = v;
	for(int i = p[v]; i != -1; i = edge[i].pre)
	{
		int u(edge[i].d);
		if(dfn[u] == 0)
		{
			CutBlock(u);
			GetMin(low[v], low[u]);
			if(low[u] >= dfn[v]) //V ��һ�����
			{
				block[0] = 0;
				while (true)
				{
					block[++block[0]] = st[top];
					if (st[top--] == u) // ֻ�ܵ��� u Ϊֹ�� v ����������������
						break;
				}
				block[++block[0]] = v; // ������ڶ���� �� һ��Ҫ����ȥ
				Count(block);
			}
		}
		else GetMin(low[v], dfn[u]);
	}
}


