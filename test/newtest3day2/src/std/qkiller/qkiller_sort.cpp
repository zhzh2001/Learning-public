#include <bits/stdc++.h>
using namespace std;
ifstream fin("qkiller.in");
ofstream fout("qkiller.out");
const int n = 1e5;
int a[n];
int main()
{
	int type;
	fin >> type;
	if (type == 4)
		fin.ignore().ignore(100, '\n');
	for (int i = 0; i < n; i++)
		fin >> a[i];
	sort(a, a + n);
	for (int i = 0; i < n; i++)
		fout << a[i] << ' ';
	fout << endl;
	return 0;
}