#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	int status = 0;
	int pids[2] = {0, 0};
	int index = 0;	
	int pid = 0;

	for (;index < 2; index++) {
		pids[index] = fork();
		if (pids[index] == -1) perror("fork fail");
		if (pids[index] == 0) break;
	}

	if (index == 2) {
		pid = waitpid(pids[0], &status, 0);
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
		sleep(20);
		exit(100);
	}

	if (index == 1) {
		sleep(10);
		exit(200);
	}

	return 0;
}

