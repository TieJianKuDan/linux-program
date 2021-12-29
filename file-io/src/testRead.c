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
	char buf[32];
	int len = 0;
	int fd = open(path, O_RDONLY | O_CREAT, 0664);
	if (fd == -1) {
		perror("open fail");
	} else {
		printf("fd = %d\n", fd);
	} 	
	while((len = read(fd, buf, 32)) > 0) {
		buf[len] = '\0';
		fprintf(stdout, "%s", buf);
	}
	if (len < 0) {
		perror("read fail\n");
	} else if (len == 0) {
		printf("\nread end!\n");
	}
	int flag = close(fd);
	if (flag == -1) {
		printf("close fail: %s\n", strerror(errno));
	}
	return 0;
}

