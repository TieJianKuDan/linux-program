#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
	struct stat buf;
	char path[] = "file/test01.txt";
	int flag = stat(path, &buf);
	if (flag) {
		perror("获取文件信息失败");
	}
	long mode = 0;
	printf("文件大小：%ld\n", buf.st_size);
	printf("文件类型：");
	mode = buf.st_mode & S_IFMT;
	switch(mode) {

		case S_IFSOCK:
			printf("socket\n");
			break;
		case S_IFLNK:
			printf("symbolic link\n");
			break;
		case S_IFREG:
			printf("普通文件\n");
			break;
		case S_IFBLK:
			printf("块文件\n");
			break;
		case S_IFDIR:
			printf("目录\n");
			break;
		case S_IFCHR:
			printf("符号设备\n");
			break;
		case S_IFIFO:
			printf("管道\n");
			break;
	}
	return 0;	
}

