#include <fstream>
#include <ctime>
#include <algorithm>
using namespace std;
ifstream fin("qkiller.in");
ofstream fout("qkiller.out");
const int n = 100000, A = 48271, MOD = 2147483647;
int a[n + 5], id[n + 5], ans[n + 5];
int main()
{
	int type;
	fin >> type;
	long long seed;
	if (type == 4)
	{
		tm rec;
		char c;
		fin >> rec.tm_year >> c >> rec.tm_mon >> c >> rec.tm_mday >> rec.tm_hour >> c >> rec.tm_min >> c >> rec.tm_sec;
		rec.tm_year -= 1900;
		rec.tm_mon--;
		seed = mktime(&rec);
	}
	for (int i = 1; i <= n; i++)
	{
		fin >> a[i];
		id[i] = i;
	}
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++)
	{
		int pos;
		switch (type)
		{
		case 1:
			pos = (i + n) / 2;
			break;
		case 2:
			pos = i;
			break;
		case 3:
			pos = n;
			break;
		case 4:
			seed = seed * A % MOD;
			pos = seed % (n - i + 1) + i;
			break;
		}
		ans[id[pos]] = a[i];
		swap(id[i], id[pos]);
	}
	for (int i = 1; i <= n; i++)
		fout << ans[i] << endl;
	return 0;
}