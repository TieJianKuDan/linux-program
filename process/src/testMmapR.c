/**
 * 程序功能: 测试 mmap 开辟有名文件映射(读)
 * 运行结果:
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	int fd = open("file/helper.mmap", O_RDWR | O_CREAT, 0664);
	if (fd == -1) {
		printf("open error\n");
		exit(-1);
	}
	int res = ftruncate(fd, 512);
	if (res == -1) {
		perror("truncate error");
		exit(-1);
	}
	/*
	res = unlink("file/helper.mmap");
	if (res == -1) {
		perror("unlink error");
	}
	*/
	char * fp = (char *) mmap(NULL, 512, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (fp == MAP_FAILED) {
		perror("mmap error");
		exit(-1);
	}
	while (1) {
		// 有信息来了
		printf(fp);
		sleep(1);
	}
	return 0;	
}

