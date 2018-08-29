#include <stdio.h>
#include <limits.h>
#include <float.h>

int main() {
	int x;
	float y;
	double z;

	x = INT_MAX;
	y = FLT_MAX;
	z = DBL_MAX;

	printf("Integer size: %i, value: %i\n", sizeof(x), x);
	printf("Float size: %i, value: %i\n", sizeof(y), y);
	printf("Double size: %i, value: %i\n", sizeof(z), x);

	return 0;
}