#include<bits/stdc++.h>
using namespace std;
ifstream fin("fact.in");
ofstream fout("fact.out");
int main()
{
	int n,k;
	fin>>n>>k;
	long double lg=.0L;
	for(int i=1;i<=n;i++)
		lg+=log10((long double)i);
	int len=floor(lg);
	fout.precision(k);
	fout<<pow(10.0L,lg-len)<<"e+"<<len<<endl;
	return 0;
}