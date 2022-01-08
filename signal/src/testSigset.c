/**
 * 程序功能: 打印未决信号 
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
	sigset_t set;
	sigset_t oldset;
	int res = 0;
	
	sigfillset(&set);
//	没必要，9 和 19 不能被阻塞
//	sigdelset(&set, SIGKILL);
	sigprocmask(SIG_BLOCK, &set, &oldset);
	
	while (1) {
		res = sigpending(&oldset);
		if (res == -1) {
			perror("sigpending error");
		}
		if (sigismember(&oldset, SIGHUP)) {
			printf("未决信号：SIGHUP\n");
		}
		if (sigismember(&oldset, SIGINT)) {
			printf("未决信号：SIGINT\n");
		}
		if (sigismember(&oldset, SIGQUIT)) {
			printf("未决信号：SIGQUIT\n");
		}
		if (sigismember(&oldset, SIGTERM)) {
			printf("未决信号：SIGTERM\n");
		}
		printf("分割线----------->\n");
		sleep(1);
	}	
}

