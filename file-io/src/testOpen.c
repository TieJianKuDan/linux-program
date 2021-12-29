#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main()
{
	char path[] = "file/test01.txt";
	int fd = open(path, O_RDONLY | O_CREAT, 0664);
	if (fd == -1) {
		perror("open fail");
	} else {
		printf("fd = %d\n", fd);
	} 	
	int flag = close(fd);
	if (flag != -1) {
		printf("close fail: %s", strerror(errno));
	}
	return 0;
}

