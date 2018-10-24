#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

#define BUFFER_SIZE 8
#define CURRENT_TIME time(NULL)

int count;
int buffer[BUFFER_SIZE];

time_t timestamp;

void *producer(void *argp) {
	while (1) {
		if (count >= BUFFER_SIZE) {
			sleep(1);
			continue;
		}

		buffer[count - 1] = count;
		count++;
	}
}

void *consumer(void *argp) {
	while (1) {
		if (count <= 0) {
			sleep(1);
			continue;
		}

		if (CURRENT_TIME - timestamp > 1) {
			fflush(stdout);
			printf("%d\n", buffer[count - 1]);
			timestamp = CURRENT_TIME;
		}
		buffer[count - 1] = 0;
		count--;
	}
}

int main() {
	count = 0;
	timestamp = CURRENT_TIME;

	pthread_t producerThread, consumerThread;
	pthread_create(&producerThread, NULL, producer, NULL);
	pthread_create(&consumerThread, NULL, consumer, NULL);

	pthread_join(producerThread, NULL);
	pthread_join(consumerThread, NULL);

	return 0;
}