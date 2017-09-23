#include <fstream>
#include <algorithm>
using namespace std;
ifstream fin("bales.in");
ofstream fout("bales.out");
const int N = 1000005, M = 300005;
struct quest
{
	int l, r, min;
	bool operator<(const quest &rhs) const
	{
		return min > rhs.min;
	}
} a[M], b[M];
int n, f[N];
int getf(int x)
{
	return f[x] == x ? x : f[x] = getf(f[x]);
}
bool check(int m)
{
	copy(a + 1, a + m + 1, b + 1);
	sort(b + 1, b + m + 1);
	for (int i = 0; i <= n; i++)
		f[i] = i;
	for (int i = 1, j; i <= m; i = j)
	{
		int minx = b[i].l, maxx = b[i].l, miny = b[i].r, maxy = b[i].r;
		for (j = i + 1; j <= m && b[j].min == b[i].min; j++)
		{
			minx = min(minx, b[j].l);
			maxx = max(maxx, b[j].l);
			miny = min(miny, b[j].r);
			maxy = max(maxy, b[j].r);
		}
		if (maxx > getf(miny))
			return false;
		while (getf(minx - 1) != getf(maxy))
			f[getf(maxy)] = getf(maxy) - 1;
	}
	return true;
}
int main()
{
	int m;
	fin >> n >> m;
	for (int i = 1; i <= m; i++)
		fin >> a[i].l >> a[i].r >> a[i].min;
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