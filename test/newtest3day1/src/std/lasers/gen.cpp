#include <fstream>
#include <random>
#include <ctime>
#include <cassert>
#include <set>
using namespace std;
ofstream fout("lasers.in");
const int n = 300000, xn = 250000, yn = 220000, c = 1e9;
int x[n], y[n];
int main()
{
	minstd_rand gen(time(NULL));
	uniform_int_distribution<> dc(0, c);
	for (int i = 1; i <= xn; i++)
		x[i] = dc(gen);
	for (int i = 1; i <= yn; i++)
		y[i] = dc(gen);
	int sx = x[1], sy = y[1], tx = x[xn], ty = y[yn];
	assert(sx != tx || sy != ty);
	fout << n << ' ' << sx << ' ' << sy << ' ' << tx << ' ' << ty << endl;
	set<pair<int, int>> S;
	S.insert(make_pair(sx, sy));
	S.insert(make_pair(tx, ty));
	uniform_int_distribution<> dxn(1, xn), dyn(1, yn);
	for (int i = 1; i <= n; i++)
	{
		int nx = x[dxn(gen)], ny = y[dyn(gen)];
		if (S.find(make_pair(nx, ny)) != S.end())
		{
			i--;
			continue;
		}
		fout << nx << ' ' << ny << endl;
		S.insert(make_pair(nx, ny));
	}
	return 0;
}