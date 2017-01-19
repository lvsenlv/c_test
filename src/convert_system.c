/*************************************************************************
	> File Name: main.c
	> Author: 
	> Mail: 
	> Created Time: 2017年01月12日 星期四 09时38分45秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "convert_system.h"

extern char *g_info[];
extern char g_symbol_table[];
extern int g_num_table[];

int main(int argc, char *argv[])
//int main(void)
{
	/*int argc = 4;
	char *argv[4] = {
		"test",
		"-16",
		"-10",
		"ABc"
	};*/
#ifdef __DEBUG__
	struct timeval start_usec;
	struct timeval stop_usec;
	gettimeofday(&start_usec,NULL);
#endif //__DEBUG__

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
	int i = 0;
	short int flag_strtol = 0;
	link_list_t head_node, *link_node = NULL, *new_link_node = NULL;
	head_node.elem = output_type;
	head_node.res = NULL;
	head_node.res_size = 0;
	head_node.res_cur_size = 0;
	head_node.flag_avalid = -1;
	head_node.next = NULL;
	link_node = &head_node;
	for(i = arg_nums; i < argc; i++)
	{
		flag_strtol = 0;
		new_link_node = (link_list_t *)malloc(sizeof(link_list_t));
		if(!new_link_node)
		{
			DISP_INFO(INFO_MALLOC);
			return -1;
		}

		input = strtol_rewrite(*(argv+i), &flag_strtol, input_type);
		input = (input < 0) ? (input * -1) : input;//ignore the sign
		if(output_type == 10)
			new_link_node->flag_avalid = flag_strtol ? FLAG_INVALID : FLAG_OUT_10;
		else if(input_type == output_type)
			new_link_node->flag_avalid = flag_strtol ? FLAG_INVALID : FLAG_IN_OUT;
		else
			new_link_node->flag_avalid = flag_strtol ? FLAG_INVALID : FLAG_ELSE;
		link_node->next = new_link_node;
		link_node = new_link_node;
		if(link_node_init(new_link_node, input))
			return -1;
	}

#ifdef __DEBUG__
	link_list_print(&head_node, argc, argv);
#endif //__DEBUG__

	if(num_sys_convert(&head_node))
	{
		DISP_INFO(INFO_CONVERT);
		link_list_release(&head_node);
		return -1;
	}
	
	link_list_print(&head_node, argc, argv);
	
	link_list_release(&head_node);
	
#ifdef __DEBUG__
	gettimeofday(&stop_usec, NULL);
	printf("project costs %ld us\n", \
		(stop_usec.tv_sec - start_usec.tv_sec)*1000000 + stop_usec.tv_usec - start_usec.tv_usec);
#endif //__DEBUG__

	return 0;
}

ELEM_TYPE strtol_rewrite(const char *nptr, short int *flag_strtol, int base)
{
	if(base > 35 || base < 2)
	{
		*flag_strtol = -1;
		return -1;
	}
    ELEM_TYPE sum = 0, res = 1, base_num = 1;
    int num = 0, count = 0;
    int i =0;
	short int flag_sign = 0;
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
            num = g_num_table[*ptr - '0'];
        else if(*ptr >= 'A' && *ptr <= 'Z')
            num = g_num_table[*ptr - 'A' + 10];
        else if(*ptr >= 'a' && *ptr <= 'z')
            num = g_num_table[*ptr - 'a' + 10];
		else
		{
			*flag_strtol = -1;
			return -1;
		}

        if(num > base-1)
        {
			*flag_strtol = -1;
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
            num = g_num_table[*ptr - '0'];
        else if(*ptr >= 'A' && *ptr <= 'Z')
            num = g_num_table[*ptr - 'A' + 10];
        else if(*ptr >= 'a' && *ptr <= 'z')
            num = g_num_table[*ptr - 'a' + 10];

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
	if(pnode->flag_avalid == FLAG_INVALID || \
		pnode->flag_avalid == FLAG_OUT_10 || \
		pnode->flag_avalid == FLAG_IN_OUT)
	{
		pnode->res = NULL;
		pnode->res_size = 0;
	}
	else
	{
		pnode->res = (char *)malloc(BUF_SIZE*sizeof(char));
		if(!pnode->res)
		{
			DISP_INFO(INFO_MALLOC);
			return -1;
		}
		pnode->res_size = BUF_SIZE;
	}
	
	pnode->res_cur_size = 0;
	pnode->next = NULL;
	return 0;
}

void link_list_print(link_list_t *pnode, int argc, char **argv)
{
	link_list_t *link_node = pnode->next;
	int i = ARGC_OFFSET;
	while(link_node && i < argc)
	{	
		if(link_node->flag_avalid == FLAG_INVALID)
		{
			DISP_INFO(INFO_PARAM_ERROR);
			link_node = link_node->next;
			i++;
			continue;
		}
		
		printf("%s -> ", *(argv+i));
		switch(link_node->flag_avalid)
		{
			case FLAG_OUT_10:
				printf("%lld \n", link_node->elem);
				break;
			case FLAG_IN_OUT:
				printf("%s \n", *(argv+i));
				break;
			default:
				(link_node->res && link_node->res_cur_size) ? \
					printf("%s \n", link_node->res) : printf("NULL \n");
				
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
	char *tmp_res = NULL;
	char *tmp_node = NULL;
	ELEM_TYPE tmp_elem = 0;
	
	while(link_node)
	{
		if(link_node->flag_avalid == FLAG_INVALID || \
			link_node->flag_avalid == FLAG_OUT_10 || \
			link_node->flag_avalid == FLAG_IN_OUT)
		{
			link_node = link_node->next;
			continue;
		}
		tmp_res = link_node->res;
		//tmp_elem = (link_node->elem < 0) ? (link_node->elem * -1) : link_node->elem;
		tmp_elem = link_node->elem;
		
		while(tmp_elem)
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
				tmp_res = link_node->res + link_node->res_cur_size;//point to new address
			}

			*tmp_res++ = g_symbol_table[tmp_elem % type];
			link_node->res_cur_size++;
			tmp_elem /= type;
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
	char tmp_elem = 0;
	
	for(;link_node != NULL; link_node = link_node->next)
	{
		if(link_node->flag_avalid == FLAG_INVALID || \
			link_node->flag_avalid == FLAG_OUT_10 || \
			link_node->flag_avalid == FLAG_IN_OUT)
			continue;
		
		size = link_node->res_cur_size / 2;
		if(!size)
			continue;
		
		head_ptr = link_node->res;
		tail_ptr = link_node->res + link_node->res_cur_size - 1;
		if((!head_ptr) || (!tail_ptr))
			continue;
		
		for(i = 0; i < size; i++)
		{
			tmp_elem = *head_ptr;
			*head_ptr++ = *tail_ptr;
			*tail_ptr-- = tmp_elem;
		}
	}
	
	return 0;
}

