#include<stdio.h>
#include<stdarg.h>,

double maxim(int n, ...)
{
	double max = -1E10;
	double x;

	va_list a;
	va_start(a, n);

	for (int i = 0; i < n; i++)
	{
		x = va_arg(a, double);
		if (x > max)
		{
			max = x;

		}
	}
	va_end(a);
	return max;
}

int main()
{
	double max;

	max = maxim(4, 2.45, 3.4, 7.0, 2.0);
	printf("Maximul este %.2lf", max);
}