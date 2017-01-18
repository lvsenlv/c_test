/*************************************************************************
	> File Name: convert_system.h
	> Author: 
	> Mail: 
	> Created Time: 2017年01月12日 星期四 09时41分42秒
 ************************************************************************/

#ifndef __CONVERT_SYSTEM_H__
#define __CONVERT_SYSTEM_H__

#define BUF_SIZE 			10
#define ARGC_OFFSET 		3
#ifdef __DEBUG__
#define DISP_INFO(opts) 	{printf("[%s][%d]:%s\n", __func__, __LINE__, *(g_info + opts));}
#else
#define DISP_INFO(opts) 	{printf("%s\n", *(g_info + opts));}
#endif //__DEBUG__

typedef long long int 		ELEM_TYPE;

char *g_info[] = { 
	"\n\t Function: the conversion of random number system\n",
	"Usage: convert_system -i -o number1 number2 ...",
	"-i : input type",
	"-o : output type",
	"2<= input type <=36",
	"2<= output type <=36",
	"malloc failed",
	"realloc failed",
	"invalid input",
	"failed to convert",
};
char g_symbol_table[] = {
	'0','1','2','3','4','5','6','7','8','9',
	'A','B','C','D','E','F','G','H','I','J','K','L','M',
	'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
};
int g_num_table[] = {
    0,1,2,3,4,5,6,7,8,9,
    10,11,12,13,14,15,16,17,18,19,
    20,21,22,23,24,25,26,27,28,29,
    30,31,32,33,34,35,
};

typedef struct link_list {
	ELEM_TYPE elem;
	char *res; 						//end of this string is not '/0', so ban using strlen
	unsigned int res_size;
	unsigned int res_cur_size; 		//record current size of res
	short int flag_avalid; 			//the data is avalid or not
	struct link_list *next;
} link_list_t;

enum {
	INFO_FUNC = 0,
	INFO_USAGE,
	INFO_INPUT,
	INFO_OUTPUT,
	INFO_INPUT_RANGE,
	INFO_OUTPUT_RANGE,
	INFO_MALLOC,
	INFO_REALLOC,
	INFO_PARAM_ERROR,
	INFO_CONVERT,
};

enum {
	FLAG_INVALID = 0, 	//invalid data
	FLAG_OUT_10, 		//output_type == 10
	FLAG_IN_OUT, 		//input_type == output_type
	FLAG_ELSE, 			//other situation
};

ELEM_TYPE strtol_rewrite(const char *nptr, short int *flag_strtol, int base);
int link_node_init(link_list_t *pnode, ELEM_TYPE param);
void link_list_print(link_list_t *pnode, int argc, char **argv);
void link_list_release(link_list_t *pnode);
int num_sys_convert(link_list_t *pnode);
int link_value_reverse(link_list_t *pnode);

#endif //__CONVERT_SYSTEM_H__

