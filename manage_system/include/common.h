/*************************************************************************
	> File Name: common.h
	> Author: lvsenlv
	> Mail: lvsen46000@163.com
	> Created Time: 2017年03月06日 星期一 13时42分52秒
 ************************************************************************/

#ifndef __COMMON_H
#define __COMMON_H

#include <stdio.h>
#include <stdlib.h>

/******************************modifiable*******************************/
//#include <stdint.h>

//typedef     char                            int8_t;
typedef     short                           int16_t;
typedef     int                             int32_t;
//typedef     long long                       int64_t;
typedef     unsigned char                   uint8_t;
typedef     unsigned short                  uint16_t;
typedef     unsigned int                    uint32_t;
//typedef     unsigned long long              uint64_t;

//#undef      NULL
//#define     NULL                            ((void *)0)
/************************************************************************/

#define     __I                             volatile const
#define     __O                             volatile
#define     __IO                            volatile

#define     ERR_MALLOC                      "error in malloc"
#define     ERR_FATAL                       "fatal error"

typedef enum {
    STAT_OK = 0,
    STAT_ERR,
}G_STATUS;

#ifdef __OS
    #ifdef __REDIRECTION
        extern FILE *g_disp_file;
        #define     DISP(format, args...) \
                    fprintf(g_disp_file, format, ##args)
        #define     DISP_ERR(str) \
                    fprintf(g_disp_file, "[%s][%d]: %s \n", __func__, __LINE__, str)
        #define     DISP_ERR_PLUS(format, args...) \
                    fprintf(g_disp_file, format, ##args)
    #else //REDIRECTION
        #define     DISP(format, args...) \
                    fprintf(stdout, format, ##args)
        #define     DISP_ERR(str) \
                    fprintf(stderr, "[%s][%d]: %s \n", __func__, __LINE__, str)
        #define     DISP_ERR_PLUS(format, args...) \
                    fprintf(stderr, format, ##args)
    #endif //__REDIRECTION
#else //__OS
    #define     DISP(format, args...)           ((void)0)
    #define     DISP_ERR(str)                   ((void)0)
    #define     DISP_ERR_PLUS(format, args...)  ((void)0)
#endif //__OS

#ifdef __LINUX
    #include <sys/time.h>
    extern struct timeval g_start_time, g_stop_time;
    #define     START_COUNT                     gettimeofday(&g_start_time, NULL)
    #define     STOP_COUNT                      gettimeofday(&g_stop_time, NULL)
    #ifdef __REDIRECTION
        #define     GET_TIME \
                    fprintf(g_disp_file, "projec cost about %ldus in total\n", \
                    (g_stop_time.tv_sec - g_start_time.tv_sec) * 1000000 + \
                     g_stop_time.tv_usec - g_start_time.tv_usec)
    #else //REDIRECTION
        #define     GET_TIME \
                    fprintf(stdout, "projec cost about %ldus in total\n", \
                    (g_stop_time.tv_sec - g_start_time.tv_sec) * 1000000 + \
                     g_stop_time.tv_usec - g_start_time.tv_usec)
    #endif //__REDIRECTION
#endif //__LINUX

#endif
