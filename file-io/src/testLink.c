#include <stdio.h>
#include <unistd.h>

int main()
{	
	char oldPath[] = "file/old.txt";
	char newPath[] = "file/new.txt";

	if ((link(oldPath, newPath)) < 0) {
		perror("link error");
	}
	
	if ((unlink(oldPath)) < 0) {
		perror("unlink error");
	}	

	return 0;
}
