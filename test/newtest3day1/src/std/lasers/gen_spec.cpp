#include <fstream>
#include <random>
#include <ctime>
#include <algorithm>
using namespace std;
ofstream fout("lasers.in");
const int n = 300000, n2 = 14950, n3 = 100;
int x[n], y[n];
int main()
{
	minstd_rand gen(time(NULL));
	for (int i = 1; i <= n2; i++)
		x[i] = i;
	shuffle(x + 1, x + n2 + 1, gen);
	for (int i = 1; i <= n2; i++)
		y[i] = i;
	shuffle(y + 1, y + n2 + 1, gen);
	int sx = x[1], sy = y[1], tx = x[n2], ty = y[n2];
	fout << n << ' ' << sx << ' ' << sy << ' ' << tx << ' ' << ty << endl;
	for (int i = 1; i <= n2 - 2; i++)
		fout << x[i] << ' ' << y[i + 1] << endl
			 << x[i + 1] << ' ' << y[i + 1] << endl;
	fout << x[n2 - 1] << ' ' << y[n2] << endl;
	for (int i = 1; i <= n3; i++)
	{
		uniform_int_distribution<> dn(1, n2);
		fout << x[dn(gen)] << ' ' << y[dn(gen)] << endl;
	}
	return 0;
}