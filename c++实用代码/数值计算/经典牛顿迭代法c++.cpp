#include<iostream>
#include<cmath>
#define N 2  // �����Է������з��̸�����δ֪������ 
#define Epsilon 0.0001  // ������1����������
#define Max 100  //����������
using namespace std;
const int N2 = 2 * N;
int main()
{
	void ff(float xx[N], float yy[N]); //�����������������������yy[N]
	void ffjacobian(float xx[N], float yy[N][N]); //�����ſ˱Ⱦ���yy[N][N]
	void inv_jacobian(float yy[N][N], float inv[N][N]); //�����ſ˱Ⱦ���������inv
	void newdundiedai(float x0[N], float inv[N][N], float y0[N], float x1[N]); //�ɽ��ƽ����� x0 ������ƽ����� x1
	float x0[N] = {2.0, 0.25}, y0[N], jacobian[N][N], invjacobian[N][N], x1[N], errornorm;
	int i, j, iter = 0;
	//���ȡ����x0�ĳ�ʼ���������������е�ע�ͷ����Ϳ����ɼ�����x0�����ʼ���ƽ�����
	//for( i=0;i<N;i++)
	//	cin>>x0[i];
	cout << "��ʼ���ƽ�������" << endl;
	for (i = 0; i < N; i++)
		cout << x0[i] << "  ";
	cout << endl;
	cout << endl;
	do
	{
		iter = iter + 1;
		cout << "�� " << iter << " �ε�����ʼ" << endl;
		//����������������������� y0
		ff(x0, y0);
		//�����ſ˱Ⱦ��� jacobian
		ffjacobian(x0, jacobian);
		//�����ſ˱Ⱦ��������� invjacobian
		inv_jacobian(jacobian, invjacobian);
		//�ɽ��ƽ����� x0 ������ƽ����� x1
		newdundiedai(x0, invjacobian, y0, x1);
		//�����������1����errornorm
		errornorm = 0;
		for (i = 0; i < N; i++)
			errornorm = errornorm + fabs(x1[i] - x0[i]);
		if (errornorm < Epsilon) break;
		for (i = 0; i < N; i++)
			x0[i] = x1[i];
	}
	while (iter < Max);
	system("pause");
	return 0;
}

void ff(float xx[N], float yy[N])
{
	float x, y;
	int i;
	x = xx[0];
	y = xx[1];
	yy[0] = x * x - 2 * x - y + 0.5;
	yy[1] = x * x + 4 * y * y - 4;
	cout << "��������������������ǣ� " << endl;
	for( i = 0; i < N; i++)
		cout << yy[i] << "  ";
	cout << endl;
	cout << endl;
}

void ffjacobian(float xx[N], float yy[N][N])
{
	float x, y;
	int i, j;
	x = xx[0];
	y = xx[1];
	//jacobian have n*n element
	yy[0][0] = 2 * x - 2;
	yy[0][1] = -1;
	yy[1][0] = 2 * x;
	yy[1][1] = 8 * y;
	cout << "�ſ˱Ⱦ����ǣ� " << endl;
	for( i = 0; i < N; i++)
	{
		for(j = 0; j < N; j++)
			cout << yy[i][j] << "  ";
		cout << endl;
	}
	cout << endl;
}

void inv_jacobian(float yy[N][N], float inv[N][N])
{
	float aug[N][N2], L;
	int i, j, k;
	cout << "��ʼ�����ſ˱Ⱦ��������� ��" << endl;
	for (i = 0; i < N; i++)
	{
		for(j = 0; j < N; j++)
			aug[i][j] = yy[i][j];
		for(j = N; j < N2; j++)
			if(j == i + N) aug[i][j] = 1;
			else  aug[i][j] = 0;
	}
	for (i = 0; i < N; i++)
	{
		for(j = 0; j < N2; j++)
			cout << aug[i][j] << "  ";
		cout << endl;
	}
	cout << endl;
	for (i = 0; i < N; i++)
	{
		for (k = i + 1; k < N; k++)
		{
			L = -aug[k][i] / aug[i][i];
			for(j = i; j < N2; j++)
				aug[k][j] = aug[k][j] + L * aug[i][j];
		}
	}
	for (i = 0; i < N; i++)
	{
		for(j = 0; j < N2; j++)
			cout << aug[i][j] << "  ";
		cout << endl;
	}
	cout << endl;
	for (i = N - 1; i > 0; i--)
	{
		for (k = i - 1; k >= 0; k--)
		{
			L = -aug[k][i] / aug[i][i];
			for(j = N2 - 1; j >= 0; j--)
				aug[k][j] = aug[k][j] + L * aug[i][j];
		}
	}
	for (i = 0; i < N; i++)
	{
		for(j = 0; j < N2; j++)
			cout << aug[i][j] << "  ";
		cout << endl;
	}
	cout << endl;
	for (i = N - 1; i >= 0; i--)
		for(j = N2 - 1; j >= 0; j--)
			aug[i][j] = aug[i][j] / aug[i][i];
	for (i = 0; i < N; i++)
	{
		for(j = 0; j < N2; j++)
			cout << aug[i][j] << "  ";
		cout << endl;
		for(j = N; j < N2; j++)
			inv[i][j-N] = aug[i][j];
	}
	cout << endl;
	cout << "�ſ˱Ⱦ��������� " << endl;
	for (i = 0; i < N; i++)
	{
		for(j = 0; j < N; j++)
			cout << inv[i][j] << "  ";
		cout << endl;
	}
	cout << endl;
}

void newdundiedai(float x0[N], float inv[N][N], float y0[N], float x1[N])
{
	int i, j;
	float sum = 0;
	for(i = 0; i < N; i++)
	{
		sum = 0;
		for(j = 0; j < N; j++)
			sum = sum + inv[i][j] * y0[j];
		x1[i] = x0[i] - sum;
	}
	cout << "���ƽ�������" << endl;
	for (i = 0; i < N; i++)
		cout << x1[i] << "  ";
	cout << endl;
	cout << endl;
}

