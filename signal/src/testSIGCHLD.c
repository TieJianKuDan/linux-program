/**
 * 程序功能: 使用 SIGCHLD 信号回收子进程 
 * 运行结果: 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>

#define N 5

void sigchld(int signo)
{
	int pid = 0;

	printf("<===[ppid=%d]: 开始回收子进程\n", getpid());
	while ((pid = waitpid(-1, NULL, WNOHANG)) > 0) {
		printf("===>[ppid=%d]: 子进程[%d]回收完成\n", getpid(), pid);
	}
}

int main()
{
	int pids[N];
	int index = 0;
	int res = 0;
	sigset_t mask;
	
	// 注意这里提前对SIGCHLD屏蔽
	sigemptyset(&mask);
	sigaddset(&mask, SIGCHLD);
	sigprocmask(SIG_BLOCK, &mask, NULL);
	
	for (; index < N; index++) {
		pids[index] = fork();
		if (pids[index] == -1) {
			perror("fork error");
			exit(-1);
		}
		if (pids[index] == 0) break;
	}
	
	if (index < N) {
		while (1) {
			printf("======>[cpid=%d]: 正在执行任务...\n", getpid());
			sleep(3);
		}
	} else {
		struct sigaction act;
		act.sa_handler = sigchld;
		sigemptyset(&act.sa_mask);
		act.sa_flags = 0;
		res = sigaction(SIGCHLD, &act, NULL);
		if (res == -1) {
			perror("sigaction error");
			exit(-1);
		}
		sigprocmask(SIG_UNBLOCK, &mask, NULL);
		while (1) {
			printf("===>[ppid=%d]: 正在执行任务...\n", getpid());
			sleep(3);
		}
	}
	
	return 0;
	
}

