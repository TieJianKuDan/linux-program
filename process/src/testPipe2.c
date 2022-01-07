/**
 * 程序功能: 实现 ls | wc -l 父进程 ls 子进程 wc -l
 * 运行结果:
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	int pfds[2];
	int res = pipe(pfds);	
	if (res == -1) {
		perror("create pipe error");
		exit(1);
	} 
	int pid = fork();
	if (pid == -1) {
		perror("fork error");
		exit(1);
	}
	if (pid == 0) {
		res = close(pfds[1]);
		if (res == -1) {
			perror("close error");
			exit(1);
		}
		res = dup2(pfds[0], STDIN_FILENO);
		if (res == -1) {
			perror("dup error");
			exit(1);
		}
		res = execlp("wc", "wc", "-l", NULL);	
		if (res == -1) {
			perror("exec error");
			exit(1);
		}
	}
	if (pid > 0) {
		res = close(pfds[0]);
		if (res == -1) {
			perror("close error");
			exit(1);
		}
		res = dup2(pfds[1], STDOUT_FILENO);
		if (res == -1) {
			perror("dup error");
			exit(1);
		}
		res = execlp("ls", "ls", NULL);	
		if (res == -1) {
			perror("exec error");
			exit(1);
		}
	}
	return 0;
}
