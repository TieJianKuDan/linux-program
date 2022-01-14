/**
 * 程序功能: 测试死锁 
 * 运行结果: 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>

pthread_mutex_t chopsticks_1;
pthread_mutex_t chopsticks_2;

void InitMutex() {
	pthread_mutex_init(&chopsticks_1, NULL);
	pthread_mutex_init(&chopsticks_2, NULL);
}

void * Eat1(void * arg)
{
	char * name = (char *) arg;
	while (1) {
		pthread_mutex_lock(&chopsticks_1);
		sleep(1);
		pthread_mutex_lock(&chopsticks_2);
		printf("===>[%s]: 可以干饭了！\n", name);
		sleep(1);
		pthread_mutex_unlock(&chopsticks_2);
		pthread_mutex_unlock(&chopsticks_1);
		sleep(1);
	}

	return 0;
}

void * Eat2(void * arg)
{
	char * name = (char *) arg;
	while (1) {
		pthread_mutex_lock(&chopsticks_2);
		sleep(1);
		pthread_mutex_lock(&chopsticks_1);
		printf("<---[%s]: 可以干饭了！\n", name);
		pthread_mutex_unlock(&chopsticks_1);
		pthread_mutex_unlock(&chopsticks_2);
		sleep(1);
	}

	return 0;
}
int main()
{
	pthread_t tid = 0;
	int erro_num = 0;

	InitMutex();

	erro_num = pthread_create(&tid, NULL, Eat1, "小明");
	erro_num = pthread_create(&tid, NULL, Eat2, "小红");

	pthread_exit(NULL);
}
