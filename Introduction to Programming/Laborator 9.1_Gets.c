#include <stdio.h>

int main() {
	char str[50];

	printf("Enter a string : ");
	gets_s(str);

	printf("You entered: %s", str);

	return(0);
}
