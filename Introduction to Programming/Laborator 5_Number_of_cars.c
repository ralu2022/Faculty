#include<stdio.h>
#include<string.h>
#include<malloc.h>

struct tpers
{
	char nume[50];
	int nrMasini;
};

typedef struct tpers tpers;

void main()

{
	tpers *pers = malloc(sizeof(tpers));

	printf("Numele pers:");
	gets(pers->nume);

	printf("Numar masini:");
		scanf_s("%d", &pers->nrMasini);
	printf("Buna,%s, ai %d masini!", pers->nume, pers->nrMasini);

	return 0;

}