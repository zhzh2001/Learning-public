#include <fstream>
#include <cmath>
using namespace std;
ifstream fin("fact.in");
ofstream fout("fact.out");
const long double huge = 1e4000L;
const int len = 4000;
int main()
{
	int n, k;
	fin >> n >> k;
	long double ans0 = 1.0L, ans1 = 1.0L;
	int cnt = 0;
	fout.precision(k);
	for (int i = 1; i < n; i += 2)
	{
		ans0 *= i;
		if (ans0 > huge)
		{
			cnt++;
			ans0 /= huge;
		}
		ans1 *= i + 1;
		if (ans1 > huge)
		{
			cnt++;
			ans1 /= huge;
		}
	}
	if (n & 1)
		ans0 *= n;
	int t0 = floor(log10(ans0)), t1 = floor(log10(ans1));
	long double dt0 = ans0 / pow(10.0L, t0), dt1 = ans1 / pow(10.0L, t1);
	dt0 *= dt1;
	if (dt0 >= 10.0L)
	{
		t0++;
		dt0 /= 10.0L;
	}
	fout << dt0 << "e+" << (long long)cnt * len + t0 + t1 << endl;
	return 0;
}