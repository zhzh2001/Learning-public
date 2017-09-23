#include<fstream>
#include<cmath>
#include<thread>
using namespace std;
ifstream fin("fact.in");
ofstream fout("fact.out");
const long double huge=1e4000L;
const int len=4000;
void calc(int l,int r,long double& ans,int& cnt)
{
	ans=1.0L;
	cnt=0;
	for(int i=l;i<=r;i++)
	{
		ans*=i;
		if(ans>huge)
		{
			cnt++;
			ans/=huge;
		}
	}
}
int main()
{
	int n,k;
	fin>>n>>k;
	long double ans1,ans2;
	int cnt1,cnt2;
	thread th1(calc,1,n/2,ref(ans1),ref(cnt1));
	thread th2(calc,n/2+1,n,ref(ans2),ref(cnt2));
	th1.join();
	th2.join();
	int t1=floor(log10(ans1)),t2=floor(log10(ans2));
	ans1/=pow(10.0L,t1);
	ans2/=pow(10.0L,t2);
	ans1*=ans2;
	if(ans1>=10.0L)
	{
		t1++;
		ans1/=10.0L;
	}
	fout.precision(k);
	fout<<ans1<<"e+"<<(long long)(cnt1+cnt2)*len+t1+t2<<endl;
	return 0;
}