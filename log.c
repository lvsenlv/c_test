/*************************************************************************
	> File Name: log.c
	> Author: 
	> Mail: 
	> Created Time: 2016年12月12日 星期一 09时56分43秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include "log.h"

static char g_log_name[LOG_NAME_LEN] = {0};
FILE *g_log_file = NULL;
char *log_str[] = {
	"ERROR",
	"DEBUG",
	};
static inline void log_close(void);
static void before_main(void) __attribute__((constructor));

void log_init(void)
{
	int log_level = 0;
	char log_path[LOG_PATH_LEN] = {0};
	if (get_log_level(&log_level) < 0 || log_level <= 0)
	{
		//fprintf(stderr, "[%s][%d]: failed to init log \n", __func__, __LINE__);
		g_log_file = stderr;
	}
	else if (LOG_LEVEL_STOP != log_level)
	{
		if (get_log_path(log_path, LOG_PATH_LEN))
		{
			fprintf(stderr, "[%s][%d]: failed to init log \n", __func__, __LINE__);		
		}
		
		if (NULL != g_log_file)
		{
			log_close();
		}
	
		snprintf(g_log_name, sizeof(g_log_name), "%s/test.log", log_path);
		g_log_file = fopen(g_log_name, "a+");
		if ( !g_log_file )
		{
			perror("fopen g_log_file");
			g_log_file = stderr;
		}
	
		if (setvbuf(g_log_file, NULL, _IONBF, 0))
		{
			LOG(LOG_LEVEL_ERROR, "setvbuf error \n");
		}
	}
	
}

int get_log_level(int *level)
{
	if (LOG_CONF_CHECK)
	{
		return -1;
	}

	//FILE *fp = popen("cat /root/test/conf/log.conf | grep LOG_LEVEL", "r");
	FILE *fp = popen(LOG_CMD_LEVEL, "r");
	if ( !fp )
	{
		perror("popen log.conf->LOG_LEVEL");
		pclose(fp);
		return -1;
	}

	int ret = -1;
	char buf[LOG_BUF_LEN] = {0};
	char temp[LOG_BUF_LEN] = {0};
	if ( !feof(fp) && fgets(buf, sizeof(buf), fp))
	{
		if ( 1 != sscanf(buf, "%*[^=]=%[^ \t\r\n]", temp))
		{
			fprintf(stderr, "[%s][%d]: faild to sscanf \n", __func__, __LINE__);
			ret = -1;
		}
		else
		{
			*level = atoi(temp);
			ret = 0;
		}
	}
	else
	{
		fprintf(stderr, "[%s][%d]: failed to get path \n", __func__, __LINE__);
		ret = -1;
	}

	pclose(fp);
	return ret;
}

int get_log_path(char *path, unsigned int len)
{
	if (LOG_CONF_CHECK)
	{
		return -1;
	}

	//FILE *fp = popen("cat /root/test/conf/log.conf | grep LOG_DIR", "r");
	FILE *fp = popen(LOG_CMD_PATH, "r");
	if ( !fp )
	{
		perror("popen log.conf->LOG_DIR");
		pclose(fp);
		return -1;
	}

	int ret = -1;
	char buf[LOG_BUF_LEN+1] = {0};
	char temp[LOG_BUF_LEN] = {0};
	if ( !feof(fp) && fgets(buf, sizeof(buf), fp))
	{
		if ( 1 != sscanf(buf, "%*[^=]=%[^ \t\r\n]", temp))
		{
			fprintf(stderr, "[%s][%d]: faild to sscanf \n", __func__, __LINE__); 
			//should not use perror here. Failed to get messages may print "success"
			ret = -1;
		}
		else
		{
			snprintf(path, len, "%s", temp);
			ret = 0;
		}
	}
	else
	{
		fprintf(stderr, "[%s][%d]: failed to get path \n", __func__, __LINE__);
		ret = -1;
	}

	pclose(fp);
	return ret;
}

static inline void log_close(void)
{
	if (stderr != g_log_file)
		fclose(g_log_file);
}

int log_check(void)
{
	if (access(g_log_name, F_OK))
	{
		return -1;
	}
	
	struct stat st;
	if (stat(g_log_name, &st))
	{
		return -1;
	}

	if (st.st_size >= LOG_FILE_SIZE)
	{
		char cmd[LOG_BUF_LEN] = {0};
		snprintf(cmd, sizeof(cmd), ">%s", g_log_name);
		return system(cmd);
	}
	return 0;
}

static void before_main(void)
{
    fprintf(stderr, "before_main \n");
}

