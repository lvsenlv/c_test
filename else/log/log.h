/*************************************************************************
	> File Name: log.h
	> Author: 
	> Mail: 
	> Created Time: 2016年12月12日 星期一 09时56分54秒
 ************************************************************************/

#ifndef __LOG_H_
#define __LOG_H_
#include <time.h>

#define LOG_PATH_LEN			128
#define LOG_BUF_LEN				128
#define LOG_NAME_LEN			128
#define LOG_FILE_SIZE			1024		//unit of size is byte
#define LOG_CONF_PATH			"conf/log.conf"
#define LOG_CMD_LEVEL			"cat conf/log.conf | grep LOG_LEVEL"
#define LOG_CMD_PATH			"cat conf/log.conf | grep LOG_DIR"
#define LOG_CONF_CHECK 			({ \
	int ret = 0; \
	if (access(LOG_CONF_PATH, F_OK)) \
	{ \
		perror("log.conf"); \
		ret = -1; \
	} \
	ret; \
	})

#define DISP_LOG(level, format, args...) ({ \
	if (level < LOG_LEVEL_MAX) \
	{ \
		log_check(); \
		time_t ti; \
		struct tm *tm; \
		ti = time(NULL); \
		tm = localtime(&ti); \
		fprintf(g_log_file, "%4d-%02d-%02d %02d:%02d:%02d [%s] | [%s][%d] : ", \
		tm->tm_year+1900, tm->tm_mon, tm->tm_mday, tm->tm_hour, tm->tm_min, \
		tm->tm_sec, *(log_str+level), __func__, __LINE__); \
		fprintf(g_log_file, format, ##args); \
	} \
	})

enum {
	LOG_LEVEL_STOP = 0,
	LOG_LEVEL_ERROR,
	LOG_LEVEL_DEBUG,
	LOG_LEVEL_MAX,
};

extern FILE *g_log_file;
extern char *log_str[];

void log_init(void);
int get_log_level(int *level);
int get_log_path(char *path, unsigned int len);
int log_check(void);


#endif

