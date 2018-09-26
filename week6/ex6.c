#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>

void signalHandler(int signum) {
	switch (signum) {
		case SIGINT:
			printf("Stopped.\n");
			exit(0);
		default:
			break;
	}
}

int main() {
	int fd1[2], fd2[2];
	pipe(fd1);
	pipe(fd2);

	pid_t child1Pid = 1;
	pid_t child2Pid = 1;

	child1Pid = fork();
	if (!child1Pid) { // Child 1
		pid_t received;
		read(fd1[0], &received, sizeof(received));
		printf("Child 1: Received PID %d, going to sleep.\n", received);
		sleep(6);
		printf("Child 1: Awake, stopping process %d\n", received);
		kill(received, SIGSTOP);
		printf("Child 1: Stopped, going to sleep...\n");
		sleep(4);
		printf("Child 1: Awake, resuming process %d\n", received);
		kill(received, SIGCONT);
		printf("Child 1: Resumed, going to sleep...\n");
		sleep(4);
		printf("Child 1: Awake, asking process %d to terminate.\n", received);
		kill(received, SIGINT);
		printf("Child 1: Asked process %d to terminate.\n", received);
	} else {
		child2Pid = fork();
	}

	if (!child2Pid) { // Child 2
		signal(SIGINT, signalHandler);
		while (1) {
			printf("Child 2: Doing something...\n");
			sleep(1);
		}
	}
	if (child1Pid && child2Pid) { // Parent
		printf("Parent: Sending 2nd child PID %d to 1st child...\n", child2Pid);
		write(fd1[1], &child2Pid, sizeof(child2Pid));
		close(fd1[1]);
		printf("Parent: Sent PID. Waiting for changes in 2nd child...\n");
		pid_t child2Wait = waitpid(child2Pid, 0, 0);
		printf("Parent: 2nd child terminated.");
	}

	return 0;
}