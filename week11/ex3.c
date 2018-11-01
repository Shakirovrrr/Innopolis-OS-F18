#include <stdio.h>
#include <unistd.h>

int main() {
	printf("Hello");
	fork();
	printf("\n");

	return 0;
}