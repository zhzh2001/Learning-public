#include<bits/stdc++.h>
using namespace std;
ofstream fout("task4_3.in");
const int N=200005,W=1e9;
pair<int,int> p[N];
int main()
{
	minstd_rand gen(time(NULL));
	int cc=0;
	for(int i=242546636;i<=W;i+=18562374)
		for(int j=549879641;j<=549884341;j++)
			p[++cc]=make_pair(i,j);
	for(int i=1;i<=6666;i++)
	{
		uniform_int_distribution<> d(0,1e9);
		p[++cc]=make_pair(d(gen),d(gen));
	}
	shuffle(p+1,p+cc+1,gen);
	fout<<cc<<endl;
	for(int i=1;i<=cc;i++)
		fout<<p[i].first<<' '<<p[i].second<<endl;
	return 0;
}