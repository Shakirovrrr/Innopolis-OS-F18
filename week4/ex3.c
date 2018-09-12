#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	char *buffer = malloc(sizeof(char) * 256);
	while (1) {
		printf("Command_> ");
		scanf("%s", buffer);
		if (strcmp(buffer, "exit") == 0) {
			break;
		}

		system(buffer);
		//execl("/bin/sh", "sh", "-c", buffer, (char *) 0);
	}

	return 0;
}