#include <fstream>
#include <algorithm>
using namespace std;
ifstream fin("landscape.in");
ofstream fout("landscape.out");
const int N = 5005;
int a[N], b[N];
long long f[N][N];
int main()
{
	int n, x, y, z;
	fin >> n >> x >> y >> z;
	int suma = 0, sumb = 0;
	for (int i = 1; i <= n; i++)
	{
		int A, B;
		fin >> A >> B;
		while (A--)
			a[++suma] = i;
		while (B--)
			b[++sumb] = i;
	}
	for (int i = 1; i <= suma; i++)
		f[i][0] = 1ll * y * i;
	for (int i = 1; i <= sumb; i++)
		f[0][i] = 1ll * x * i;
	for (int i = 1; i <= suma; i++)
		for (int j = 1; j <= sumb; j++)
			f[i][j] = min(f[i - 1][j - 1] + z * abs(a[i] - b[j]), min(f[i][j - 1] + x, f[i - 1][j] + y));
	fout << f[suma][sumb] << endl;
	return 0;
}