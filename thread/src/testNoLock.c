/**
 * 程序功能: 测试没有加锁下多线程操作临界区 
 * 运行结果: 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>

int ticket = 50;
const int thread_num = 5;

void * SellTicket(void * arg)
{
	while (ticket > 0) { 
		printf("===>[tid=%lu]正在出票, 请稍后...\n", pthread_self());
		sleep(1);
		ticket--;
		printf("<===[tid=%lu]出票成功，还剩[%d]张票\n",pthread_self(), ticket);
	}
	return NULL;
}

int main()
{
	pthread_t tid = 0;
	int erro_num = 0;

	for (int i = 0; i < thread_num; i++) {
		erro_num = pthread_create(&tid, NULL, SellTicket, NULL);
		if (erro_num > 0) {
			printf("%s\n", strerror(erro_num));
		}
		erro_num = pthread_detach(tid);
		if (erro_num > 0) {
			printf("%s\n", strerror(erro_num));
		}
	}
	
	pthread_exit(NULL);	
}

