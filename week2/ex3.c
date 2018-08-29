#include <stdio.h>
#include <stdlib.h>

void printTriangle(int n) {
	int width = 2 * n - 1;

	char *printed = malloc(sizeof(char) * width + 1);
	for (int i = 0; i < width; i++) {
		printed[i] = ' ';
	}
	printed[width + 1] = '\0';

	int start = width / 2;
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < 2 * i - 1; j++) {
			printed[start + j] = '*';
		}
		printf("%s", printed);
		printf("\n");
		start--;
	}

	free(printed);
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Wrong command line args.");
		return 1;
	}

	int n = atoi(argv[1]);

	printTriangle(n);

	return 0;
}