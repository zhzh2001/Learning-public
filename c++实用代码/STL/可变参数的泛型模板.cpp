#include <iostream>
#include <stdarg.h>

using namespace std;

template <typename T>
T max ( int num, ... )
{
	T m;
	va_list ap;
	va_start (ap, num);
	m = va_arg(ap, T);
	for(int i= 1; i< num; ++i)
	{
		T t = va_arg (ap, T);
		if ( t > m ) m = t;
	}
	va_end (ap);
	return m;
}

int main()
{
	double n = max<double>(5, 5.0, 6.9 ,3.9 ,8.6 ,5.1); /* ��5�������е����ֵ */
	cout << "���ֵΪ" << n<<"\n";
	system("pause");for (;;);
	return 0;
}


