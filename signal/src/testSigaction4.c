/**
 * 程序功能: 测试信号捕获使得信号屏蔽字的作用 
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
	for (int i = 0; i < 5; i++) {
		sleep(1);
		printf("===>正在处理[信号%d]中...\n", signo);
	}
	printf("信号处理完毕<===\n");
}

int main()
{
	int res = 0;
	struct sigaction act;
	struct sigaction oldact;

	act.sa_handler = sig_int;
	sigfillset(&act.sa_mask);
	act.sa_flags = 0;

	res = sigaction(SIGINT, &act, &oldact);
	if (res == -1) {
		perror("sigaction error");
	}
	
	res = sigaction(SIGQUIT, &act, &oldact);
	if (res == -1) {
		perror("sigaction error");
	}

	while (1) {
		printf("主程序正在执行业务...\n");
		sleep(1);
	}	
}

