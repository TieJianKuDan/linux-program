/**
 * 程序功能: 创建守护进程 
 * 运行结果: 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

void createDaemon() {
	int pid = 0;

	pid = fork();
	if (pid == -1) {
		perror("fork error");
		exit(-1);
	}
	if (pid > 0) {
		// 让父进程结束，因为后台服务的话不需要父进程这种依赖于终端的进程
		exit(0);
	}
	if (pid == 0) {
		// 最重要的一步——脱离终端会话，创建自己的会话
		pid = setsid();
		if (pid == -1) {
			perror("setsid error");
			exit(-1);
		}
		umask(00);
		chdir("/");	
		close(0);
		open("/dev/null", O_RDWR);
		dup2(0, 1);
		dup2(0, 2);
	}
	
}

int main()
{
	createDaemon();	
	while(1) {
		sleep(10);
	}
}

