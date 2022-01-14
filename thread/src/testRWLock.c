/**
 * 程序功能: 测试读写锁 
 * 运行结果: 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>

pthread_rwlock_t rwlock;
const int r_thread_num = 5;
const int w_thread_num = 3;

void PrintError(int erro_num) 
{
	if (erro_num > 0) {
		printf("%s\n", strerror(erro_num));
	}
}

void * ReadShare(void * arg)
{
	while (1) {
		pthread_rwlock_rdlock(&rwlock);
		printf("[%lu] -----> 正在读取临界区\n", pthread_self());
		sleep(2);
		pthread_rwlock_unlock(&rwlock);
		sleep(1);
	}
	return NULL;
}

void * WriteShare(void * arg)
{
	while (1) {
		pthread_rwlock_wrlock(&rwlock);
		printf("[%lu] <=== 正在写入临界区\n", pthread_self());
		sleep(2);
		pthread_rwlock_unlock(&rwlock);
		sleep(8);
	}
	return NULL;
}

int main()
{
	int erro_num = 0;
	pthread_t tid = 0;

	erro_num = pthread_rwlock_init(&rwlock, NULL);
	PrintError(erro_num);

	for (int i = 0; i < r_thread_num; i++) {
		erro_num = pthread_create(&tid, NULL, ReadShare, NULL);
		PrintError(erro_num);
		pthread_detach(tid);
	}		

	for (int i = 0; i < w_thread_num; i++) {
		erro_num = pthread_create(&tid, NULL, WriteShare, NULL);
		PrintError(erro_num);
		pthread_detach(tid);
	}		

	pthread_exit(NULL);
}

