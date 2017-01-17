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

extern char *g_info[];
extern char symbol_table[];
extern int num_table[];

int main(void)
//int main(int argc, char *argv[])
{
	int argc = 6;
	char *argv[6] = {
		"test",
		"-10",
		"-2",
		"17A",
		"10",
		"158"
	};
	if(argc < 4)
	{
		DISP_INFO(INFO_FUNC);
		DISP_INFO(INFO_USAGE);
		DISP_INFO(INFO_INPUT);
		DISP_INFO(INFO_OUTPUT);
		return -1;
	}

	int input_type = 0, output_type = 0;
	ELEM_TYPE input = 0;
	input_type = strtol(*(argv+1), NULL, 10) * -1;
	output_type = strtol(*(argv+2), NULL, 10) * -1;
	if( input_type < 0 || output_type < 0 )
	{
		DISP_INFO(INFO_INPUT);
		DISP_INFO(INFO_OUTPUT);
		return -1;
	}
	if( input_type < 2 || input_type > 36 || output_type <2 || output_type > 36 )
	{
		DISP_INFO(INFO_INPUT_RANGE);
		DISP_INFO(INFO_OUTPUT_RANGE);
		return -1;
	}
	
	int arg_nums = ARGC_OFFSET;//ignore 3 params: file_name, input_type, output_type
	int i = 0, flag_strtol = 0;
	link_list_t head_node, *link_node = NULL, *new_link_node = NULL;
	head_node.elem = output_type;
	head_node.res = NULL;
	head_node.res_size = 0;
	head_node.res_cur_size = 0;
	head_node.next = NULL;
	link_node = &head_node;
	for(i = arg_nums; i < argc; i++)
	{
		flag_strtol = 0;
		input = strtol_rewrite(*(argv+i), &flag_strtol, input_type);
		if(flag_strtol)
			continue;
		
		new_link_node = (link_list_t *)malloc(sizeof(link_list_t));
		if(!new_link_node)
		{
			DISP_INFO(INFO_MALLOC);
			return -1;
		}

		link_node->next = new_link_node;
		link_node = new_link_node;
		input = (input < 0) ? (input * -1) : input;//ignore the sign
		if(link_node_init(new_link_node, input))
			return -1;
	}
	
	//link_list_print(&head_node);
	if(num_sys_convert(&head_node))
	{
		DISP_INFO(INFO_CONVERT);
		link_list_release(&head_node);
		return -1;
	}
	
	link_list_print(&head_node, argc, argv, FLAG_ELSE);
	
	link_list_release(&head_node);
	
	return 0;
}

ELEM_TYPE strtol_rewrite(const char *nptr, int *flag_strtol, int base)
{
	if(base > 35 || base < 2)
	{
		DISP_INFO(INFO_PARAM_ERROR);
		*flag_strtol = -1;
		return -1;
	}
    ELEM_TYPE sum = 0, res = 1, base_num = 1;
    int num = 0, count = 0;
    int i =0, flag_sign = 0;
    const char *ptr = NULL;
    if(*nptr == '-')
    {
		nptr++;
		flag_sign = 1;
	}
	
	while(*nptr == '0')
		nptr++;
	
    ptr = nptr;
    while(*ptr != ' ' &&  *ptr != '\t' && *ptr != '\0')
    {
        if(*ptr >= '0' && *ptr <= '9')
            num = num_table[*ptr - '0'];
        else if(*ptr >= 'A' && *ptr <= 'Z')
            num = num_table[*ptr - 'A' + 10];
        else if(*nptr >= 'a' && *ptr <= 'z')
            num = num_table[*ptr - 'a' + 10];
		else
		{
			*flag_strtol = -1;
			DISP_INFO(INFO_PARAM_ERROR);
			return -1;
		}

        if(num > base-1)
        {
			*flag_strtol = -1;
			DISP_INFO(INFO_PARAM_ERROR);
			return -1;			
		}

        count++;
        ptr++;
    }
	
    ptr = nptr;
    for(i = 1; i < count; i++)
        base_num *= base;
    for(i = 0; i < count; i++)
    {
        if(*ptr >= '0' && *ptr <= '9')
            num = num_table[*ptr - '0'];
        else if(*ptr >= 'A' && *ptr <= 'Z')
            num = num_table[*ptr - 'A' + 10];
        else if(*nptr >= 'a' && *ptr <= 'z')
            num = num_table[*ptr - 'a' + 10];

        res = num * base_num;
        base_num /= base;
        sum += res;
        ptr++;
    }
    return (flag_sign == 1 ? sum*-1 : sum);
}

int link_node_init(link_list_t *pnode, ELEM_TYPE param)
{
	pnode->elem = param;
	pnode->res = (char *)malloc(BUF_SIZE*sizeof(char));
	if(!pnode->res)
	{
		DISP_INFO(INFO_MALLOC);
		return -1;
	}
	
	pnode->res_size = BUF_SIZE;
	pnode->res_cur_size = 0;
	pnode->next = NULL;
	return 0;
}

void link_list_print(link_list_t *pnode, int argc, char **argv, int flag_print)
{
	link_list_t *link_node = pnode->next;
	int i = ARGC_OFFSET;
	while(link_node && i < argc)
	{	
		printf("%s -> ", *(argv+i));
		switch(flag_print)
		{
			case FLAG_OUT_10:
				printf("%lld \n", link_node->elem);
				break;
			case FLAG_IN_OUT:
				printf("%s \n", *(argv+i));
				break;
			default:
				if(link_node->res && link_node->res_cur_size)
					printf("%s \n", link_node->res);
				else
					printf("NULL \n");
				
				break;
		}
				
		link_node = link_node->next;
		i++;
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
	//int type = (pnode->elem < 0) ? (pnode->elem * -1) : pnode->elem;
	unsigned int type = pnode->elem;
	char *flag_res = NULL;
	char *tmp_node = NULL;
	ELEM_TYPE temp = 0;
	
	while(link_node)
	{
		flag_res = link_node->res;
		//temp = (link_node->elem < 0) ? (link_node->elem * -1) : link_node->elem;
		temp = link_node->elem;
		
		while(temp)
		{
			if(link_node->res_cur_size >= link_node->res_size)
			{
				tmp_node = (char *)realloc(link_node->res, link_node->res_size+BUF_SIZE);
				if(!tmp_node)
				{
					DISP_INFO(INFO_REALLOC);
					return -1;
				}
				
				link_node->res = tmp_node;
				link_node->res_size += BUF_SIZE;
				flag_res = link_node->res + link_node->res_cur_size;//point to new address
			}

			*flag_res++ = symbol_table[temp % type];
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

