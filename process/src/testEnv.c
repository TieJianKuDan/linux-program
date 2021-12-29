/**
 * 打印所有环境变
 */
#include <stdio.h>

extern char ** environ;

int main()
{
	for (int i = 0; environ[i]; i++) {
		printf("%s\n", environ[i]);
	}
	return 0;
}

