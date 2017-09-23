#include <fstream>
#include <random>
#include <ctime>
using namespace std;
ofstream fout("paint.in");
const int n = 1e7, m = 1e7;
int main()
{
	minstd_rand gen(time(NULL));
	fout << n << ' ' << m << endl;
	for (int i = 1; i <= m; i++)
	{
		uniform_int_distribution<> dn(1, n);
		int l = dn(gen), r = dn(gen);
		if (l > r)
			swap(l, r);
		fout << l << ' ' << r << endl;
	}
	return 0;
}