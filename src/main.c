/*************************************************************************
	> File Name: main.c
	> Author: 
	> Mail: 
	> Created Time: 2017年01月12日 星期四 09时38分45秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "convert_system.h"

#define BUF_SIZE 10

char *g_info[] = { 
	"Usage: convert_system [input type] [output type] number1 number2",
	"malloc failed",
	"2<= input type <=36",
	"2<= output type <=36",
	"failed to convert",
};
char symbol_table[36] = {
	'0','1','2','3','4','5','6','7','8','9',
	'A','B','C','D','E','F','G','H','I','J','K','L','M',
	'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
};

int main(void)
{
	int argc = 6;
	char *argv[6] = {
		"test",
		"10",
		"2",
		"-158",
		"777",
		"177"
	};
	if(argc < 4)
	{
		print_info(1);
		return -1;
	}

	unsigned int input_type = 0, output_type = 0;
	long int input = 0;
	input_type = strtol(*(argv+1), NULL, 10);
	output_type = strtol(*(argv+2), NULL, 10);
	if( input_type <2 || input_type > 36 || output_type <2 || output_type > 36)
	{
		print_info(3);
		print_info(4);
		return -1;
	}
	
	int arg_nums = 3;//ignore 3 params: file_name, input_type, output_type
	int i = 0;
	link_list_t head_node, *link_node = NULL, *new_link_node = NULL;
	head_node.elem = output_type;
	head_node.res = NULL;
	head_node.res_size = 0;
	head_node.res_cur_size = 0;
	head_node.next = NULL;
	link_node = &head_node;
	for(i = arg_nums; i < argc; i++)
	{
		new_link_node = (link_list_t *)malloc(sizeof(link_list_t));
		if(!new_link_node)
			return -1;
		link_node->next = new_link_node;
		link_node = new_link_node;
		input = strtol(*(argv+i), NULL, input_type);
		if(link_node_init(new_link_node, input))
			return -1;
	}
	
	link_list_print(&head_node);
	
	if(num_sys_convert(&head_node))
	{
		print_info(5);
		link_list_release(&head_node);
		return -1;
	}
	
	link_list_print(head_node.next);
	
	link_list_release(&head_node);
	
	return 0;
}

void print_info(int opts)
{
	printf(" \n \
		%s\n \
	\n", *(g_info + opts - 1));
}

int link_node_init(link_list_t *pnode, long int param)
{
	pnode->elem = param;
	pnode->res = (char *)malloc(BUF_SIZE*sizeof(char));
	if(!pnode->res)
		return -1;
	pnode->res_size = BUF_SIZE;
	pnode->res_cur_size = 0;
	pnode->next = NULL;
	return 0;
}

void link_list_print(link_list_t *pnode)
{
	link_list_t *link_node = pnode;
	while(link_node)
	{
		printf("%ld\t", link_node->elem);
		
		if(link_node->res && link_node->res_cur_size)
			printf("%s \n", link_node->res);
		else
			printf("NULL \n");
		
		link_node = link_node->next;
	}
}

void link_list_release(link_list_t *pnode)
{
	link_list_t *link_node = pnode->next;
	while(link_node)
	{
		if(link_node->res)
		{
			free(link_node->res);
			link_node->res = NULL;
		}
		
		free(link_node);
		link_node = link_node->next;
	}
	
	pnode->next = NULL;
}

int num_sys_convert(link_list_t *pnode)
{
	link_list_t *link_node = pnode->next; //ignore head_node
	unsigned int type = (pnode->elem < 0) ? (pnode->elem * -1) : pnode->elem;
	char *flag = NULL;
	char *tmp_node = NULL;
	long int temp = 0;
	
	while(link_node)
	{
		flag = link_node->res;
		//temp = (link_node->elem < 0) ? (link_node->elem * -1) : link_node->elem;
		temp = link_node->elem;
		
		while(temp)
		{
			if(link_node->res_cur_size >= link_node->res_size)
			{
				tmp_node = (char *)realloc(link_node->res, link_node->res_size+BUF_SIZE);
				if(!tmp_node)
					return -1;
				
				link_node->res = tmp_node;
				link_node->res_size += BUF_SIZE;
				flag = link_node->res + link_node->res_cur_size;//point to new address
			}

			*flag++ = symbol_table[temp % type];
			link_node->res_cur_size++;
			temp /= type;
		}
		
		link_node = link_node->next;
	}

	link_value_reverse(pnode);
	
	return 0;
}

int link_value_reverse(link_list_t *pnode)
{
	link_list_t *link_node = pnode->next;
	char *head_ptr = NULL, *tail_ptr = NULL;
	int i = 0, size = 0;
	char temp = 0;
	
	for(;link_node != NULL; link_node = link_node->next)
	{
		
		size = link_node->res_cur_size / 2;
		if(!size)
			continue;
		
		head_ptr = link_node->res;
		tail_ptr = link_node->res + link_node->res_cur_size - 1;
		if((!head_ptr) || (!tail_ptr))
			continue;
		
		for(i = 0; i < size; i++)
		{
			temp = *head_ptr;
			*head_ptr++ = *tail_ptr;
			*tail_ptr-- = temp;
		}
	}
	
	return 0;
}
