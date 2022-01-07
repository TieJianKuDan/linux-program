/**
 * 程序功能: 测试使用fork新建子进程
 * 运行结果:
 */

#include <stdio.h>
#include <unistd.h>

#define N 1

int main()
{
	int pid = 0;
	int i = 0; 

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
		printf("This is child process %d and my parent's pid is %d\n", 
				getpid(), getppid());
		printf("Child process %d: uid = %d gid = %d\n", 
				getpid(), getuid(), getgid());
	} else {
		printf("Parent %d has created all child process\n", getpid());
		printf("Parent process %d: uid = %d, gid = %d\n", 
				getpid(), getuid(), getgid());
		sleep(1);
	} 
	
	return 0;
}

