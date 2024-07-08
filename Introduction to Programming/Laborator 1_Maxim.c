#include<stdio.h>
#include<malloc.h>
#include<limits.h>



int maxim(int n, int* a);

int main()
{
	int* a, n;
	int max;

	printf("Scrieti lungimea vectorului:");
	scanf_s("%d", &n);

	a = (int*)calloc(n, sizeof(int));
	if (a == NULL)
	{
		perror("Memorie insuficienta");
		return 1;
	}

	for (int i = 0; i < n; i++)
	{
		printf("a[%d]=", i);
		scanf_s("%d", &a[i]);
	}

	max = maxim(n, a);

	printf("Max este %d", max);
}

int maxim (int n, int* a)

{
int max = INT_MIN;

	for (int i = 0; i < n; i++)
	{
		if (a[i] > max)
		{
			max = a[i];
		}
	}
	return max;
}
