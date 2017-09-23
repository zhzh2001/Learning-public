#include<bits/stdc++.h>
#include<mpreal.h>
using namespace std;
using namespace mpfr;
const int digits=100,len=323228480;
const mpreal huge="1e323228480";
int main()
{
	int n;
	cin>>n;
	mpreal::set_default_prec(digits2bits(digits));
	mpreal ans=1.0;
	int cnt=0;
	for(int i=1;i<=n;i++)
	{
		ans*=i;
		if(ans>huge)
		{
			ans/=huge;
			cnt++;
		}
	}
	cout.precision(digits);
	cout<<ans<<' '<<(long long)cnt*len<<endl;
	return 0;
}