#include <stdio.h>

#include "mymath.h"

int main()
{
	int a = 0, b = 0;
	printf("Please input tow numbers with ',' to separate.\n");
	scanf("%d,%d", &a, &b);
	printf("%d + %d = %d\n", a, b, addInt(a, b));
	return 0;
}
