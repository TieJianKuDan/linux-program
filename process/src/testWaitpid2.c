/**
 * 程序功能: 回收所有子进程
 * 运行结果:
 */
 
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	int status = 0;
	int pids[2] = {0, 0};
	int index = 0;	
	int pid = 0;

	for (;index < 2; index++) {
		pids[index] = fork();
		if (pids[index] == -1) perror("fork fail");
		if (pids[index] == 0) break;
	}

	if (index == 2) {
		while ((pid = waitpid(-1, &status, 0)) > 0){
			if (pid == -1) {
				perror("child clean fail\n");
			}
			if (pid > 0) {
				printf("child[%d] clean successfully\n", pid);
			}
			if (WIFEXITED(status)) {
				printf("exit value = %d\n", WEXITSTATUS(status));
			}
			if (WIFSIGNALED(status)) {
				printf("terminating signal = %d\n", WTERMSIG(status));
			}
		}

	}

	if (index == 0) {
		int res = execlp("ls", "ls", "-lah", NULL);
		if (res == -1) {
			printf("execlp fail");
		}
	}

	if (index == 1) {
		int res = execl("out/badcode", "out/badcode", NULL);
		if (res == -1) {
			printf("execlp fail");
		}
	}

	return 0;
}

