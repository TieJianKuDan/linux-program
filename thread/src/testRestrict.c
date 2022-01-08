/**
 * 程序功能: 测试 restrict 编译器做出的优 
 * 运行结果: 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	int * restrict restar = (int *)malloc(sizeof(int));
	int * par = restar;
	*restar = 1;
	*restar += 3;
	*par *= 3;
	*restar += 3;
	printf("%d\n", *restar);
	return 0;	
}

