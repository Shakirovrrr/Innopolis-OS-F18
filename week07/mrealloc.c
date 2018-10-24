#include "mrealloc.h"

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