/**
 * 程序功能: 
 * 	使用信号量实现生产者只能在面包少于5时生产，消费者只能在有面包时消费 
 * 运行结果: 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include <pthread.h>

sem_t sem_c;
sem_t sem_p;
const int c_thread_num = 3;
const int p_thread_num = 2;

void PrintError(int erro_num) 
{
	if (erro_num > 0) {
		printf("%s\n", strerror(erro_num));
	}
}

void * Consume(void * arg)
{
	while (1) {
		sem_wait(&sem_c);
		sleep(1);
		printf("========|>[%lu]: 消费了一个面包，真不错\n", pthread_self());
		sem_post(&sem_p);
		sleep(1);
	}
	return NULL;
}

void * Produce(void * arg)
{
	while (1) {
		sem_wait(&sem_p);
		printf("<|---[%lu]: 生产了一个面包\n", pthread_self());
		sem_post(&sem_c);
		sleep(1);
	}
	return NULL;
}

int main()
{
	int erro_num = 0;
	int index = 0;
	pthread_t tids[c_thread_num + p_thread_num];

	erro_num = sem_init(&sem_c, 0, 0);
	PrintError(erro_num);
	erro_num = sem_init(&sem_p, 0, 5);

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

	sem_destroy(&sem_c);
	sem_destroy(&sem_p);
}

