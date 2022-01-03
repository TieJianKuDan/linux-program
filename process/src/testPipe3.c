/*
 * 测试同一个进程对管道进行读写 为什么说不可以???
 */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define MESSAGE "hello world!\n"

int main()
{
	int fds[2];
	int res = pipe(fds);
	char buf[128];
	if (res == -1) {
		perror("create pipe unsuccessful");
		exit(1);
	}	

	// 关闭读端
	// close(fds[0]);
	write(fds[1], MESSAGE, sizeof(MESSAGE));
	if (res == -1) {
		perror("wirte error");
		exit(-1);
	}
	// 关闭写端
	// close(fds[1]);
	res = read(fds[0], buf, sizeof(buf));
	if (res == -1) {
		perror("read error");
		exit(-1);
	} else {
		write(STDOUT_FILENO, buf, res);
	}

	return 0;
}

