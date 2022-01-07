/**
 * 程序功能: 测试 dup、dup2 和 fcntl实现dup
 * 运行结果:
 */

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

/**
 * 测试 dup()
 */
void testDup()
{
	char info[] = "STDOUT_FILENO 复制成功\n";
	int fd = dup(STDOUT_FILENO);
	if (fd == -1) {
		perror("dup error");
	}
	// 向 fd 写入数据
	write(fd ,info, sizeof(info));
}

void testDup2()
{
	int fd = open("file/test05.txt", O_RDWR | O_CREAT, 0664);	
	if (fd == -1) {
		perror("open error");
	}
	int res = dup2(fd, STDOUT_FILENO);
	if (res == -1) {
		perror("dup2 error");
	}
	printf("hello world!\n");
}

void testFcntl()
{
	int fd = fcntl(STDOUT_FILENO, F_DUPFD, 0);
	char info[] = "STDOUT_FILENO 复制成功\n";
	if (fd == -1) {
		perror("dup error");
	}
	// 向 fd 写入数据
	write(fd ,info, sizeof(info));
}

int main()
{
	// testDup();	
	// testDup2();	
	testFcntl();
	return 0;
}

