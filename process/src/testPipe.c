/**
 * 程序功能: 测试使用匿名管道在亲缘进程间通信
 * 运行结果: 
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define MESSAGE "hello world!\n"

int main()
{
	int fds[2];
	int res = pipe(fds);
	if (res == -1) {
		perror("create pipe unsuccessful");
		exit(1);
	}	
	int pid = fork();	
	if (pid == -1) {
		perror("fork error");
		exit(1);
	}
	if (pid == 0) {
		// 关闭读端
		// close(fds[0]);
		write(fds[1], MESSAGE, sizeof(MESSAGE));
		if (res == -1) {
			perror("wirte error");
		}
	}
	if (pid > 0) {
		// 关闭写端
		char buf[128];
		// close(fds[1]);
		res = read(fds[0], buf, sizeof(buf));
		if (res == -1) {
			perror("read error");
		} else {
			write(STDOUT_FILENO, buf, res);
		}
		
	}
	return 0;
}

