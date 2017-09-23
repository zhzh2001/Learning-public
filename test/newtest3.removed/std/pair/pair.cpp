#include<fstream>
#include<algorithm>
#include<set>
using namespace std;
ifstream fin("pair.in");
ofstream fout("pair.out");
const int N=200005;
const long long INF=0x3f3f3f3f3f3f3f3fll;
pair<int,int> p[N];
int main()
{
	int n;
	fin>>n;
	for(int i=1;i<=n;i++)
		fin>>p[i].first>>p[i].second;
	sort(p+1,p+n+1);
	long long ans=INF;
	multiset<pair<int,int>> S;
	int j=1;
	for(int i=1;i<=n;i++)
	{
		for(;j<i&&(long long)(p[i].first-p[j].first)*(p[i].first-p[j].first)>=ans;j++)
			S.erase(S.find(make_pair(p[j].second,p[j].first)));
		auto ret=S.insert(make_pair(p[i].second,p[i].first));
		for(auto it=ret;it--!=S.begin();)
		{
			int dy=p[i].second-it->first;
			if((long long)dy*dy>=ans)
				break;
			int dx=p[i].first-it->second;
			ans=min(ans,(long long)dx*dx+(long long)dy*dy);
		}
		for(auto it=ret;++it!=S.end();)
		{
			int dy=it->first-p[i].second;
			if((long long)dy*dy>=ans)
				break;
			int dx=p[i].first-it->second;
			ans=min(ans,(long long)dx*dx+(long long)dy*dy);
		}
	}
	fout<<ans<<endl;
	return 0;
}