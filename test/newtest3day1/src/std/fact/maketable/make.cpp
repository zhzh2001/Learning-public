#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>
using namespace std;
const long double huge = 1e4000L;
const int len = 4000, K = 5e8;
int main(int argc, char *argv[])
{
	if (argc != 4)
		exit(1);
	long long l, r;
	sscanf(argv[1], "%lld", &l);
	sscanf(argv[2], "%lld", &r);
	FILE *fout = fopen(argv[3], "wb");
	long double ans1 = 1.0L, ans2 = 1.0L;
	int cnt1 = 0, cnt2 = 0;
	for (long long i = l; i <= r; i += K)
	{
		for (long long j = i; j < i + K; j += 2)
		{
			ans1 *= j;
			if (ans1 > huge)
			{
				cnt1++;
				ans1 /= huge;
			}
			ans2 *= j + 1;
			if (ans2 > huge)
			{
				cnt2++;
				ans2 /= huge;
			}
		}
		fwrite(&ans1, sizeof(ans1), 1, fout);
		fwrite(&cnt1, sizeof(cnt1), 1, fout);
		fwrite(&ans2, sizeof(ans2), 1, fout);
		fwrite(&cnt2, sizeof(cnt2), 1, fout);
	}
	fclose(fout);
	fprintf(stderr, "%lu\n", clock());
	system("pause");
	return 0;
}