#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
	char str1[] = "Some string";
	char str2[32];

	int fd[2];
	pipe(fd);

	write(fd[1], str1, strlen(str1) + 1);
	close(fd[1]);
	read(fd[0], str2, sizeof(str2));
	close(fd[0]);

	printf("Original string: %s\n", str1);
	printf("String from pipe: %s\n", str2);

	return 0;
}