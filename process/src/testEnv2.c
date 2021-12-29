#include <stdio.h>
#include <stdlib.h>

int main()
{
	// 获得环境变量
	char * res = getenv("PATH");
	if (res == NULL) {
		printf("环境变量{%s}不存在\n", "PAHT");
	}
	printf("PAHT = %s\n", res);	

	// 设置环境变量
	setenv("AUTHOR", "铁剑库丹", 1);
	res = getenv("AUTHOR");
	if (res == NULL) {
		printf("环境变量{%s}不存在", "AUTHOR");
	}
	printf("PAHT = %s\n", res);	

	// 删除环境变量
	res = unsetenv("PATH");
	if (res == -1) {
		perror("删除环境变量失败");
	}
	res = getenv("PATH");
	if (res == NULL) {
		printf("环境变量{%s}不存在\n", "PAHT");
	}
	printf("PAHT = %s\n", res);	
	
	return 0;
}

