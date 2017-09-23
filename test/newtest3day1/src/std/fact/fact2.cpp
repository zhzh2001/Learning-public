#include <fstream>
#include <cmath>
using namespace std;
ifstream fin("fact.in");
ofstream fout("fact.out");
const int llim = 16000;
int main()
{
	int n, k;
	fin >> n >> k;
	long double lim = pow(2.0L, llim), ans = 1.0L;
	int cnt = 0;
	for (int i = 1; i <= n; i++)
	{
		ans *= i;
		if (ans > lim)
		{
			ans /= lim;
			cnt++;
		}
	}
	long double lg = 1ll * cnt * llim / log2(10.0L);
	long long len = floor(lg);
	ans *= pow(10.0L, lg - len);
	int t = floor(log10(ans));
	fout.precision(k);
	fout << ans / pow(10.0L, t) << "e+" << len + t << endl;
	return 0;
}