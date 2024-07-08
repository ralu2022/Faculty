#include <stdio.h>
#include <malloc.h>
typedef struct tstiva tstiva;
struct tstiva {
	char info;
	tstiva* leg;
} *cap;
int introducere(char c);
int scoatere();
void afisare();
int main() {
	char c;
	int op;
	op = -1;
	do {
		printf("Introduceti optiunea dvs:\n");
		printf("1 pt adaugare in stiva:\n");
		printf("2 pt scoatere din stiva:\n");
		printf("3 pt afisarea stivei:\n");
		printf("0 pt iesire din program:\n");
		scanf_s("%d", &op);
		getchar();
		switch (op) {
		case 1: {
			printf("Introduceti un caracter:");
			scanf_s("%c", &c);
			getchar();
			if (introducere(c)) {
				printf("Am introdus in stiva elementul: %c\n", c);
			}
			break;
		}
		case 2: {
			if (scoatere()) {
				printf("Am scos un element din stiva\n");
			}
			break;
		}
		case 3: {
			afisare();
			break;
		}
		case 0: {
			break;
		}
		default: {
			printf("Introduceti 1,2,3 sau 0");
		}
		}
	} while (op != 0);
}
int introducere(char c) {
	tstiva* p;
	p = (tstiva*)malloc(sizeof(tstiva));
	if (p == NULL) {
		return 0;
	}
	p->info = c;
	p->leg = cap;
	cap = p;
	return 1;
}
int scoatere() {
	tstiva* p = cap;
	if (p == NULL) {
		return 0;
	}
	cap = p->leg;
	free(p);
	return 1;
}
void afisare() {
	tstiva* p = cap;
	printf("Stiva contine:");
	while (p != NULL) {
		printf("%c", p->info);
		p = p->leg;
	}
	printf("\n");
}