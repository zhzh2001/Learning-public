#include <cstdio>
#include <set>
#include <ctime>
#include <cassert>
#include <thread>
#include <chrono>
using namespace std;
const int n = 100000, A = 48271, MOD = 2147483647;
int a[n + 5];
FILE *fres;
void Return(double score, const char *msg = nullptr)
{
	fprintf(fres, "%.3lf\n", score);
	if (msg)
		fprintf(fres, "%s\n", msg);
	exit(0);
}
bool flag, done;
void sort1(int l, int r)
{
	int i = l, j = r, x = a[(l + r) / 2];
	do
	{
		for (; a[i] < x; i++)
			;
		for (; x < a[j]; j--)
			;
		if (i <= j)
			swap(a[i++], a[j--]);
	} while (i <= j);
	if (flag)
	{
		done = false;
		return;
	}
	if (l < j)
		sort1(l, j);
	if (flag)
	{
		done = false;
		return;
	}
	if (i < r)
		sort1(i, r);
}
void sort2(int l, int r)
{
	int i = l, j = r, x = a[l];
	do
	{
		for (; a[i] < x; i++)
			;
		for (; x < a[j]; j--)
			;
		if (i <= j)
			swap(a[i++], a[j--]);
	} while (i <= j);
	if (flag)
	{
		done = false;
		return;
	}
	if (l < j)
		sort2(l, j);
	if (flag)
	{
		done = false;
		return;
	}
	if (i < r)
		sort2(i, r);
}
void sort3(int l, int r)
{
	int i = l, j = r, x = a[r];
	do
	{
		for (; a[i] < x; i++)
			;
		for (; x < a[j]; j--)
			;
		if (i <= j)
			swap(a[i++], a[j--]);
	} while (i <= j);
	if (flag)
	{
		done = false;
		return;
	}
	if (l < j)
		sort3(l, j);
	if (flag)
	{
		done = false;
		return;
	}
	if (i < r)
		sort3(i, r);
}
long long seed;
void sort4(int l, int r)
{
	seed = seed * A % MOD;
	int i = l, j = r, x = a[seed % (r - l + 1) + l];
	do
	{
		for (; a[i] < x; i++)
			;
		for (; x < a[j]; j--)
			;
		if (i <= j)
			swap(a[i++], a[j--]);
	} while (i <= j);
	if (flag)
	{
		done = false;
		return;
	}
	if (l < j)
		sort4(l, j);
	if (flag)
	{
		done = false;
		return;
	}
	if (i < r)
		sort4(i, r);
}
int main(int argc, char *argv[])
{
	FILE *fin = fopen("qkiller.in", "r"), *fout = fopen("qkiller.out", "r");
	fres = argc > 4 ? fopen(argv[4], "w") : stdout;
	int k;
	fscanf(fin, "%d", &k);
	if (k == 4)
	{
		tm rec;
		//memset(&rec,0,sizeof(rec));
		fscanf(fin, "%d/%d/%d %d:%d:%d", &rec.tm_year, &rec.tm_mon, &rec.tm_mday, &rec.tm_hour, &rec.tm_min, &rec.tm_sec);
		rec.tm_year -= 1900;
		rec.tm_mon--;
		seed = mktime(&rec);
		assert(seed >= 0);
	}
	multiset<int> S;
	for (int i = 1; i <= n; i++)
	{
		int x;
		fscanf(fin, "%d", &x);
		S.insert(x);
	}
	for (int i = 1; i <= n; i++)
	{
		fscanf(fout, "%d", a + i);
		if (S.find(a[i]) == S.end())
			Return(.0, "无效的方案");
		S.erase(S.find(a[i]));
	}
	flag = false;
	thread *th = nullptr;
	switch (k)
	{
	case 1:
		th = new thread(sort1, 1, n);
		break;
	case 2:
		th = new thread(sort2, 1, n);
		break;
	case 3:
		th = new thread(sort3, 1, n);
		break;
	case 4:
		th = new thread(sort4, 1, n);
		break;
	default:
		throw;
	}
	this_thread::sleep_for(chrono::seconds(1));
	flag = done = true;
	th->join();
	delete th;
	if (done)
		Return(.0, "方案失败");
	else
		Return(1.0, "正确");
	return 0;
}