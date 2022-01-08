/**
 * 程序功能: 父进程发信号终止子进程 
 * 运行结果: 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

int main()
{
	int pids[5];
	int res = 0;
	int i = 0;
	
	for (; i < 5; i++) {
		pids[i] = fork();
		if (pids[i] == -1) {
			perror("fork error");
			exit(-1);
		}
		if (pids[i] == 0) {
			break;
		}
	}
		
	if (i != 5) {
		while (1) {
			printf("[cpid=%d] I am still alive!\n", getpid());
			sleep(1);
		}
		
	} else {
		sleep(5);
		printf("[ppid=%d] Killer is comming\n", getpid());
		
		for (i = 0; i < 5; i++) {
			res = kill(pids[i], SIGKILL);
			if (res == -1) {
				perror("send signal error");
			}
			printf("[ppid=%d] Who is next!!!\n", getpid());
			sleep(1);
		}
	}

	return 0;
}

