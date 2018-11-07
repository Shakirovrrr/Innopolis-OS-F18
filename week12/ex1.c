#include <stdio.h>

int main() {
	FILE *rand = fopen("/dev/random", "r");
	char randomChars[21];

	fscanf(rand, "%c", randomChars);
	fclose(rand);

	randomChars[20] = '\0';
	char *iter = randomChars;
	// Convert to displayable chars
	for (int i = 0; i < 20; ++i, iter++) {
		*iter = (*iter % (char) 62) + (char) 65;
	}

	FILE *outFile = fopen("ex1.txt", "w");
	fprintf(outFile, "%s\n", randomChars);
	fclose(outFile);

	return 0;
}