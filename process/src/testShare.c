/**
 * 程序功能: 测试进程之间读时共享，写时复制
 * 运行结果:
 */

#include <stdio.h>
#include <unistd.h>

#define N 2

int main()
{
	int pid = 0;
	int i = 0; 
	int test = 0;
	test = 6;
	for (i = 1; i <= N; i++) {
		pid = fork();
		if (pid == -1) {
			perror("Create child process fail\n");
		}
		if (pid > 0) {
			printf("Create child process %d successfully!\n", pid);
		}
		if (pid == 0) {
			break;
		}
	}

	if (i <= N) {
		// 子进程逻辑
		printf("Child: pid = %d test = %d\n", getpid(), test);
		test = 10;
		printf("Child: pid = %d test = %d\n", getpid(), test);
	} else {
		printf("Parent: pid = %d test = %d\n", getpid(), test);
		sleep(10);
		printf("Parent: pid = %d test = %d\n", getpid(), test);
	}
	
	return 0;
}

