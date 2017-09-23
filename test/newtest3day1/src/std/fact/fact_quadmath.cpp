#include <bits/stdc++.h>
#include <quadmath.h>
using namespace std;
ifstream fin("fact.in");
ofstream fout("fact.out");
const __float128 huge = 1e4000q;
int main()
{
	int n, k;
	fin >> n >> k;
	__float128 ans = 1.0q;
	for (int i = 1; i <= n; i++)
	{
		ans *= i;
		if (ans > huge)
			ans /= huge;
	}
	char buf[100];
	quadmath_snprintf(buf, sizeof(buf), "%.*Qe", k - 1, ans);
	fout << buf << endl;
	return 0;
}