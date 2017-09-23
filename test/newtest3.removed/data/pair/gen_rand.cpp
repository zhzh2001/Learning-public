#include<bits/stdc++.h>
using namespace std;
ofstream fout("task4_1.in");
const int n=200000;
int main()
{
	minstd_rand gen(time(NULL));
	fout<<n<<endl;
	for(int i=1;i<=n;i++)
	{
		uniform_int_distribution<> d(0,1e9);
		fout<<d(gen)<<' '<<d(gen)<<endl;
	}
	return 0;
}