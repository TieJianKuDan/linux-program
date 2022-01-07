/**
 * 程序功能: 测试命名管道的写端
 * 运行结果:
 */

#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	char buf[128];
	int len = 0;
	int fd = open("file/dove.pip", O_RDWR);
	if (fd == -1) {
		printf("open error\n");
	}
	printf("请输入信息\n");
	while (1) {
		if ((len = read(STDIN_FILENO, buf, sizeof(buf))) > 0) {
			write(fd, buf, len);
		}	
	}
	return 0;
}

