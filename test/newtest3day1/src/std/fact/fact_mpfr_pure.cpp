#include<bits/stdc++.h>
#include<mpreal.h>
using namespace std;
using namespace mpfr;
ifstream fin("fact.in");
ofstream fout("fact.out");
const int digits=100;
int main()
{
	int n,k;
	fin>>n>>k;
	mpreal::set_default_prec(digits2bits(digits));
	mpreal ans=1.0;
	for(int i=1;i<=n;i++)
		ans*=i;
	fout.precision(k);
	fout<<ans<<endl;
	return 0;
}