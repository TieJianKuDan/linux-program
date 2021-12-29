#include <stdio.h>
#include <unistd.h>

#define LOCATION "out/sayHello"

int main()
{
	int pid = fork();
	if (pid == 0) {
		printf("[child] pid = %d\n", getpid());
		execl(LOCATION, LOCATION, NULL);
	}
	if (pid == -1) {
		perror("创建子进程失败\n");
	}
	if (pid > 0) {
		sleep(1);
	}
		
	return 0;
}

