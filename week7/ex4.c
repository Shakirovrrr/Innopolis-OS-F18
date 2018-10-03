#include <stdio.h>
#include "mrealloc.h"

int main() {
	int *arr = calloc(10, sizeof(int));
	for (int i = 0; i < 10; ++i) {
		arr[i] = i;
		printf("%d ", arr[i]);
	}
	printf("\n");

	arr = mRealloc(arr, sizeof(int) * 8);
	for (int j = 0; j < 8; ++j) {
		printf("%d ", arr[j]);
	}
	printf("\n");

	free(arr);

	return 0;
}