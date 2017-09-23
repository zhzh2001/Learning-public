#include <fstream>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <limits>

using namespace std;

#define MAXN 3000

static int LL[MAXN + 1][MAXN + 1];

struct point
{
	long long x, y;
};

struct compare
{
	bool operator()(const point &a, const point &b)
	{
		if (a.x != b.x)
			return a.x < b.x;
		return a.y < b.y;
	}
};

int main()
{
	ifstream in("corral.in");
	int C, N;
	vector<point> points;
	vector<long long> xs;
	vector<long long> ys;
	int X, Y;

	in >> C >> N;
	for (int i = 0; i < N; i++)
	{
		long long x, y;
		in >> x >> y;
		points.push_back((point){x, y});
		xs.push_back(x);
		ys.push_back(y);
	}
	sort(points.begin(), points.end(), compare());
	sort(xs.begin(), xs.end());
	xs.erase(unique(xs.begin(), xs.end()), xs.end());
	sort(ys.begin(), ys.end());
	ys.erase(unique(ys.begin(), ys.end()), ys.end());
	X = xs.size();
	Y = ys.size();
	xs.push_back(numeric_limits<long long>::max());
	ys.push_back(numeric_limits<long long>::max());

	memset(LL, 0, sizeof(LL));
	int p = 0;
	for (int x = 1; x <= X; x++)
		for (int y = 1; y <= Y; y++)
		{
			LL[x][y] = LL[x - 1][y] + LL[x][y - 1] - LL[x - 1][y - 1];
			while (p < N && points[p].x == xs[x - 1] && points[p].y == ys[y - 1])
			{
				LL[x][y]++;
				p++;
			}
		}

	long long ans = numeric_limits<long long>::max();

	for (int x0 = 0; x0 < X; x0++)
	{
		long long S = 0;
		int x1 = x0 + 1;
		int y0 = 0;
		int y1 = 1;
		int I = LL[x1][y1] - LL[x0][y1] - LL[x1][y0] + LL[x0][y0];

		while (true)
		{
			while (I < C && (x1 < X || y1 < Y))
			{
				S = min(xs[x1] - xs[x0], ys[y1] - ys[y0]);
				while (xs[x1] - xs[x0] <= S)
					x1++;
				while (ys[y1] - ys[y0] <= S)
					y1++;
				assert(0 <= x0 && x0 <= x1 && x1 <= X);
				assert(0 <= y0 && y0 <= y1 && y1 <= Y);
				I = LL[x1][y1] - LL[x0][y1] - LL[x1][y0] + LL[x0][y0];
			}
			if (I < C)
				break;
			ans = min(ans, S + 1);

			assert(S >= ys[y1 - 1] - ys[y0]);
			y0++;
			if (y0 == Y)
				break;
			if (y1 <= y0)
			{
				y1 = y0 + 1;
				S = 0;
			}
			else
				S -= ys[y0] - ys[y0 - 1];
			while (xs[x1 - 1] - xs[x0] > S)
				x1--;
			assert(0 <= x0 && x0 <= x1 && x1 <= X);
			assert(0 <= y0 && y0 <= y1 && y1 <= Y);
			I = LL[x1][y1] - LL[x0][y1] - LL[x1][y0] + LL[x0][y0];
		}
	}

	ofstream out("corral.out");
	out << ans << "\n";

	return 0;
}