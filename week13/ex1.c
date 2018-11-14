#include <stdio.h>
#include <malloc.h>
#include <errno.h>

//#define NEW(T) malloc(sizeof(T))
#define NNEW(T, N) malloc(sizeof(T) * (N))

int main() {
	FILE *inputFile = fopen("input.txt", "r");
	if (!inputFile) {
		return ENOENT;
	}
	char *strBuf = NNEW(char, 128);

	size_t length = 0;
	ssize_t charsRead = getline(&strBuf, &length, inputFile);
	printf("N chars: %d, length: %d, line: %s", charsRead, length, strBuf);

	free(strBuf);
	return 0;
}