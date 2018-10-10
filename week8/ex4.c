#include <stdio.h>
#include <malloc.h>
#include <sys/resource.h>
#include <unistd.h>

int main() {
	struct rusage usage;
	for (int i = 0; i < 10; ++i) {
		calloc(1024, 10 * 1024); // 1024 objects with size 10 KB
		getrusage(RUSAGE_SELF, &usage);
		printf("Memory usage: %dK\n", usage.ru_maxrss);
		sleep(1);
	}

	return 0;
}