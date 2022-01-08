/**
 * 程序功能: 测试写入内容超出映射区大小和偏移量大于文件大小 
 * 运行结果: 
 * 	偏移量不能大于文件大小,否则总线错误
 * 	映射区大小和文件大小没有关系		
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h> 

int main()
{
	int fd = -1;
	int res = 0;
	char * fp = NULL;		
	int pid = 0;

	fd = open("file/helper.mmap", O_RDWR | O_CREAT | O_TRUNC, 0664);
	if (fd == -1) {
		perror("open error");
		exit(-1);
	}
	res = ftruncate(fd, 16);	
	if (res == -1) {
		perror("ftruncate error");
		exit(-1);
	}
	fp = mmap(NULL, 20, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	if (fp == MAP_FAILED) {
		perror("mmap error");
		exit(-1);
	}
	pid = fork();
	if (pid == 0) {
		strcpy(fp, "This child! Hello everybody!\n");
	}else {
		wait(NULL);
		printf("%s", fp);	
		res = munmap(fp, 20);
		if (res == -1) {
			perror("munmap error");
		}
	}	
	return 0;
}

