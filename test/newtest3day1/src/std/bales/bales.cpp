#include <fstream>
#include <algorithm>
using namespace std;
ifstream fin("bales.in");
ofstream fout("bales.out");
const int N = 1000005, M = 300005;
struct quest
{
	int l, r, min, id;
	bool operator<(const quest &rhs) const
	{
		return min > rhs.min;
	}
} a[M], b[M];
int n, m, f[N];
int getf(int x)
{
	return f[x] == x ? x : f[x] = getf(f[x]);
}
bool check(int mid)
{
	int cc = 0;
	for (int i = 1; i <= m; i++)
		if (a[i].id <= mid)
			b[++cc] = a[i];
	for (int i = 0; i <= n; i++)
		f[i] = i;
	for (int i = 1, j; i <= cc; i = j)
	{
		int minx = b[i].l, maxx = b[i].l, miny = b[i].r, maxy = b[i].r;
		for (j = i + 1; j <= cc && b[j].min == b[i].min; j++)
		{
			minx = min(minx, b[j].l);
			maxx = max(maxx, b[j].l);
			miny = min(miny, b[j].r);
			maxy = max(maxy, b[j].r);
		}
		if (maxx > getf(miny))
			return false;
		while (minx <= maxy)
			if (getf(maxy) == maxy)
				f[maxy--] = getf(minx - 1);
			else
				maxy = getf(maxy);
	}
	return true;
}
int main()
{
	fin >> n >> m;
	for (int i = 1; i <= m; i++)
	{
		fin >> a[i].l >> a[i].r >> a[i].min;
		a[i].id = i;
	}
	sort(a + 1, a + m + 1);
	int l = 1, r = m, ans = 1;
	while (l <= r)
	{
		int mid = (l + r) / 2;
		if (check(mid))
		{
			l = mid + 1;
			ans = mid;
		}
		else
			r = mid - 1;
	}
	fout << (ans + 1) % (m + 1) << endl;
	return 0;
}