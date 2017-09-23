#include<fstream>
#include<mpreal.h>
using namespace std;
using namespace mpfr;
ifstream fin("fact.in");
ofstream fout("fact.ans");
const int digits=100;
int main()
{
	long long n;
	int k;
	fin>>n>>k;
	mpreal::set_default_prec(digits2bits(digits));
	mpreal ans=lngamma((mpreal)n+"1.0")/log((mpreal)"10.0");
	unsigned long long len=(unsigned long long)floor(ans);
	fout.precision(k);
	fout<<pow((mpreal)"10.0",ans-len)<<"e+"<<len<<endl;
	return 0;
}