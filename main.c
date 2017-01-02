/*************************************************************************
	> File Name: main.c
	> Author: 
	> Mail: 
	> Created Time: 2016年12月06日 星期二 10时28分29秒
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "3tcloud_test.h"
#include "log.h"

int main()
{
	test_time();
	log_init();
	LOG(LOG_LEVEL_ERROR, "test1 \n");
	LOG(LOG_LEVEL_ERROR, "test2 \n");
	LOG(LOG_LEVEL_ERROR, "test3 \n");
	
	return 0;
}
