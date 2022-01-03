/**
 * 测试管道有多个进程在写，多个进程在读
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

#define MESSAGE "hello world!\n"
#define COUNT 3

int main()
{
	int fds[2];
	int res = pipe(fds);
	int count = 0;
	int pid = 0;

	if (res == -1) {
		perror("create pipe unsuccessful");
		exit(1);
	}	
	for (; count < COUNT; count++) {
		pid = fork();
		if (pid == -1) {
			perror("fork error");
			exit(1);
		}
		if (pid == 0) break;	
	}
	if (count % 2 == 0) {
		char buf[128];
		// 关闭写端
		// res = close(fds[1]);
		if (res == -1) {
			perror("close error");
		}
		while (1) {
			read(fds[0], buf, sizeof(buf));
			printf("[pid=%d]", getpid());
			printf(buf);
		}
	}
	if (count % 2 != 0) {
		// 关闭写端
		// close(fds[0]);
		while (1) {
			res = write(fds[1], MESSAGE, sizeof(MESSAGE));
			if (res == -1) {
				perror("write error");
				exit(-1);
			} 
			sleep(1);
		}
	}
	return 0;
}

