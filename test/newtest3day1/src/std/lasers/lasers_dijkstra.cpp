#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
ifstream fin("lasers.in");
ofstream fout("lasers.out");
const int N = 300005, INF = 0x3f3f3f3f;
int x[N], y[N];
struct node
{
	bool state;
	int v, w;
	node(bool state, int v, int w) : state(state), v(v), w(w) {}
	bool operator>(const node &rhs) const
	{
		return w > rhs.w;
	}
};
int main()
{
	int n, sx, sy, tx, ty;
	fin >> n >> sx >> sy >> tx >> ty;
	unordered_map<int, vector<int>> mat[2];
	for (int i = 1; i <= n; i++)
	{
		fin >> x[i] >> y[i];
		mat[0][x[i]].push_back(y[i]);
		mat[1][y[i]].push_back(x[i]);
	}
	unordered_map<int, int> d[2];
	d[0][sx] = d[1][sy] = 0;
	priority_queue<node, vector<node>, greater<node>> Q;
	Q.push(node(0, sx, 0));
	Q.push(node(1, sy, 0));
	unordered_set<int> vis[2];
	while (!Q.empty())
	{
		node k = Q.top();
		Q.pop();
		if (vis[k.state].find(k.v) != vis[k.state].end())
			continue;
		vis[k.state].insert(k.v);
		for (auto v : mat[k.state][k.v])
			if (vis[k.state ^ 1].find(v) == vis[k.state ^ 1].end())
			{
				if (d[k.state ^ 1].find(v) == d[k.state ^ 1].end())
					d[k.state ^ 1][v] = INF;
				if (d[k.state][k.v] + 1 < d[k.state ^ 1][v])
					Q.push(node(k.state ^ 1, v, d[k.state ^ 1][v] = d[k.state][k.v] + 1));
			}
	}
	int ans = INF;
	if (d[0].find(tx) != d[0].end())
		ans = min(ans, d[0][tx]);
	if (d[1].find(ty) != d[1].end())
		ans = min(ans, d[1][ty]);
	fout << ans << endl;
	return 0;
}