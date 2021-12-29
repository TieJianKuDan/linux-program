#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main()
{
	char path[] = "file/test02.txt";
	int len = 0;
	int fd = open(path, O_WRONLY | O_CREAT, 0664);
	if (fd == -1) {
		perror("open fail");
	} else {
		printf("fd = %d\n", fd);
	} 	
	if ((len = write(fd, "hello world!", sizeof("hello world!") - 1)) > 0) {
		write(STDOUT_FILENO, "write successfully!\n", sizeof("write successfully!"));
	}
	if (len < 0) {
		perror("read fail\n");
	}
	int flag = close(fd);
	if (flag == -1) {
		printf("close ifail: %s\n", strerror(errno));
	}
	return 0;
}

