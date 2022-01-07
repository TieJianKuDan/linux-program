/**
 * 程序功能: 测试文件读写指针是否为同一个
 * 运行结果: 是，读会影响写
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
	int fd = 0, size = 0, flag = 0;
	char temp = 'a';
	char buf[32];
	char path[] = "file/test04.txt";
	fd = open(path, O_RDWR | O_CREAT, 0644);
	if (fd < 0) {
		perror("open file error");
	}
	flag = read(fd, buf, sizeof(buf));
	if (flag < 0) {
		perror("read error");
	}
	write(STDOUT_FILENO, buf, flag);
	flag = write(fd, "append", 6);
	if (flag < 0) {
		perror("write error");
	}
	return 0;
}

