#include <stdio.h>
#include <malloc.h>

char *reverseString(char *str) {
	char *it = str;
	while (*it != '\0') {
		it++;
	}

	char *rev = malloc(sizeof(char) * 256);
	char *itRev = rev;
	it--;
	while (it >= str) {
		*itRev = *it;
		it--;
		itRev++;
	}
	*itRev = '\0';

	return rev;
}

int main() {
	char *str = malloc(sizeof(char) * 256);

	printf("Type a string: ");
	scanf("%s", str);
	printf("\n");

	char *rev = reverseString(str);

	printf("Reversed: %s", rev);

	free(str);
	free(rev);
	return 0;
}