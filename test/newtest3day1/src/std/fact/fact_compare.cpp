#include <bits/stdc++.h>
#include <mpreal.h>
using namespace std;
using namespace mpfr;
const long double huge = 1e4000L;
const int digits = 100;
const mpreal fhuge = "1e323228480";
int main()
{
	int n, k;
	cin >> n >> k;
	long double ans = 1.0L;
	mpreal::set_default_prec(digits2bits(digits));
	mpreal fans = 1.0;
	cout.precision(k);
	for (int i = 1; i <= n; i++)
	{
		ans *= i;
		fans *= i;
		if (ans > huge)
			ans /= huge;
		if (fans > fhuge)
		{
			fans /= fhuge;
			fans *= 1e100;
		}
		if (i > 8e7)
		{
			int t = floor(log10(ans));
			long double dt = ans / std::pow(10.0L, t);
			stringstream ss1, ss2;
			ss1.precision(k);
			ss1 << dt;
			ss2.precision(digits);
			ss2 << fans;
			if (ss1.str().length() < 2)
				continue;
			stringstream ss3(ss1.str().substr(2));
			long long val;
			ss3 >> val;
			if (ss2.str()[ss1.str().length()] >= '5')
				val--;
			stringstream ss4;
			ss4.width(ss1.str().length() - 2);
			ss4.fill('0');
			ss4 << val;
			if (ss4.str() != ss2.str().substr(2, ss4.str().length()))
				cout << i << ' ' << ss1.str() << ' ' << ss2.str() << endl;
			if (i % 1000000 == 0)
				cout << i << endl;
		}
	}
	return 0;
}