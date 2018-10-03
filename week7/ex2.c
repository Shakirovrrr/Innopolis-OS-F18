#include <stdio.h>
#include <stdlib.h>

int main() {
	size_t n = 0;
	printf("N?  ");
	scanf("%d", &n);

	int *arr = (int *) calloc(n, sizeof(int));
	if (!arr){
		perror("Cannot allocate array.");
	}

	for (int i = 0; i < n; ++i) {
		arr[i] = i;
	}

	for (int i = 0; i < n; ++i) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	free(arr);

	return 0;
}