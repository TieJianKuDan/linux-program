/**
 * 程序功能: 测试条件变量——消费者生产者模型 
 * 运行结果: 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
const int c_thread_num = 5;
const int p_thread_num = 6;
int bread_num = 0;

void * Consume(void * arg)
{
	while (1) {
		pthread_mutex_lock(&mutex);
		while (bread_num <= 0) {
			pthread_cond_wait(&cond, &mutex);
		}
		bread_num--;
		printf("======|> [%lu]:消费了一个面包，还有[%d]个\n",
		      pthread_self(), bread_num);
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
	
}

void * Produce(void * arg)
{
	while (1) {
		pthread_mutex_lock(&mutex);
		bread_num++;
		printf("<|--- [%lu]:生产了一个面包，还有[%d]个\n",
		      pthread_self(), bread_num);
		pthread_mutex_unlock(&mutex);
		pthread_cond_broadcast(&cond);
		sleep(1);	
	}

}

void PrintError(int erro_num) 
{
	if (erro_num > 0) {
		printf("%s\n", strerror(erro_num));
	}
}

int main()
{
	int erro_num = 0;	
	pthread_t tids[p_thread_num + c_thread_num];
	int index = 0;

	pthread_mutex_init(&mutex, NULL);
	pthread_cond_init(&cond, NULL);

	for (; index < c_thread_num; index++) {
		erro_num = pthread_create(&tids[index], NULL, Consume, NULL);	
		PrintError(erro_num);
	}
			
	for (; index < p_thread_num + c_thread_num; index++) {
		erro_num = pthread_create(&tids[index], NULL, Produce, NULL);	
		PrintError(erro_num);
	}	
	
	for (int i = 0; i < index; i++) {
		pthread_join(tids[i], NULL);
	}
	
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);

	return 0;
}

