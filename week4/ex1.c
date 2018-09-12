#include <stdio.h>
#include <sys/types.h>

int main() {
	char forked = fork();

	if (forked) {
		printf("Hello from parent! My PID is %d.\n", getpid());
	} else {
		printf("Hello from child! My PID is %d.\n", getpid());
	}

	return 0;
}
