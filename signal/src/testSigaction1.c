/**
 * 程序功能: 为 SIGTERM 设置捕捉函数 
 * 运行结果: 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>

void sig_int(int signo)
{
	printf("捕捉到信号 %d\n", signo);
}

int main()
{
	int res = 0;
	struct sigaction act;
	struct sigaction oldact;

	act.sa_handler = sig_int;
	// 不要这样做，会捕捉不到的
	// act.sa_sigaction = NULL;
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask, SIGQUIT);
	act.sa_flags = 0;
	act.sa_restorer = NULL;

	res = sigaction(SIGINT, &act, &oldact);
	if (res == -1) {
		perror("sigaction error");
	}

	while (1) sleep(5);	
}

