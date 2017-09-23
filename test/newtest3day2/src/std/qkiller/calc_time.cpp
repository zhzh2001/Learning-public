#include <bits/stdc++.h>
using namespace std;
const int months = 12;
int days[months] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int main()
{
	tm rec;
	memset(&rec, 0, sizeof(rec));
	scanf("%d/%d/%d %d:%d:%d", &rec.tm_year, &rec.tm_mon, &rec.tm_mday, &rec.tm_hour, &rec.tm_min, &rec.tm_sec);
	int secs = 0;
	for (int i = 1970; i < rec.tm_year; i++)
	{
		secs += 365 * 24 * 3600;
		if (i % 4 == 0)
			secs += 24 * 3600;
		//leap year
	}
	rec.tm_mon--;
	for (int i = 0; i < rec.tm_mon; i++)
	{
		secs += days[i] * 24 * 3600;
		if (rec.tm_year % 4 == 0 && i == 1)
			secs += 24 * 3600;
		//leap year
	}
	secs += (rec.tm_mday - 1) * 24 * 3600 + rec.tm_hour * 3600 + rec.tm_min * 60 + rec.tm_sec;
	secs -= 8 * 3600;
	cout << secs << endl;
	//time zone
	rec.tm_year -= 1900;
	cout << mktime(&rec) << endl;
	cout << time(NULL) << endl;
	return 0;
}