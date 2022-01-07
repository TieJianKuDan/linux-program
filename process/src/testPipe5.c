/**
 * 程序功能: 实现 ls | wc -l 子进程1->ls 子进程2->wc -l 父进程负责回收子进程
 * 运行结果:
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	int pids[2];
	int fds[2];
	int res = 0;
	int i = 0;

	res = pipe(fds);
	if (res == -1) {
		perror("pipe error");
		exit(-1);
	}
	for (; i < 2; i++) {
		pids[i] = fork(); 
		if (pids[i] == -1) {
			perror("fork error");
			exit(-1);
		}
		if (pids[i] == 0) break;
	}
	if (i == 2) {
		int status = 0;
		int pid = 0;
		// 注意！！！
		close(fds[0]);
		close(fds[1]);
		while ((pid = wait(&status)) > 0) {
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
	if (i == 1) {
		res = close(fds[1]);
		if (res == -1) {
			perror("close error");
		}
		res = dup2(fds[0], STDIN_FILENO);
		if (res == -1) {
			perror("dup2 error");
			exit(-1);
		}
		res = execlp("wc", "wc", "-l", NULL);
		if (res == -1) {
			perror("execlp error");
			exit(-1);
		}
	}
	if (i == 0) {
		res = close(fds[0]);
		if (res == -1) {
			perror("close error");
		}
		res = dup2(fds[1], STDOUT_FILENO);
		if (res == -1) {
			perror("dup2 error");
			exit(-1);
		}
		res = execlp("ls", "ls", NULL);
		if (res == -1) {
			perror("execlp error");
			exit(-1);
		}
	}
}

