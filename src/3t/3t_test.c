/*************************************************************************
	> File Name: g_env.c
	> Author: 
	> Mail: 
	> Created Time: 2016年12月06日 星期二 13时46分24秒
 ************************************************************************/
#include <stdio.h>
//#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include "3t_test.h"

char FileName[16] = {"clone"};
char FilePath[64] = {"/root/test/clone"};

int test_memset(void)
{
	tcloud_env_t g_env;

    printf( "%d \n", sizeof(g_env) );
    memset( &g_env, 0, sizeof(g_env) );
    printf( "%d \n", sizeof(g_env) );

    g_env.path = "TPATH";
    g_env.lang = "TLANG";
    g_env.resource = "TRESOURCE";

    printf( "%d \n", sizeof(g_env) );
    printf( "%s \n", g_env.path );
    printf( "%s \n", g_env.lang );
    printf( "%s \n", g_env.resource );

	return 0;
}

int test_snprintf(void)
{
	char cmd[20] = {0};
	
	snprintf( cmd, 20, ">%s", FileName );
	printf( "%s\n%d\n", cmd, sizeof(cmd) );

	return 0;
}

void test_time(void)
{
	struct stat st;
	struct tm *tm;

	time( &st.st_mtime );
	tm=localtime( &st.st_mtime );
	printf( "%04d-%02d-%02d %02d:%02d:%02d \n", tm->tm_year+1900, tm->tm_mon+1, \
		tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec );
}

int test_file(void)
{
	char cmd[128] = {0};
	char cmd_order[] = {"cat /bin/clone > /root/test_file" };
	snprintf( cmd, sizeof(cmd), "%s", cmd_order);
	FILE *fp = popen( cmd, "r" );
	if ( !fp )
	{
		perror( "popen" );
		return -1;
	}
	pclose( fp );

    return 0;
}

int test_struct_array(void)
{
	file_info_t file[3] = {
		{.numb = 5, .fp = "test_line5", .weight = 240, .hight = 320 },
		{.numb = 6, .fp = "test_line6", .weight = 480, .hight = 720 },
	};

	int i = 0;
	for ( i = 0; i < 3; i++ )
	{
		printf( "file %d is in %s, it's size %d * %d \n", file[i].numb, \
			file[i].fp, file[i].weight, file[i].hight );
	}

    return 0;
}

