/**
 * 程序功能: 测试孤儿进程
 * 运行结果:
 */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#define LOCATION "ps"
#define OPTION "-ajx"

int main()
{
	int fd = open("file/orphan.txt", O_RDWR | O_CREAT, 0644);
	if (fd == -1) {
		perror("open fail");
	}
	int res = dup2(fd, STDOUT_FILENO);
	if (res == -1) {
		perror("dup2 fail");
	}
									
	int pid = fork();
	if (pid == 0) {
		sleep(10);
		int res = execlp(LOCATION, LOCATION, OPTION, NULL);
		if (res == -1) {
			perror("exec fail");
		}
	}
	if (pid == -1) {
		perror("创建子进程失败\n");
	}
	if (pid > 0) {
		sleep(5);
	}
}

