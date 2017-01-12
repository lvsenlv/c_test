/*************************************************************************
	> File Name: convert_system.h
	> Author: 
	> Mail: 
	> Created Time: 2017年01月12日 星期四 09时41分42秒
 ************************************************************************/

#ifndef _CONVERT_SYSTEM_H
#define _CONVERT_SYSTEM_H



typedef struct link_list {
	long int elem;
	char *res;//end of this string is not '/0', so ban using strlen
	unsigned int res_size;
	unsigned int res_cur_size;//record current size of res
	struct link_list *next;
} link_list_t;

void print_info(int opts);
int init_node(link_list_t *pnode, long int param);
void print_link_list(link_list_t *pnode);
void release_link_list(link_list_t *pnode);
int convert_system(link_list_t *pnode);
int strrev(link_list_t *pnode);

#endif

