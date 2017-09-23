#include<fstream>
#include<algorithm>
#include<vector>
#include<utility>
using namespace std;
ifstream fin("pair.in");
ofstream fout("pair.out");
const int N=200005;
const long long INF=0x3f3f3f3f3f3f3f3fll;
typedef pair<int,int> pii;
pii p[N];
long long solve(int l,int r)
{
	if(l==r)
		return INF;
	int mid=(l+r)/2,x=p[mid].first;
	long long d=min(solve(l,mid),solve(mid+1,r));
	sort(p+l,p+r+1,[](pii x,pii y)
	{
		return x.second<y.second;
	});
	vector<int> v;
	for(int i=l;i<=r;i++)
	{
		if((long long)(p[i].first-x)*(p[i].first-x)>=d)
			continue;
		for(int j=v.size()-1;j>=0;j--)
		{
			int dy=p[i].second-p[v[j]].second;
			if((long long)dy*dy>=d)
				break;
			int dx=p[i].first-p[v[j]].first;
			d=min(d,(long long)dx*dx+(long long)dy*dy);
		}
		v.push_back(i);
	}
	return d;
}
int main()
{
	int n;
	fin>>n;
	for(int i=1;i<=n;i++)
		fin>>p[i].first>>p[i].second;
	sort(p+1,p+n+1);
	fout<<solve(1,n)<<endl;
	return 0;
}