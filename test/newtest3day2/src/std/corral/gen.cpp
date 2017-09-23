#include <fstream>
#include <random>
#include <windows.h>
using namespace std;
ofstream fout("corral.in");
const int n = 50000, c = 23333;
int main()
{
	minstd_rand gen(GetTickCount());
	fout << c << ' ' << n << endl;
	for (int i = 1; i <= n; i++)
	{
		uniform_int_distribution<> d(1, 1e6);
		fout << d(gen) << ' ' << d(gen) << endl;
	}
	return 0;
}