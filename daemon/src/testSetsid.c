/**
 * 程序功能: 让子进程创建一个会话，观察前后变化 
 * 运行结果: 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main()
{
	int pid = 0;
	char choice = 0;

	pid = fork();
	if (pid == -1) {
		perror("fork error");
	}
	if (pid != 0) {
		wait(NULL);
	} else {
		printf("[pid=%d]: 我是儿子，创建会话吗？(y/n)\n", getpid());
		scanf("%c", &choice);
		if (choice == 'y') {
			pid = setsid();
			if (pid == -1) {
				perror("setsid error");
			} else {
				printf("[pid=%d]: 创建会话[sid=%d]成功\n", getpid(), pid);
			}
		}
		pause();
	}
	return 0;
}

