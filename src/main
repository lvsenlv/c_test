/*************************************************************************
	> File Name: main.c
	> Author: 
	> Mail: 
	> Created Time: 2016年12月06日 星期二 10时28分29秒
 ************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "3t_test.h"
#include "log.h"

#define D2_ARRAY_LEN(array_name) (sizeof(array_name)/sizeof(**array_name))
#define D2_ARRAY_COL(array_name) (sizeof(*array_name)/sizeof(**array_name))

int main()
{
    test_time();
    int array[3][4]={
        {0,1,2,3},
        {4,15,6,17},
        {80,9,10,11}
    };
    int *ptr = &array[0][0];
    int i = 0, max_num = *ptr;

    //efficiently
    //this code could be only used to find out the max_num
    for (i = 0; i < D2_ARRAY_LEN(array); i++)
    {
        max_num = *(ptr+i) > max_num ? *(ptr+i) : max_num;
    }

    fprintf(stdout, "max_num=%d \n", max_num);
    
    //if want to get the location of max_num in array
    int location = 0;
    ptr = &array[0][0];
    max_num = *ptr;
    for (i = 0; i < D2_ARRAY_LEN(array); i++)
    {
        if (*(ptr+i) > max_num)
        {
            max_num = *(ptr+i);
            location = i;
        }
    }
    fprintf(stdout, "the max_num=%d is in %d row %d col \n", max_num, \
            location/D2_ARRAY_COL(array)+1, location%D2_ARRAY_COL(array)+1);

    
    log_init();
    LOG(LOG_LEVEL_ERROR, "test1 \n");
    LOG(LOG_LEVEL_ERROR, "test2 \n");
    LOG(LOG_LEVEL_ERROR, "test3 \n");
    
    
    return 0;
}
