#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main()
{
	int fd = 0, size = 0, flag = 0;
	char temp = 'a';
	char buf[32];
	char path[] = "file/test03.txt";
	fd = open(path, O_RDWR | O_CREAT, 0644);
	if (fd < 0) {
		perror("open file error");
	}
	size = lseek(fd, 0, SEEK_END);
	printf("文件大小为：%d\n", size);
	flag = read(fd, &temp, 1);
	if (flag == 0) {
		printf("读到文件末尾\n");
	}
	write(STDOUT_FILENO, &temp, 1);
	return 0;
}

