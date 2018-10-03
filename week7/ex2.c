#include <stdio.h>
#include <stdlib.h>

#define N 10

int main() {
	int *arr = (int *) calloc(N, sizeof(int));

	for (int i = 0; i < N; ++i) {
		arr[i] = i;
	}

	for (int i = 0; i < N; ++i) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	free(arr);

	return 0;
}