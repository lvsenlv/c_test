/*************************************************************************
	> File Name: main.c
	> Author: 
	> Mail: 
	> Created Time: 2017年02月13日 星期一 17时55分43秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#define 	BUF_LEN 			128

#ifndef _DEBUG_0
#ifndef _DEBUG_1
#ifndef _DEBUG_2
char *str[] = {
	"_DEBUG_0 : 测试多线程同时使用一个资源时，若不加锁会产生的情况；",
	"           新建两个线程，分别对g_num进行++和--操作。",
	"_DUBUG_1 : 测试多线程进入挂起态后，当满足就绪条件后，就绪的先后顺序；",
	"           主线程启动4个线程，每个线程有一个参数i（i=生成顺序），",
	"           无论线程的启动顺序如何，执行顺序只能为，线程0、线程1、线程2、线程3。",
	NULL,
};
int main(int argc, char **agv)
{
	char **ptr = str;
	while(*ptr)
		fprintf(stderr, "%s\n", *ptr++);
	
	return 0;
}
#endif
#endif
#endif



#ifdef _DEBUG_2
void *print_log(void *arg);
void *print_std(void *arg);

int main(int argc, char **argv)
{
	pthread_t pthread_id1, pthread_id2;
	void *pthread_ret = NULL;
	int ret = 0;
	
	ret = pthread_create(&pthread_id1, NULL, print_log, NULL);
	if(ret)
	{
		fprintf(stderr, "error in pthread_create : %s\n", strerror(ret));
		exit(-1);
	}

	ret = pthread_create(&pthread_id2, NULL, print_std, NULL);
	if(ret)
	{
		fprintf(stderr, "error in pthread_create : %s\n", strerror(ret));
		exit(-1);
	}

	ret = pthread_join(pthread_id1, &pthread_ret);
	if(ret)
	{
		fprintf(stderr, "error in pthread_join: %s\n", strerror(ret));
		exit(-1);
	}

	ret = pthread_join(pthread_id2, &pthread_ret);
	if(ret)
	{
		fprintf(stderr, "error in pthread_join: %s\n", strerror(ret));
		exit(-1);
	}
	
	return 0;
}

void *print_log(void *arg)
{
	char buf[BUF_LEN] = {0};
	char tmp_buf[BUF_LEN+BUF_LEN] = {0};
	int i = 0;
	
	snprintf(buf, sizeof(buf), "%s", "mkdir -p /root/test");
	system(buf);

	snprintf(buf, sizeof(buf), "%s", "> /root/test/log");
	system(buf);

	while(++i)
	{
		snprintf(buf, sizeof(buf), "[%s][%d] : i = %d", __func__, __LINE__, i);
		snprintf(tmp_buf, sizeof(tmp_buf), "echo \"%s\" >> /root/test/log", buf);
		system(tmp_buf);
		sleep(1);
	}
	
	return NULL;
}

void *print_std(void *arg)
{
	char buf[BUF_LEN] = {0};
	int i = 0;
	
	while(++i)
	{
		snprintf(buf, sizeof(buf), "[%s][%d] : i = %d", __func__, __LINE__, i);
		system(buf);
		sleep(1);
	}
	return NULL;
}

#endif //_DEBUG_2



#ifdef _DEBUG_1
void *func(void *arg);

int g_num = 0;
pthread_mutex_t mylock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t qready = PTHREAD_COND_INITIALIZER;

int main(int argc, char **argv)
{
	int i = 0, ret = 0;
	pthread_t pthread_id[4];
	void *pthread_ret;
	
	for(i = 0; i < 4; i++)
	{
		ret = pthread_create(&pthread_id[i], NULL, func, (void *)i);
		if(ret)
		{
			fprintf(stderr, "error in pthread_create: %s\n", strerror(ret));
			exit(-1);
		}
	}
	
	for(i = 0; i < 4; i++)
	{
		ret = pthread_join(pthread_id[i], &pthread_ret);
		if(ret)
		{
			fprintf(stderr, "error in pthread_join: %s\n", strerror(ret));
			exit(-1);
		}
	}
	
	return 0;
}

void *func(void *arg)
{
	int i = (int)arg;
	int ret = 0;
	sleep(5-i);
	pthread_mutex_lock(&mylock);
	while(i != g_num)
	{
		//printf("thread %d waiting \n", i);
		//printf("g_num_in_while = %d \n", g_num);
		ret = pthread_cond_wait(&qready, &mylock);
		//printf("thread %d end wait %s \n", i, (ret ? "failed" : "success"));
	}
	printf("thread %d is runing \n", i);
	g_num++;
	printf("g_num_out_while = %d \n", g_num);
	pthread_mutex_unlock(&mylock);
	pthread_cond_broadcast(&qready);
	return NULL;
}
#endif //_DEBUG_1



#ifdef _DEBUG_0
void *func_add(void *arg);
void *func_sub(void *arg);

int g_num = 0;
pthread_mutex_t mylock = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char** argv) 
{
	pthread_t pthread_id1, pthread_id2;
	int ret = 0;
	void *pthread_ret;
	
	ret = pthread_create(&pthread_id1, NULL, func_add, NULL);
	if(ret)
	{
		fprintf(stderr, "error in pthread_create: %s\n", strerror(ret));
		exit(-1);
	}

	ret = pthread_create(&pthread_id2, NULL, func_sub, NULL);
	if(ret)
	{
		fprintf(stderr, "error in pthread_create: %s\n", strerror(ret));
		exit(-1);
	}
	
	ret = pthread_join(pthread_id1, &pthread_ret);
	if(ret)
	{
		fprintf(stderr, "error in pthread_join: %s \n", strerror(ret));
		exit(-1);
	}
	printf("thread 1 exit code %d \n", (int)pthread_ret);
	
	/*ret = pthread_join(pthread_id2, &pthread_ret);
	if(ret)
	{
		printf("error in pthread_join: %s \n", strerror(ret));
		exit(-1);
	}
	printf("thread 2 exit code %d \n", (int)pthread_ret);*/
	
	return 0;
}

void *func_add(void *arg)
{
	int i = 0;
	for(i = 0; i >= 0; i++)
	{
		pthread_mutex_lock(&mylock);
		g_num++;
		printf("g_num++ = %d \n", g_num);
		sleep(1);
		pthread_mutex_unlock(&mylock);
		sleep(1);
	}
	return NULL;
}

void *func_sub(void *arg)
{
	int i = 0;
	for(i = 0; i >=0; i++)
	{
		pthread_mutex_lock(&mylock);
		g_num--;
		printf("g_num-- = %d \n", g_num);
		sleep(1);
		pthread_mutex_unlock(&mylock);
		sleep(1);
		
	}
	return NULL;
}
#endif //_DEBUG_0

