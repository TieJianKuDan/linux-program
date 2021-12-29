#include <stdio.h>
#include "mymath.h"

int main()
{
	int a = 2;
	int b = 3;
	printf("%d + %d = %d\n", a, b, add(a, b));	
	return 0;
}
