#include <stdio.h>
#include <malloc.h>

int main() {
	// s was not allocated, so "*s = foo"
	// was causing a segmentation fault
	char **s = (char **) malloc(sizeof(char *));
	char foo[] = "Hello World";
	*s = foo;
	printf("s is %s\n", s);
	s[0] = foo;
	printf("s[0] is %s\n", s[0]);
	return 0;
}