#include<bits/stdc++.h>
#include<gmpxx.h>
using namespace std;
ifstream fin("fact.in");
ofstream fout("fact.out");
int main()
{
	int n,k;
	fin>>n>>k;
	mpz_class ans;
	mpz_fac_ui(ans.get_mpz_t(),n);
	stringstream ss;
	ss<<ans;
	int len=ss.str().length();
	string s;
	if(len<=k)
	{
		s=ss.str();
		for(int i=len+1;i<=k;i++)
			s=s+'0';
	}
	else
	{
		s=ss.str().substr(0,k);
		if(ss.str()[k]>='5')
		{
			stringstream ss1(s);
			long long t;
			ss1>>t;
			t++;
			stringstream ss2;
			ss2<<t;
			s=ss2.str();
		}
	}
	while(s[s.length()-1]=='0')
		s.erase(s.length()-1);
	if(k>1)
		fout<<s[0]<<'.'<<s.substr(1)<<"e+"<<len-1<<endl;
	else
		fout<<s[0]<<"e+"<<len-1<<endl;
	return 0;
}