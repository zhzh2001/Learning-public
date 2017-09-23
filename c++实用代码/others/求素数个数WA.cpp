#include<iostream>
#include<math.h>
#include<windows.h>
using namespace std;
const   unsigned   default_n = 2000000000;
const   int   maxlen = 1000;

int   primes[maxlen];
int   len;
int   sum;
unsigned   int   n;
int   m = 7;
int   Q = 1;
int   phiQ = 1;
int   *v;

bool   string2int(unsigned   int   &n, char   *s);
void   init(void);
unsigned   int   phi(unsigned   int   x, int   a);

int   main()
{

	char   number_string[80];
	unsigned   int   time;

	cout << "calc   pi(n)\n";
	cout << "n(default   =   " << default_n << ")   =   ";
	cin.get(number_string, 80);
	if(!string2int(n, number_string))n = default_n;

	time = GetTickCount();
	init();
	//phi(n,len)��ʾ0-n��prime[0--len]���ʣ������ж�Ӳ��֣�����Ҫ-sum;��phi������prime[0--len]����Ҫ+len
	int   num = (int)phi(n, len) - sum + len - 1;
	time = GetTickCount() - time;
	GlobalFree(v);
	cout << "pi(n)=" << num << "(" << time << "ms)\n";
	cout << "press   any   key   to   continue...";
	cin.get();
	cin.get();
}

void   init(void)
{
	int   max;
	int   sqrt_max;
	bool   *mark;
	int   i, j;
	int   len2, len3;
	int   s;
	int   sqrt_n;

	sqrt_n = (int)sqrt(n);
	max = (int)pow(n, 2.0 / 3.0);
	sqrt_max = (int)sqrt(max);
	mark = (bool *)GlobalAlloc(GMEM_FIXED | GMEM_ZEROINIT, max);

	//i��2��ʼ--n^1/3��
	//mark���0--n^2/3��������primes[]����0-n^1/3������
	//len��ʾ0-n^1/3����������
	//ɸѡ��
	for(i = 2, len = 0; i < sqrt_max; i++)
	{
		if(!mark[i])
		{
			j = i * i;
			primes[++len] = i;
			while(j < max)
			{
				mark[j] = true;
				j += i;
			}
		}
	}
	//i��n^1/3��ʼ--n^1/2��
	//j��n^2/3��ʼ��i������j�Լ�
	//sum��ʾ0--n^2/3��n^1/3--n^1/2֮�������˻�>n���ĸ���
	//len2��ʾ0-n^1/2����������
	for(j = max - 1, sum = 0, s = 0, len2 = len; i <= sqrt_n; i++)
	{
		if(!mark[i])
		{
			++len2;
			while((unsigned)i * j > n)
			{
				if(!mark[j--])++s;
			}
			sum += s;
		}
	}

	//i��n^1/2��ʼ--n^2/3��
	//len3��ʾ0-n^2/3����������
	for(len3 = len2; i < max; i++)
	{
		if(!mark[i])++len3;
	}

	//sum������Ϲ�ʽ
	//��len->len2��len2-len3֮�������ĳ˻�����
	//��n^1/3--n^1/2��n^1/2--n^2/3֮�������ĳ˻�����

	sum = (len2 - len) * len3 - sum;
	sum += len * (len - 1) / 2 - len2 * (len2 - 1) / 2;

	//ŷ������
	//m=7
	//Q=2*3*5*7*11*13*17=510510
	//phiQ=1*2*4*6*10*12*16
	if(m > len)m = len;
	for(i = 1; i <= m; ++i)
	{
		Q *= primes[i];
		phiQ *= primes[i] - 1;
	}
	//v
	v = (int *)GlobalAlloc(GMEM_FIXED, Q * sizeof(int));
	for(i = 0; i < Q; ++i)v[i] = i;
	for(i = 1; i <= m; ++i)
	{
		for(j = Q - 1; j >= 0; --j)
		{
			v[j] -= v[j/primes[i]];
		}
	}

	GlobalFree(mark);
}

bool   string2int(unsigned   int   &n, char   *s)
{
	unsigned   int   val = 0;
	for(int   i = 0; s[i]; ++i)
	{
		if(s[i] > '9' || s[i] < '0')return   false;
		val *= 10;
		val += s[i] - '0';
		if(val > default_n)return   false;
	}
	n = val;
	return   true;
}

//С��x,������prime[0]---prime[a]֮����������ʵ�������Ŀ
//���Ҳ�����prime[0]--prime[a]
//�ݹ�ԭ��
//phi(x,a)=phi(x,a-1)-phi(x/prime[a],a-1)
//phi(x,a)��ʾС��x,������prime[0]---prime[a]֮����������ʵ�������Ŀ
//phi(x,a-1)��ʾС��x,������prime[0]---prime[a-1]֮����������ʵ�������Ŀ
//phi(x/prime[a],a-1)��ʾС��x/prime[a],������prime[0]---prime[a-1]֮����������ʵ�������Ŀ
//��0--x֮����prime[0]---prime[a]֮����������ʵ�������Ŀ
//���ǿ������0--x֮����prime[0]---prime[a-1]֮����������ʵ�������Ŀ
//��������ʵ���϶������Щ0--x֮����prime[0]---prime[a-1]֮����������ʣ�����prime[a]�ı���������������Ҫ��ȥ���ǣ����ǵĸ�������phi(x/prime[a],a-1)
unsigned   int   phi(unsigned   int   x, int   a)
{
	if(a == m)
	{
		return   (x / Q) * phiQ + v[x%Q];
	}
	if(x < (unsigned)primes[a])
	{
		return   1;
	}
	return   phi(x, a - 1) - phi(x / primes[a], a - 1);
}


