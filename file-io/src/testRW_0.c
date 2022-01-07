/**
 * 程序功能: 测试文件中有空洞能全部读出来吗
 * 运行结果: 因为文件末尾是通过判断文件指针所处位置是否超出文件大小来判断的，并不是\0
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	int fd = 0;
	int len = 0;
	char buf[16];

	fd = open("file/test06.txt", O_RDWR | O_CREAT | O_TRUNC, 0664);
	if (fd == -1) {
		printf("open error\n");
	}	
	write(fd, "hello world!", 12);
	lseek(fd, 10, SEEK_END);
	write(fd, "end", 3);
	lseek(fd, 0, SEEK_SET);
	while ((len = read(fd, buf, sizeof(buf))) > 0) {
		write(STDOUT_FILENO, buf, len);
	}
	return 0;
}

