/**
 * 程序功能: 测试使用文件进行进程间通信(读)
 * 运行结果:
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
	int fd = open("file/dove2.pip", O_RDWR | O_CREAT, 0664);
	char buf[128];
	int len = 0;
	int res = 0;

	if (fd == -1) {
		printf("open error\n");
		exit(-1);
	}
	while (1) {
		if ((len = read(fd, buf, sizeof(buf))) > 0) {
			res = write(STDOUT_FILENO, buf, len);
			if (res == -1) {
				perror("write error");
			}	
		}
		else if (len == -1) {
			perror("read error");
		}
		else {
			sleep(1);
		}
	}
}

