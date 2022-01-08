/**
 * 程序功能: 使用 pthread_join 回收子线程 
 * 运行结果: 
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>

#define N 5

void * CountOff(void * arg)
{
	int res = (int) arg;
//	sleep(res);
	printf("[tid=%lu]: %d\n", pthread_self(), res);
	res += 100;

	return (void *) res;
}

int main()
{
	pthread_t tids[5];
	void * retval;
	
	for (int i = 0; i < N; i++) {
		pthread_create(tids + i, NULL, &CountOff, (void *) i);
	}
	
	for (int i = 0; i < N; i++) {
		pthread_join(tids[i], &retval);
		printf("回收线程[%lu]: return value is {%d}\n", tids[i], (int) retval);
	}

	return 0;
}

