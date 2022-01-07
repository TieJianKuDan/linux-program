/**
 * 程序功能: 测试管道有多个进程在读，一个进程写
 * 运行结果: 可以
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
	if (count == COUNT) {
		// 关闭读端
		close(fds[0]);
		// res = dup2(fds[1], STDOUT_FILENO);
		// close(fds[1]);
		if (res == -1) {
			perror("dup2 error");
		}
		int index = 0;
		while (1) {
			// printf("%d-%s", index, MESSAGE);
			write(fds[1], MESSAGE, sizeof(MESSAGE));
			index++;
		 	sleep(1); // sleep + printf 读进程会总是阻塞，why?
		}
	} else {
		char buf[128];
		// 关闭写端
		close(fds[1]);
		while (1) {
			res = read(fds[0], buf, sizeof(buf));
			if (res == -1) {
				perror("read error");
				sleep(1);
			} else {
				printf("pid=%d: %s", getpid(), buf);
			}
		}
	}
	return 0;
}

