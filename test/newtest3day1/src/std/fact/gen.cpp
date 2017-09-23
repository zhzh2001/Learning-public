#include<bits/stdc++.h>
using namespace std;
const int t=10000,k=10;
ofstream fout("fact.in");
int main()
{
	minstd_rand gen(time(NULL));
	uniform_int_distribution<long long> dn(0,1e18);
	fout<<t<<endl;
	for(int i=1;i<=t;i++)
		fout<<dn(gen)<<' '<<k<<endl;
	return 0;
}