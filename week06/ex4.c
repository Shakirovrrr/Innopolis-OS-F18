#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void signalHandler(int signum) {
	switch (signum) {
		case SIGINT:
			printf("\nTerminated.\n");
			exit(1);
		case SIGSTOP:
		case SIGKILL:
			printf("\nActually I cannot handle these signals.\n");
			break;
		case SIGUSR1:
			printf("\nCaught user signal 1.\n");
			break;
		default:
			printf("\nUnhandled signal %d\n", signum);
			break;
	}
}

int main() {
	signal(SIGINT, signalHandler);
	signal(SIGSTOP, signalHandler);
	signal(SIGKILL, signalHandler);
	signal(SIGUSR1, signalHandler);

	while (1) {
		sleep(1);
	}

	return 0;
}