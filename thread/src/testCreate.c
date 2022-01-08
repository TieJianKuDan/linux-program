/**
 * 程序功能: 创建多个线程 
 * 运行结果: 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>

#define N 10

void * countOff(void * arg)
{
	sleep((int)arg);
	printf("[tid=%lu]: %d\n", pthread_self(), (int)arg);
	return NULL;
}

int main()
{
	pthread_t tid;
	
	for (int i = 0; i < N; i++) {
		pthread_create(&tid, NULL, &countOff, (void *) i);
	}	
//	getchar();
	pause();
	return 0;
}
