#include <fstream>
#include <random>
#include <ctime>
using namespace std;
ofstream fout("landscape.in");
const int n = 100000, x = 15456421, y = 54644131, z = 233, c = 50;
int main()
{
	minstd_rand gen(time(NULL));
	fout << n << ' ' << x << ' ' << y << ' ' << z << endl;
	for (int i = 1; i <= n; i++)
	{
		uniform_int_distribution<> d(0, c);
		fout << d(gen) << ' ' << d(gen) << endl;
	}
	return 0;
}