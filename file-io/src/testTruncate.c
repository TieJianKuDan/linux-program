/**
 * 程序功能: 使用 ftruncate 来拓宽文件
 * 运行结果:
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main()
{
	int size = 0, flag = 0;
	char path[] = "file/test04.txt";
	int fd = open(path, O_RDWR | O_CREAT, 0664);
	if (fd == -1) {
		perror("open fail");
	} 	
	flag = ftruncate(fd, 100);
	if (flag < 0) {
		perror("truncate fail");
	}
	size = lseek(fd, 0, SEEK_END);
	printf("拓展后文件的大小：%d\n", size);
	flag = close(fd);
	if (flag != -1) {
		printf("close fail: %s", strerror(errno));
	}
	return 0;
}

