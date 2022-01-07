/**
 * 程序功能: 测试子进程使用execvp执行其他程序
 * 运行结果:
 */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#define LOCATION "ps"

int main(int args, char * argv[])
{
	int fd = open("file/test1.txt", O_RDWR | O_CREAT, 0644);
	if (fd == -1) {
		perror("open fail");
	}
	int res = dup2(fd, STDOUT_FILENO);
	if (res == -1) {
		perror("dup2 fail");
	}

	int pid = fork();
	if (pid == 0) {
		printf("[child] pid = %d\n", getpid());
		argv[0] = LOCATION;
		execvp(LOCATION, argv);
		// execlp(LOCATION, LOCATION, "-aux", NULL);
	}
	if (pid == -1) {
		perror("创建子进程失败\n");
	}
	if (pid > 0) {
		sleep(1);
	}
}

