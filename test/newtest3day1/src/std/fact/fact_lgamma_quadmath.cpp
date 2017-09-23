#include<fstream>
#include<quadmath.h>
using namespace std;
ifstream fin("fact.in");
ofstream fout("fact.out");
int main()
{
	int n,k;
	fin>>n>>k;
	__float128 ans=lgammaq(n+1.0q)/M_LN10q;
	long long len=ans;
	char buf[100];
	quadmath_snprintf(buf,sizeof(buf),"%.*Qf",k-1,powq(10.0q,ans-len));
	string s(buf);
	while(s[s.length()-1]=='0')
		s.erase(s.length()-1);
	fout<<s<<"e+"<<len<<endl;
	return 0;
}