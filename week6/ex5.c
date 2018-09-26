#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

void signalHandler(int signum) {
	switch (signum) {
		case SIGINT:
			printf("\nTerminated.\n");
			exit(1);
	}
}

int main() {
	signal(SIGINT, signalHandler);

	pid_t childPid = fork();
	if (childPid) {
		sleep(10);
		kill(childPid, SIGINT);
	} else {
		while (1) {
			printf("I'm alive!\n");
			sleep(1);
		}
	}

	return 0;
}