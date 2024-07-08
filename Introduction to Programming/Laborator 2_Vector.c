#include<stdio.h>
void main()
{
	int a[20];	

	
	int n;
	printf("Dati nr de elemente: ");
	scanf_s("%d", &n);

	
	printf("Introduceti elementele: \n");
	for (int i = 0; i < n; i++)
	{
		printf("elem %d: ", i + 1);
		scanf_s("%d", &a[i]);
	}

	
	printf("Elementele vectorului sunt: ");
	for (int i = 0; i < n; i++)
		printf("%d", a[i]);

}