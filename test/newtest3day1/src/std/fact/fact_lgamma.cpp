#include<fstream>
#include<cmath>
using namespace std;
ifstream fin("fact.in");
ofstream fout("fact.out");
int main()
{
	long long n;
	int k;
	fin>>n>>k;
	long double ans=lgamma(n+1.0L)/log(10.0L);
	unsigned long long len=floor(ans);
	fout.precision(k);
	fout<<pow(10.0L,ans-len)<<"e+"<<len<<endl;
	return 0;
}