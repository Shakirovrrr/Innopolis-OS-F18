#include <memory.h>
#include <stdio.h>
#include <malloc.h>

#ifdef _WIN32
#define msize(x) _msize(x)
#elif linux
#define msize(x) malloc_usable_size(x)
#elif __APPLE__
#define msize(x) malloc_size(x)
#endif


void *mRealloc(void *memory, size_t newSize) {
	if (newSize == 0) {
		if (memory) {
			free(memory);
		}
		return NULL;
	}

	if (!memory) {
		return malloc(newSize);
	}

	size_t memorySize = msize(memory);

	if (memorySize > newSize) {
		memorySize = newSize;
	}

	void *newMemory = malloc(newSize);
	memcpy(newMemory, memory, memorySize);

	free(memory);

	return newMemory;
}

int main() {
	int *arr = calloc(10, sizeof(int));
	for (int i = 0; i < 10; ++i) {
		arr[i] = i;
		printf("%d ", arr[i]);
	}
	printf("\n");

	arr = mRealloc(arr, 15);
	for (int j = 0; j < 15; ++j) {
		printf("%d ", arr[j]);
	}
	printf("\n");

	free(arr);

	return 0;
}