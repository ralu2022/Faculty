#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int getNrAparitii(char* s, char c)
{
	int nr = 0;
	while (strchr(s, c) != NULL)
	{
		nr++;
		s = strchr(s, c) + 1;
	}
	return nr;
}

int main()
{
	char c;
	char* s;
	char nr, n;

	printf("Numarul de litere din nume: ");
	scanf_s("%d", &n);

	s = (char*)malloc(n * sizeof(char));
	if (s == NULL);
	{
		perror("Memorie insuficienta");
		return 1;
	}
	printf("Numele dvs.:");
	scanf_s("%s", s);
	printf("Litera cautata:");
	scanf_s("%c", c);

	nr = getNrAparitii;

	printf("Hello, %s!, In numele tau apare litera %c de %d ori!", s, c, nr);

	free(s);
	return 0;
}