/**
 * 程序功能: 测试阻塞的普通信号不支持排队 
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
		printf("正在处理信号中...\n");
	}
	printf("信号处理完毕\n");
}

int main()
{
	int res = 0;
	struct sigaction act;
	struct sigaction oldact;

	act.sa_handler = sig_int;
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

