#include <stdio.h>
#include <stdlib.h>

#define ARRLEN 5

void bubbleSort(int n, int *arr) {
	int swap;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n - i - 1; ++j) {
			if (arr[j] > arr[j + 1]) {
				swap = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = swap;
			}
		}
	}
}

int main() {
	int arr[ARRLEN] = {23, 14, 55, 8, 10};
	bubbleSort(ARRLEN, arr);

	for (int i = 0; i < ARRLEN; ++i) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	return 0;
}