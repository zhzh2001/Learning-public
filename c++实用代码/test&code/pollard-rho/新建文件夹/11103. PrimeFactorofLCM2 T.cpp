#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<set>
#include<iostream>
using namespace std;
#define bigint long long
bigint gcd(bigint a, bigint b)
{
    while(b)
    {
        bigint c = a % b;
        a = b;
        b = c;
    }
    return a;
}
//a*b%n
bigint product_mod(bigint a, bigint b, bigint n)
{
    bigint tmp = 0;
    while(b)
    {
        if(b & 1)
        {
            tmp += a;
            if(tmp >= n) tmp -= n;
        }
        a <<= 1;
        if(a >= n) a -= n;
        b >>= 1;
    }
    return tmp;
}
//a^m%n
bigint power_mod(bigint a, bigint m, bigint n)
{
    bigint tmp = 1;
    a %= n;
    while(m)
    {
        if(m & 1) tmp = product_mod(tmp, a, n);
        a = product_mod(a, a, n);
        m >>= 1;
    }
    return tmp;
}
int pri[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
//Miller_Rabin大素数判断
bool Miller_Rabin(bigint n)
{
    if(n < 2) return false;
    if(n == 2) return true;
    if(!(n & 1)) return false;
    bigint k = 0 , i , j , m , a;
    m = n - 1;
    while(!(m & 1)) m >>= 1, k++;
    for(i = 0 ; i < 10 ; i ++)
    {
        if(pri[i] >= n) return true;
        a = power_mod(pri[i], m, n);
        if(a == 1) continue;
        for(j = 0 ; j < k ; j ++)
        {
            if(a == n - 1) break;
            a = product_mod(a, a, n);
        }
        if(j == k) return false;
    }
    return true;
}
bigint pollard_rho(bigint C, bigint N) //返回一个平凡因子
{
    bigint I, X, Y, K, D;
    I = 1;
    X = Y = rand() % N;
    K = 2;
    do
    {
        I++;
        D = gcd(N + Y - X, N);//这里为了防止负数，先加上一个N
        if (D > 1 && D < N) return D;//如果D不是非平凡因子
        if (I == K) Y = X, K <<= 1;
        X = (product_mod(X, X, N) + N - C) % N;//随机一个增量来求X,Y，使得gcd(Y - X,N)不是非平凡因子(不是1，跟N)
    }
    while (Y != X);
    return N;
}
//二分，分解N的质因数,这里返回最小质因子，如果想要其他的话，可以用个数组存起来
bigint rho(bigint N)
{
    if(Miller_Rabin(N))return N;
    bigint T = N;
    while(T >= N){
		T = pollard_rho(rand() % (N - 1) + 1, N);
		return T;
		//cout<<"T="<<T<<"\n";
	}
}
set<bigint> zzy;
bigint queue[100005];
void calc(){
	int h,t,N,p;scanf("%d",&N);
	h=1;t=N;
	for (int i=1;i<=N;++i)cin>>queue[i];
	while (h<=t){
		p=rho(queue[h]);
		if (p==queue[h])zzy.insert(p);
			else queue[++t]=p,queue[++t]=queue[h]/p;
		++h;
	}
}
int main()
{
    //freopen("1.in","r",stdin);
    //freopen("2.out","w",stdout);
    int T;
    scanf("%d",&T);
    for (int i1=1;i1<=T;++i1){
		zzy.clear();calc();
		int s=0;
		for (set<bigint>::iterator dhh=zzy.begin();dhh!=zzy.end();++dhh)
			++s;
		printf("Case #%d: %d\n",i1,s);
    	for (set<bigint>::iterator dhh=zzy.begin();dhh!=zzy.end();++dhh)
			cout<<*dhh<<"\n";
	}
    //system("pause");
    return 0;
}


