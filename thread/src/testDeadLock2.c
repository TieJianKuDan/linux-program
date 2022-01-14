/**
 * 程序功能: 哲学家就餐问题 
 * 运行结果: 为什么不会死锁？ 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>

pthread_mutex_t chopsticks[5];

void InitMutex() {
	for (int i = 0; i < 5; i++) {
		pthread_mutex_init(&chopsticks[i], NULL);
	}
}

void * Eat(void * arg)
{
	pthread_mutex_t ** mutexs = (pthread_mutex_t **) arg;

	while (1) {
		pthread_mutex_lock(* mutexs);
		sleep(1);
		pthread_mutex_lock(* (mutexs + 1));
		printf("[%lu]: 可以干饭了！\n", pthread_self());
		pthread_mutex_unlock(* (mutexs + 1));
		pthread_mutex_unlock(* mutexs);
		sleep(1);
	}

	return 0;
}
int main()
{
	pthread_t tid = 0;
	int erro_num = 0;

	InitMutex();

	for (int i = 0; i < 5; i++) {
		pthread_mutex_t * mutex_pair[2];
		mutex_pair[0] = &chopsticks[i % 5]; 
		mutex_pair[1] = &chopsticks[(i + 1) % 5]; 
		erro_num = pthread_create(&tid, NULL, Eat, mutex_pair);
		if (erro_num > 0) {
			printf("pthread_create error: %s\n", strerror(erro_num));
		} else {
			printf("创建线程[%lu]\n", tid);
		}	
	}

	pthread_exit(NULL);
}

