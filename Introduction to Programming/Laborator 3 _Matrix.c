#include<stdio.h>

void main()
{
	int a[10][10];
	int m, n;
	int i, j;

	printf("Introduceti nr de linii: ");
	scanf_s("%d", &m);
	printf("Introduceti nr de coloane: ");
	scanf_s("%d", &n);

	printf("Introduceti elementele matricei: \n");
	for (i = 0; i < m; i++)
		for (j = 0; j < n; j++)
		{
			printf("\tElem [%d,%d]= ", i + 1, j + 1);
			scanf_s("%d", &a[i][j]);
		}

	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
			printf("%5d", a[i][j]);
		printf("\n");
	}
}