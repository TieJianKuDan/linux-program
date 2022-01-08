/**
 * 程序功能: 测试匿名mmap，同时测试偏移量 
 * 运行结果: 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>

int main()
{
	char * fp = NULL;
	int pid = 0;
	
	fp = mmap(NULL, 10, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	if (fp == MAP_FAILED) {
		perror("mmap error");
	} 
	pid = fork();
	if (pid == 0) {
		strcpy(fp, "This child! Hello everybody!\n");
	}else {
		wait(NULL);
		printf("%s", fp);	
	}

	return 0;
}

