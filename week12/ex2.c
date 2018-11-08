#include <stdio.h>
#include <errno.h>

int main(int argc, char *argv[]) {
	if (argc > 3) {
		perror("Too many arguments\n");
		return E2BIG;
	}

	if (argc == 1) {
		while (!feof(stdin)) {
			char c;
			scanf("%c", &c);
			printf("%c", c);
		}

		return 0;
	}

	if (argc == 2) {
		FILE *outFile = fopen(argv[1], "w");

		while (!feof(stdin)) {
			char c;
			scanf("%c", &c);
			fprintf(outFile, "%c", c);
			printf("%c", c);
		}

		fclose(outFile);
		return 0;
	}

	if (argc == 3) {
		if (!(argv[1][0] == '-' && (argv[1][1] == 'a' || argv[1][1] == 'A'))) {
			perror("Unknown argument or wrong order of arguments\n");
			return EINVAL;
		}

		FILE *outFile = fopen(argv[2], "a");

		while (!feof(stdin)) {
			char c;
			scanf("%c", &c);
			fprintf(outFile, "%c", c);
			printf("%c", c);
		}

		fclose(outFile);
		return 0;
	}

	return 0;
}