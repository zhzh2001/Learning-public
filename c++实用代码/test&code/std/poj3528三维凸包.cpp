#include<iostream>
using namespace std;
#include<cmath>
#include<cstring>
#include<cstdio>
#define N 505
#define eps 0.000001
struct Point
{
	double x,y,z;
	Point(){}
	Point(double _x,double _y,double _z)
	{
		x=_x;
		y=_y;
		z=_z;
	}
	Point operator-(Point t1)//��������
	{
		return Point(x-t1.x,y-t1.y,z-t1.z);
	}
	Point operator*(Point t2)//���
	{
		return Point(y*t2.z-t2.y*z,z*t2.x-x*t2.z,x*t2.y-y*t2.x);
	}
	double operator^(Point t3)//���
	{
		return x*t3.x+y*t3.y+z*t3.z;
	}
};
struct Plane
{
	int a,b,c;//a,b,cΪ������ı�ţ�a,b,cҪ�����͹�����濴������ϵ
	bool in;//��ʾ��ƽ���Ƿ���͹����
};
void Swap(Point &a,Point &b)
{
	Point c;
	c=a;
	a=b;
	b=c;
}
Point point[N];
Plane plane[N*10];
int edge[N][N];
int plen;//���������ĸ���
void dfs(int p,int t);
double vol(Point p,Plane f)//p��ƽ��abc��ɵ����������������ı�
{
	Point a=point[f.a]-p,b=point[f.b]-p,c=point[f.c]-p;
	return (a*b)^c;
}
double vlen(Point a)//������a��ģ
{
	return sqrt(a.x*a.x+a.y*a.y+a.z*a.z);
}
void deal(int p,int t1,int t2)
{
	int t=edge[t1][t2];//������ñ����ڵ�����һ��ƽ��
	if(plane[t].in)
	{
		if(vol(point[p],plane[t])>eps)
			dfs(p,t);
		else
		{
			Plane add;
			add.a=t2,add.b=t1,add.c=p,add.in=true;//����ע��˳�򣬾Ϳ��Բ���Swap�ˣ�add.a,add.b,add.cҪ������ϵ
			edge[add.a][add.b]=edge[add.b][add.c]=edge[add.c][add.a]=plen;
			plane[plen++]=add;
		}
	}
}
void dfs(int p,int t)//�ݹ���������Ӧ�ô�͹����ɾ������
{
	plane[t].in=false;
	deal(p,plane[t].b,plane[t].a);//ע�⣬a��b��˳��պø�������෴��Ϊ�ľ����������(point[plane[t].a],point[plane[t].b])���ڵ�����һ��ƽ��
	deal(p,plane[t].c,plane[t].b);
	deal(p,plane[t].a,plane[t].c);
}
int del(int n)//����������n���㣬���ؼ������ƽ����������޷�����͹�����򷵻�-1
{
	if(n<4)//�������С�ڣ����޷�����͹�������ѱ�֤�������ڻ���ڣ�����ȥ
		return -1;
	//*****************��һ��������֤ǰ�ĵ㲻���棬���ѱ�֤������ȥ
	bool allTheSamePoint=true;
	for(int i=1;i<n;i++)//��֤ǰ���㲻����
	{
		if(vlen(point[i]-point[0])>eps)
		{
			Swap(point[1],point[i]);
			allTheSamePoint=false;
			break;
		}
	}
	if(allTheSamePoint)
		return -1;
	bool allTheSameLine=true;
	for(int i=2;i<n;i++)//��֤ǰ���㲻����
	{
		if(vlen((point[1]-point[0])*(point[i]-point[1]))>eps)
		{
			Swap(point[2],point[i]);
			allTheSameLine=false;
			break;
		}
	}
	if(allTheSameLine)
		return -1;
	bool allTheSamePlane=true;
	for(int i=3;i<n;i++)//��֤ǰ�ĵ㲻����
	{
		if(fabs((point[1]-point[0])*(point[2]-point[0])^(point[i]-point[0]))>eps)
		{
			Swap(point[3],point[i]);
			allTheSamePlane=false;
			break;
		}
	}
	if(allTheSamePlane)
		return -1;
	//��һ��������֤ǰ�ĵ㲻���棬���ѱ�֤������ȥ***********
	plen=0;//���������ĸ���
	Plane add;
	for(int i=0;i<4;i++)
	{
		add.a=(i+1)%4,add.b=(i+2)%4,add.c=(i+3)%4,add.in=true;
		if(vol(point[i],add)>0)
			swap(add.a,add.b);
		edge[add.a][add.b]=edge[add.b][add.c]=edge[add.c][add.a]=plen;//��¼��ñ����ڵ�����һ���棬���Ҹ�˳���ڸ����ڣ���͹���⿴��������ϵ����ˣ�������Ψһ��
		plane[plen++]=add;
	}
	for(int i=4;i<n;i++)
	{
		for(int j=0;j<plen;j++)
		{
			if(plane[j].in && vol(point[i],plane[j])>eps)
			{
				dfs(i,j);
				break;
			}
		}
	}
	return plen;
}
double area(Plane a)
{
	return vlen((point[a.b]-point[a.a])*(point[a.c]-point[a.a]))/2.0;
}

int main()
{
	int n;
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>point[i].x>>point[i].y>>point[i].z;
	int len=del(n);
	if(len==-1)
		printf("0.000\n");
	else
	{
		double ans=0.0;
		for(int i=0;i<len;i++)
		{
			if(plane[i].in)
			{
				ans+=area(plane[i]);
			}
		}
		printf("%.3lf\n",ans);
	}
return 0;
}


