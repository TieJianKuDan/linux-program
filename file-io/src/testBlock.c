/**
 * 程序功能: 测试非阻塞模式读写终端
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
	int flag = 0;
	char buf[32];
	int fd = open("/dev/pts/0", O_RDWR | O_NONBLOCK);
	if (fd < 0) {
		perror("打卡文件失败！");
	}
	while(1) {
		flag = read(fd, buf, sizeof(buf));
		flag = write(fd, buf, flag);
		/*
		if (flag < 0 ) {
			perror("写入失败！");
		}
		*/
	} 
	/*
	if (flag < 0 ) {
		perror("读取失败！");
	}
	*/
	return 0;	
}
