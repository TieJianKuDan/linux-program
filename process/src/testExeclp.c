#include <stdio.h>
#include <unistd.h>

int main()
{
	int pid = fork();
	if (pid == 0) {
		printf("[child] pid = %d\n", getpid());
		// execlp("ls", "ls","-lah", NULL);
		execlp("list", "list","./", NULL);
	}
	if (pid == -1) {
		perror("创建子进程失败\n");
	}
	if (pid > 0) {
		sleep(1);
	}	
}

