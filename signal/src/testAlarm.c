/**
 * 程序功能: 测试1s能数多少个数 
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
	int pid = 0;
	unsigned long * fp = NULL;
	
	fp = mmap(NULL, 8, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANON, -1, 0);	
	if (fp == MAP_FAILED) {
		perror("mmap error");
	}
	pid = fork();
	if (pid == -1) {
		perror("fork error");
	} 
	if (pid == 0) {
		alarm(1);
		while (1) {
			(*fp)++;
		}
	}
	if (pid != 0) {
		wait(NULL);
		printf("%ld\n", *fp);
	}
	return 0;	
}

