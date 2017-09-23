#include <bits/stdc++.h>
#include <gmpxx.h>
using namespace std;
ifstream fin("fact.in");
ofstream fout("fact.ans");
int main()
{
	int n, k;
	fin >> n >> k;
	mpf_class ans(1, 300);
	for (int i = 1; i <= n; i++)
		ans *= i;
	fout.precision(k);
	fout << ans << endl;
	return 0;
}