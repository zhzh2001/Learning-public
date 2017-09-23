#include <fstream>
#include <algorithm>
#include <utility>
using namespace std;
ifstream fin("corral.in");
ofstream fout("corral.out");
const int N = 3005;
pair<long long, long long> p[N];
long long x[N], y[N];
int s[N][N];
int main()
{
	int c, n;
	fin >> c >> n;
	for (int i = 1; i <= n; i++)
	{
		fin >> p[i].first >> p[i].second;
		x[i] = p[i].first;
		y[i] = p[i].second;
	}
	sort(x + 1, x + n + 1);
	sort(y + 1, y + n + 1);
	for (int i = 1; i <= n; i++)
	{
		p[i].first = lower_bound(x + 1, x + n + 1, p[i].first) - x;
		p[i].second = lower_bound(y + 1, y + n + 1, p[i].second) - y;
		s[p[i].first][p[i].second]++;
	}
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			s[i][j] += s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
	long long l = 1, r = 1e18 + 1;
	while (l < r)
	{
		long long mid = (l + r) / 2;
		bool flag = false;
		for (int x1 = 1, x2 = 1; !flag && x2 <= n; x1++)
		{
			for (; x2 <= n && x[x2] - x[x1] + 1 <= mid; x2++)
				;
			for (int y1 = 1, y2 = 1; !flag && y2 <= n; y1++)
			{
				for (; y2 <= n && y[y2] - y[y1] + 1 <= mid; y2++)
					;
				flag = s[x2 - 1][y2 - 1] - s[x1 - 1][y2 - 1] - s[x2 - 1][y1 - 1] + s[x1 - 1][y1 - 1] >= c;
			}
		}
		if (flag)
			r = mid;
		else
			l = mid + 1;
	}
	fout << r << endl;
	return 0;
}