#include<bits/stdc++.h>
using namespace std;
int main()
{
	int n;
	cin>>n;
	long double ans=1;
	for(int i=1;i<=n;i++)
	{
		ans*=i;
		cout<<i<<"!="<<ans<<endl;
	}
	return 0;
}