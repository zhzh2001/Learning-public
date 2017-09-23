#include <fstream>
#include <random>
#include <ctime>
#include <algorithm>
#include <iostream>
using namespace std;
ofstream fout("bales.in");
const int n = 1e6, m = 3e5, t = 5, tt = 273333;
struct quest
{
	int l, r, min;
} a[m + 5];
int v[t + 5], f[n + 5];
int getf(int x)
{
	return f[x] == x ? x : f[x] = getf(f[x]);
}
int main()
{
	minstd_rand gen(time(NULL));
	fout << n << ' ' << m << endl;
	for (int i = 1; i <= t; i++)
	{
		uniform_int_distribution<> d(1, 1e9);
		v[i] = d(gen);
	}
	sort(v + 1, v + t + 1);
	for (int i = 0; i <= n; i++)
		f[i] = i;
	int M = 0;
	for (int i = t; i; i--)
	{
		int maxx, miny;
		do
		{
			uniform_int_distribution<> dx(1, n);
			maxx = dx(gen);
			uniform_int_distribution<> dl(1, min(n - maxx + 1, 500));
			miny = maxx + dl(gen) - 1;
		} while (maxx > getf(miny));
		uniform_int_distribution<> dl(1, min(400000, min(maxx, n - miny + 1))), dc(1, tt);
		int minx = maxx - dl(gen) + 1, maxy = miny + dl(gen) - 1, c = i == t ? tt : 5000;
		for (int j = 1; j <= c; j++)
		{
			uniform_int_distribution<> dx(minx, maxx), dy(miny, maxy);
			a[++M].l = dx(gen);
			a[M].r = dy(gen);
			a[M].min = v[i];
		}
		while (minx <= maxy)
			if (getf(maxy) == maxy)
				f[maxy--] = getf(minx - 1);
			else
				maxy = getf(maxy);
		cout << i << endl;
	}
	shuffle(a + 1, a + M + 1, gen);
	for (int i = 1; i <= M; i++)
		fout << a[i].l << ' ' << a[i].r << ' ' << a[i].min << endl;
	for (int i = M + 1; i <= m; i++)
	{
		uniform_int_distribution<> dn(1, n), dt(1, t);
		int l = dn(gen), r = dn(gen);
		if (l > r)
			swap(l, r);
		fout << l << ' ' << r << ' ' << v[dt(gen)] << endl;
	}
	return 0;
}