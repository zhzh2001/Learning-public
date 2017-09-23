#include <fstream>
#include <algorithm>
#include <utility>
#include <limits>
using namespace std;
ifstream fin("corral.in");
ofstream fout("corral.out");
const int N = 3005;
const long long INF = numeric_limits<long long>::max();
pair<long long, long long> p[N];
long long x[N], y[N];
short s[N][N];
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
	int xn = unique(x + 1, x + n + 1) - x - 1, yn = unique(y + 1, y + n + 1) - y - 1;
	for (int i = 1; i <= n; i++)
	{
		p[i].first = lower_bound(x + 1, x + xn + 1, p[i].first) - x;
		p[i].second = lower_bound(y + 1, y + yn + 1, p[i].second) - y;
		s[p[i].first][p[i].second]++;
	}
	for (int i = 1; i <= xn; i++)
		for (int j = 1; j <= yn; j++)
			s[i][j] += s[i - 1][j] + s[i][j - 1] - s[i - 1][j - 1];
	long long ans = INF;
	x[xn + 1] = y[yn + 1] = INF;
	for (int x1 = 1; x1 <= xn; x1++)
	{
		long long now = 0;
		int x2 = x1 + 1, y1 = 1, y2 = 2, cnt = s[x2 - 1][y2 - 1] - s[x1 - 1][y2 - 1] - s[x2 - 1][y1 - 1] + s[x1 - 1][y1 - 1];
		for (;;)
		{
			while (cnt < c && (x2 <= xn || y2 <= yn))
			{
				now = min(x[x2] - x[x1], y[y2] - y[y1]);
				for (; x[x2] - x[x1] <= now; x2++)
					;
				for (; y[y2] - y[y1] <= now; y2++)
					;
				cnt = s[x2 - 1][y2 - 1] - s[x1 - 1][y2 - 1] - s[x2 - 1][y1 - 1] + s[x1 - 1][y1 - 1];
			}
			if (cnt < c)
				break;
			ans = min(ans, now + 1);
			if (++y1 > yn)
				break;
			if (y2 == y1)
			{
				y2 = y1 + 1;
				now = 0;
			}
			else
				now -= y[y1] - y[y1 - 1];
			for (; x[x2 - 1] - x[x1] > now; x2--)
				;
			cnt = s[x2 - 1][y2 - 1] - s[x1 - 1][y2 - 1] - s[x2 - 1][y1 - 1] + s[x1 - 1][y1 - 1];
		}
	}
	fout << ans << endl;
	return 0;
}