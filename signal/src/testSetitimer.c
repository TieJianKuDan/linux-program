/**
 * 程序功能: 使用setitimer实现alarm计数 
 * 运行结果: 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/wait.h>

int main()
{
	int res = 0;
	int pid = 0;
	unsigned long * fp = NULL;
	struct itimerval nv;
	struct itimerval ov;
	
	nv.it_interval.tv_sec = 1;
	nv.it_interval.tv_usec = 0;
	nv.it_value.tv_sec = 1;
	nv.it_value.tv_usec = 0;

	fp = mmap(NULL, 8, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANON, -1, 0);	
	if (fp == MAP_FAILED) {
		perror("mmap error");
	}

	pid = fork();
	if (pid == -1) {
		perror("fork error");
	} 
	if (pid == 0) {
		res = setitimer(ITIMER_REAL, &nv, &ov);	
		if (res == -1) {
			perror("setitimer error");
		}
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

