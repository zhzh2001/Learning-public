#include <bits/stdc++.h>
using namespace std;
ofstream fout("qkiller.in");
const int n = 1e5;
int main()
{
	minstd_rand gen(time(NULL));
	for (int i = 1; i <= n; i++)
	{
		uniform_int_distribution<> d(numeric_limits<int>::min(), numeric_limits<int>::max());
		fout << d(gen) << ' ';
	}
	fout << endl;
	return 0;
}