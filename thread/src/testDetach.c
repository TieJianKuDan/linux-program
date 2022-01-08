/**
 * 程序功能: 测试 pthread_detach 后还能回收到结束状态吗 
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
	sleep(res);
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
		pthread_detach(tids[i]);
	}

	// 子线程设置了detach就不能用pthread_wait获取结束状态	
	sleep(10);

	for (int i = 0; i < N; i++) {
		pthread_join(tids[i], &retval);
		printf("回收线程[%lu]: return value is {%d}\n", tids[i], (int) retval);
	}
	
	return 0;
}

