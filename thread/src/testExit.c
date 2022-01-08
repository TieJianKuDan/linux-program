/**
 * 程序功能: 测试 exit 和 pthread_exit  
 * 运行结果: 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>

void * OnCount(void * arg)
{
	int count = (int) arg;
	sleep(count);
	printf("我是第%d个线程\n", count);
	if (count == 3) {
//`		exit(0);
		pthread_exit(NULL);
		
	} else {
		return NULL;
	}
}

int main()
{
	pthread_t tid = 0;

	for (int i = 1; i < 10; i++) {
		pthread_create(&tid, NULL, OnCount, (void *) i);
	}
	
//	pause();
	sleep(5);	
//	return 0;
	pthread_exit(NULL);
}

