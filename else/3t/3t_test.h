/*************************************************************************
	> File Name: env.h
	> Author: 
	> Mail: 
	> Created Time: 2016年12月06日 星期二 13时48分49秒
 ************************************************************************/

#ifndef __3TCLOUD_TEST__
#define __3TCLOUD_TEST__

extern char FilePath[64];

#define GET_FILE(f) ({\
	int res = -1; \
	char buf[32] = {0}; \
	snprintf( buf, sizeof(buf), "%s", FilePath ); \
	if ( ! access( buf, F_OK ) ) \
	{ res = 0; } \
	res;})

typedef struct {
    const char *path;
    const char *lang;
    const char *resource; 
} tcloud_env_t;

typedef struct {
	unsigned int numb;
	const char * fp;
	unsigned int weight;
	unsigned int hight;
} file_info_t;

int test_memset(void);
int test_snprintf(void);
void test_time(void);
int test_file(void);
int test_struct_array(void);

#endif

