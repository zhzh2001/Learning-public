#include <fstream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
ifstream fin("lasers.in");
ofstream fout("lasers.out");
const int N = 300005, INF = 0x3f3f3f3f;
int x[N], y[N], d[N * 2];
pair<int, int> e[N];
vector<int> mat[N * 2];
int main()
{
	int n, sx, sy, tx, ty;
	fin >> n >> sx >> sy >> tx >> ty;
	for (int i = 1; i <= n; i++)
	{
		fin >> e[i].first >> e[i].second;
		x[i] = e[i].first;
		y[i] = e[i].second;
	}
	x[n + 1] = sx;
	x[n + 2] = tx;
	y[n + 1] = sy;
	y[n + 2] = ty;
	sort(x + 1, x + n + 3);
	sort(y + 1, y + n + 3);
	sx = lower_bound(x + 1, x + n + 3, sx) - x;
	sy = lower_bound(y + 1, y + n + 3, sy) - y + n + 2;
	tx = lower_bound(x + 1, x + n + 3, tx) - x;
	ty = lower_bound(y + 1, y + n + 3, ty) - y + n + 2;
	for (int i = 1; i <= n; i++)
	{
		e[i].first = lower_bound(x + 1, x + n + 3, e[i].first) - x;
		e[i].second = lower_bound(y + 1, y + n + 3, e[i].second) - y + n + 2;
		mat[e[i].first].push_back(e[i].second);
		mat[e[i].second].push_back(e[i].first);
	}
	fill(d + 1, d + n + 2 + n + 2 + 1, INF);
	d[sx] = d[sy] = 0;
	queue<int> Q;
	Q.push(sx);
	Q.push(sy);
	while (!Q.empty())
	{
		int k = Q.front();
		Q.pop();
		for (auto v : mat[k])
			if (d[v] == INF)
			{
				d[v] = d[k] + 1;
				Q.push(v);
			}
	}
	fout << min(d[tx], d[ty]) << endl;
	return 0;
}