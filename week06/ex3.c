#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void signalHandler(int signum) {
	printf("\nTerminated.\n");
	exit(1);
}

int main() {
	signal(SIGINT, signalHandler);

	while (1) {
		printf("Terminate me!\n");
		fflush(stdout);
		sleep(1);
	}

	return 0;
}