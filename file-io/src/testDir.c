/**
 * 程序功能: 测试关于目录的一些操作
 * 运行结果:
 */

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>

int main()
{
	char buf[32];	

	char * flag = getcwd(buf, sizeof(buf));
	if (flag == NULL) {
		perror("getcwd error");
	}
	printf("当前工作目录为: %s\n", buf);

	DIR * dir = opendir("file");
	if (dir == NULL) {
		perror("open directory error");
	}

	while(1) {
		struct dirent * de = readdir(dir);	

		if (de == NULL && errno != 0) {
			perror("read directory error");	
			exit(1);
		}

		if (de == NULL && errno == 0) {
			printf("read end\n");
			break;
		}

		printf("=================\n");
		printf("inode number: %ld\n", de->d_ino);
		printf("name: %s\n", de->d_name);
	}

	closedir(dir);

	int res = chdir("/home/leo");
	if (res < 0) {
		perror("chdir error");
	}
	flag = getcwd(buf, sizeof(buf));
	if (flag == NULL) {
		perror("getcwd error");
	}
	printf("改变工作目录后：%s\n", buf);

	return 0;
}

