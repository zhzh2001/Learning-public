#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<iostream>
using namespace std;
#define bigint __int64
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
//Miller_Rabin�������ж�
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
bigint pollard_rho(bigint C, bigint N) //����һ��ƽ������
{
    bigint I, X, Y, K, D;
    I = 1;
    X = Y = rand() % N;
    K = 2;
    do
    {
        I++;
        D = gcd(N + Y - X, N);//����Ϊ�˷�ֹ�������ȼ���һ��N
        if (D > 1 && D < N) return D;//���D���Ƿ�ƽ������
        if (I == K) Y = X, K <<= 1;
        X = (product_mod(X, X, N) + N - C) % N;//���һ����������X,Y��ʹ��gcd(Y - X,N)���Ƿ�ƽ������(����1����N)
    }
    while (Y != X);
    return N;
}
//���֣��ֽ�N��������,���ﷵ����С�����ӣ������Ҫ�����Ļ��������ø����������
bigint rho(bigint N)
{
    if(Miller_Rabin(N))
        return N;
    bigint T = N;
    while(T >= N)
        T = pollard_rho(rand() % (N - 1) + 1, N);
    bigint A = rho(T);
    bigint B = rho(N / T);
    return A < B ? A : B;
}
int main()
{
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    bigint n, p;
    cin >> n;
    while (n != 1)
    {
        p = rho(n);
        cout << p << endl;
        n/=p;
        //break;
    }
    system("pause");
    return 0;
}


