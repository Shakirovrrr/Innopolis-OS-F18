#include <stdio.h>
#include <pthread.h>

#define NTHREADS 10

void *threadJob(void *argp) {
	printf("\tThread number %d\n", *(int *) argp);

	return 0;
}

int main() {
	pthread_t threads[NTHREADS];
	for (int i = 1; i <= NTHREADS; ++i) {
		printf("Thread %d start\n", i);
		int iArg = i;
		pthread_create(&threads[i], 0, threadJob, &iArg);
		pthread_join(threads[i], 0); // Fix here
		printf("Thread %d end\n", i);
	}

	return 0;
}