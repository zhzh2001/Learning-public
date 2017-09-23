#include <fstream>
#include <random>
#include <windows.h>
using namespace std;
ofstream fout("paint.in");
const int n = 5000000, m = 5000000;
int main()
{
	minstd_rand gen(GetTickCount());
	fout << n << ' ' << m << endl;
	uniform_int_distribution<> dn(1, n);
	int l = dn(gen), r = l;
	for (int i = 1; i <= n; i++)
	{
		fout << l << ' ' << r << endl;
		uniform_int_distribution<> ds(0, 1);
		if (l == 1)
			r++;
		else if (r == n)
			l--;
		else if (ds(gen))
			r++;
		else
			l--;
	}
	return 0;
}