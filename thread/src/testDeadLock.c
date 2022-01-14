/**
 * 程序功能: 线程尝试对一个互斥量加锁两次 
 * 运行结果: 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>

pthread_mutex_t mutex;

void * DeadLock(void * arg)
{
	pthread_mutex_lock(&mutex);
	pthread_mutex_lock(&mutex);
	printf("正常来说我不会出现\n");
	pthread_mutex_unlock(&mutex);
	pthread_mutex_unlock(&mutex);
	
	return 0;
}
int main()
{
	pthread_t tid = 0;
	int erro_num = 0;

	pthread_mutex_init(&mutex, NULL);
	erro_num = pthread_create(&tid, NULL, DeadLock, NULL);
	if (erro_num > 0) {
		printf("pthread_create error: %s\n", strerror(erro_num));
	}	
	
	pthread_exit(NULL);
}

