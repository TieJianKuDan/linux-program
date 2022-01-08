/**
 * 程序功能: 测试一个进程可能同属于两个进程组吗 
 * 运行结果: 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
	int pid = fork();
	if (pid == 0) {
		pid = fork();
		if (pid == 0) {
			while (1) {
				printf("[pid=%d]: 我是孙子\n", getpid());
				sleep(3);
			}
		} else {
			while (1) {
				printf("[pid=%d]: 我是爸爸\n", getpid());
				sleep(3);
			}
		} 
	} else {
		while (1) {
			printf("[pid=%d]: 我是爷爷\n", getpid());
			sleep(3);
		}
	}
	return 0;
}

