#include<bits/stdc++.h>
using namespace std;
ifstream fin("pair.in");
ofstream fout("pair.out");
const int N=200005;
pair<int,int> a[N];
long long dist(int x,int y)
{
	return (long long)(a[x].first-a[y].first)*(a[x].first-a[y].first)+(long long)(a[x].second-a[y].second)*(a[x].second-a[y].second);
}
int main()
{
	int n;
	fin>>n;
	for(int i=1;i<=n;i++)
		fin>>a[i].first>>a[i].second;
	long long ans=dist(1,2);
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			ans=min(ans,dist(i,j));
	fout<<ans<<endl;
	return 0;
}