/**
 * 程序功能: 使用 fcntl 将终端输入变成非阻塞
 * 运行结果:
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

#define INFO "no data\n"

int main()
{
	int flag = 0;
	char buf[32];
	flag = fcntl(STDIN_FILENO, F_GETFL);
	if (flag < 0) {
		perror("fcntl get error");
	}
	flag |= O_NONBLOCK;
	flag = fcntl(STDIN_FILENO, F_SETFL, flag);
	if (flag < 0) {
		perror("fcntl set error");
	}
	while(1) {
		flag = read(STDIN_FILENO, buf, sizeof(buf));
		if (flag < 0) {
			if (errno == EAGAIN) {
				write(STDIN_FILENO, INFO, sizeof(INFO));
				sleep(3);
			} else {
				perror("read error");
				exit(1);
			}
		} else {
			write(STDIN_FILENO, buf, flag);
		}		
	}	
	return 0;
}
