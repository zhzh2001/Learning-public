#include <fstream>
#include <queue>
#include <vector>
using namespace std;
ifstream fin("landscape.in");
ofstream fout("landscape.out");
const int N = 100005;
int a[N], b[N];
int main()
{
	int n, x, y, z;
	fin >> n >> x >> y >> z;
	for (int i = 1; i <= n; i++)
		fin >> a[i] >> b[i];
	priority_queue<int, vector<int>, greater<int>> q1, q2;
	long long ans = 0;
	for (int i = 1; i <= n; i++)
	{
		for (; a[i] > b[i]; a[i]--)
		{
			int now = y;
			if (!q1.empty() && q1.top() + i * z < now)
			{
				now = q1.top() + i * z;
				q1.pop();
			}
			ans += now;
			q2.push(-now - i * z);
		}
		for (; a[i] < b[i]; a[i]++)
		{
			int now = x;
			if (!q2.empty() && q2.top() + i * z < now)
			{
				now = q2.top() + i * z;
				q2.pop();
			}
			ans += now;
			q1.push(-now - i * z);
		}
	}
	fout << ans << endl;
	return 0;
}