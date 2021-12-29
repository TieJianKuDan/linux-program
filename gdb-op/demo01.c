#include <stdio.h>
#include <stdlib.h>

int add(int a, int b)
{
	return a + b;
}

int main(int args, char* arg[]) 
{
	int a = atoi(arg[1]);
	int b = atoi(arg[2]);
	printf(" %d + %d = %d\n", a, b, add(a, b));
	return 0;
}
