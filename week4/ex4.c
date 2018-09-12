#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>

int main() {
	size_t bufferSize = 256;
	char *command = malloc(sizeof(char) * bufferSize);

	while (1) {
		waitpid(-1, 0, 0);
		printf("Command > ");
		getline(&command, &bufferSize, stdin);

		if (strcmp(command, "exit\n") == 0) {
			break;
		}

		pid_t forkPid = fork();
		if (forkPid) {
			continue;
		} else {
			system(command);
			exit(0);
		}
	}

	free(command);

	return 0;
}