/**
 * 程序功能: 测试局部静态变量和全局静态变量其实没有区别 
 * 运行结果: 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int * fun() {
	static int val = 233;
	return &val;
}


int main()
{
	int * p = fun();
	printf("%d\n", *p);
	*p += 100;
	printf("%d\n", *p);
}
