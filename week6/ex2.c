#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
	char str1[] = "Some string";
	char str2[32];

	int fd[2];
	pipe(fd);

	pid_t childPid = fork();

	if (childPid) {
		write(fd[1], str1, strlen(str1) + 1);
		close(fd[1]);
		printf("String from parent: %s\n", str1);
	} else {
		read(fd[0], str2, sizeof(str2));
		close(fd[0]);
		printf("Transferred string from child: %s\n", str2);
	}

	return 0;
}