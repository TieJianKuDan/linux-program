/******
 * 递归遍历目录
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int tranverse(const char * path, int length, const char * pre)
{
	struct stat buf; 
	int flag = 0;
	flag = stat(path, &buf);
	if (flag < 0) {
		perror("获取文键inode失败");
	}

	int index = length - 1;
	char name[32];
	int i = 0;
	while (path[index] != '/') {
		index--;
	}
	index++;
	while (path[index] != '\0') {
		name[i] = path[index];
		i++;
		index++;	
	}
	name[i] = '\0';
	printf("%s %s\n", pre, name);	

	if (S_ISDIR(buf.st_mode)) {
		char newPre[128] = "     ";
		DIR * dir = opendir(path);
		struct dirent * de = NULL;
		char subPath[255];
		strcat(newPre, pre);
		readdir(dir);
		readdir(dir);
		while ((de = readdir(dir)) != NULL) {
			strcpy(subPath, path);
			strcat(subPath, "/");
			strcat(subPath, de->d_name);
			tranverse(subPath, sizeof(subPath), newPre);
		}
		if (de == NULL && errno != 0) {
			perror("获取目录项失败");
		}
		closedir(dir);
	}

	return 0;
}

int main(int args, char * argv[])
{	
	int len = 0;
	while(argv[1][len] != '\0') {
		len++;
	}
	len++;
	tranverse(argv[1], len, "|---");	
	return 0;
}
