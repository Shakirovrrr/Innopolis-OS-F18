#include <stdio.h>

void swap(int *a, int *b) {
	int t = *a;
	*a = *b;
	*b = t;
}

int main(){
	printf("2 integers: ");
	int a, b;
	scanf("%i %i", &a, &b);

	swap(&a, &b);

	printf("Swapped: %i %i", a, b);

	return 0;
}