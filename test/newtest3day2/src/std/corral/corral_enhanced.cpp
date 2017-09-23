#include <fstream>
#include <algorithm>
using namespace std;
ifstream fin("corral.in");
ofstream fout("corral.out");
const int N = 50005;
struct clover
{
	int x, y, cnt;
} a[N];
struct event
{
	int x, yl, yr, cnt;
	bool operator<(const event &rhs) const
	{
		return x < rhs.x;
	}
} e[N * 2];
int y[N * 2];
struct node
{
	int max, lazy;
} tree[1 << 18];
void build(int id, int l, int r)
{
	tree[id].max = tree[id].lazy = 0;
	if (l < r)
	{
		int mid = (l + r) / 2;
		build(id * 2, l, mid);
		build(id * 2 + 1, mid + 1, r);
	}
}
inline void pushdown(int id, int l, int r)
{
	if (tree[id].lazy && l < r)
	{
		tree[id * 2].max += tree[id].lazy;
		tree[id * 2].lazy += tree[id].lazy;
		tree[id * 2 + 1].max += tree[id].lazy;
		tree[id * 2 + 1].lazy += tree[id].lazy;
		tree[id].lazy = 0;
	}
}
void update(int id, int l, int r, int L, int R, int val)
{
	if (L <= l && R >= r)
	{
		tree[id].lazy += val;
		tree[id].max += val;
	}
	else
	{
		pushdown(id, l, r);
		int mid = (l + r) / 2;
		if (L <= mid)
			update(id * 2, l, mid, L, R, val);
		if (R > mid)
			update(id * 2 + 1, mid + 1, r, L, R, val);
		tree[id].max = max(tree[id * 2].max, tree[id * 2 + 1].max);
	}
}
int main()
{
	int c, n;
	fin >> c >> n;
	for (int i = 1; i <= n; i++)
	{
		fin >> a[i].x >> a[i].y;
		a[i].cnt = 1;
	}
	int l = 1, r = 1e6;
	while (l < r)
	{
		int mid = (l + r) / 2, en = 0, yn = 0;
		for (int i = 1; i <= n; i++)
		{
			e[++en].x = a[i].x - mid + 1;
			y[++yn] = e[en].yl = a[i].y - mid + 1;
			y[++yn] = e[en].yr = a[i].y;
			e[en].cnt = a[i].cnt;
			e[++en].x = a[i].x + 1;
			e[en].yl = a[i].y - mid + 1;
			e[en].yr = a[i].y;
			e[en].cnt = -a[i].cnt;
		}
		sort(e + 1, e + en + 1);
		sort(y + 1, y + yn + 1);
		build(1, 1, yn);
		int now = 0;
		for (int i = 1; i <= en; i++)
		{
			if (e[i].x != e[i - 1].x)
				now = max(now, tree[1].max);
			update(1, 1, yn, lower_bound(y + 1, y + yn + 1, e[i].yl) - y, lower_bound(y + 1, y + yn + 1, e[i].yr) - y, e[i].cnt);
		}
		if (now < c)
			l = mid + 1;
		else
			r = mid;
	}
	fout << r << endl;
	return 0;
}