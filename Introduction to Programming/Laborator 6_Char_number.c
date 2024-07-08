#include <stdio.h>
#include <string.h>

void main()
{
	char s[20];

	printf("Numele tau este:");
	gets(s);

	printf("Hello, %s, numele tau are %ld caractere!", s, strlen(s));

}