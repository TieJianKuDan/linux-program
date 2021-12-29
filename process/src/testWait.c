#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	int status = 0;
	int pid = 0;
	int index = 0;	

	for (;index < 2; index++) {
		pid = fork();
		if (pid == -1) perror("fork fail");
		if (pid == 0) break;
	}

	if (pid > 0) {
		pid = wait(&status);
		if (pid == -1) {
			perror("child clean fail\n");
		}
		if (pid > 0) {
			printf("child[%d] clean successfully\n", pid);
		}
		if (WIFEXITED(status)) {
			printf("exit value = %d\n", WEXITSTATUS(status));
		}
		if (WIFSIGNALED(status)) {
			printf("terminating signal = %d\n", WTERMSIG(status));
		}
	}

	if (index == 0) {
		sleep(10);
		exit(100);
	}

	if (index == 1) {
		sleep(60);
		exit(200);
	}

	return 0;
}

