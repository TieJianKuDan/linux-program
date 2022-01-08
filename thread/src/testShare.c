/**
 * 程序功能: 测试全局区变量在线程间共享 
 * 运行结果: 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>

int g_val = 100;

void * OnThread(void * arg)
{
	g_val += 100;
	return NULL;
}

int main()
{
	printf("全局变量 g_val = %d\n", g_val);
	pthread_t tid = 0;
	pthread_create(&tid, NULL, OnThread, NULL);
	sleep(1);	
	printf("全局变量 g_val = %d\n", g_val);
	return 0;
}

