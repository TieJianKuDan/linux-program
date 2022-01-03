/**
 * 测试执行 java class 文件
 */

#include <stdio.h>
#include <unistd.h>

#define TARGET "SayHello"

int main()
{
	int pid = fork();
	if (pid == 0) {
		printf("[child] pid = %d\n", getpid());
		execlp("java", "java", "-classpath", "./out/", 
				TARGET, NULL);
	}
	if (pid == -1) {
		perror("创建子进程失败\n");
	}
	if (pid > 0) {
		sleep(1);
	}
		
	return 0;
}

