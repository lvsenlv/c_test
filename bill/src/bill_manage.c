/*************************************************************************
	> File Name: bill_manage.c
	> Author: lvsenlv
	> Mail: lvsen46000@163.com
	> Created Time: 2017年07月24日 星期一 10时08分33秒
 ************************************************************************/

#include "bill_manage.h"
#include <string.h>

volatile int g_flag = FLAG_DO_NOTHING;
FILE *g_fp = NULL;
char g_buf[BUF_SIZE];
char g_input_username[USERNAME_SIZE];

int main(void)
{   
    while(1)
    {
        disp_home_page();
        if(FLAG_LOGIN_EXISTTING_ACCOUNT == g_flag)
        {
            login();
            if(FLAG_BACK_HOME_PAGE == g_flag)
                continue;
            break;
        }
        else if(FLAG_CREATE_NEW_ACCOUNT == g_flag)
        {
            continue;
        }
        else if(FLAG_DELETE_EXISTTING_ACCOUNT == g_flag)
        {
            continue;
        }
        else if(FLAG_EXIST == g_flag)
        {
            break;
        }
    }
    
    return 0;
}

G_STATUS disp_home_page(void)
{
    char **pptr = NULL;
    int i = 0;
    while(1)
    {
        CLEAR;
        pptr = g_home_page;
        i = 0;  
        while(*pptr != NULL)
        {
            i++;
            DISP("%s \n", *pptr++);
        }

        DISP(STR_INPUT);
        scanf("%d", &g_flag);
        CLEAR_IN_BUF;
        if((g_flag > 0) && (g_flag < i))
        {
            switch(g_flag)
            {
                case 1 :
                    g_flag = FLAG_LOGIN_EXISTTING_ACCOUNT;
                    break;
                case 2 :
                    g_flag = FLAG_CREATE_NEW_ACCOUNT;
                    break;
                case 3 :
                    g_flag = FLAG_DELETE_EXISTTING_ACCOUNT;
                    break;
                case 4 :
                    g_flag = FLAG_EXIST;
                    break;
                default :
                    break;
            }
            break;
        }

        CLEAR;
        DISP("%s \n", STR_ERR_ILLGAL_INPUT);
        DISP(STR_ANY_KEY);
        WAIT_FOR_KEY;
    }

    return STAT_OK;
}

G_STATUS login(void)
{
    g_fp = fopen(CONF_FILE, "r");
    if(NULL == g_fp)
    {
        DISP_ERR(STR_ERR_CONF_FILE_CORRUPTION);
        return STAT_ERR;
    }

    int i;
    char ch, flag;
    int tmp = 0;
    while(1)
    {
        //input username
        i = 0;
        flag = 0;
        memset(g_input_username, '\0', USERNAME_SIZE);
        fseek(g_fp, 0, SEEK_SET);
        
        CLEAR;
        DISP("%s \n", STR_INPUT_USERNAME);
        ch = getchar();
        while(1)
        {
            if('\n' == ch)
                break;
            g_input_username[i++] = ch;
            if(USERNAME_SIZE == i)
            {
                flag = 1;
                CLEAR_IN_BUF;
                break;
            }
            ch= getchar();
        }
        
        if(flag)
        {
            CLEAR;
            DISP("%s \n", STR_ERR_USER_NAME_OUT_SIZE);
            DISP(STR_ANY_KEY);
            WAIT_FOR_KEY;
            continue;
        }
        
        //get username in conf File
        tmp = i; //length of username
        while(1)
        {
            flag = 0;
            memset(g_buf, '\0', PASSWORD_SIZE);
            fgets(g_buf, BUF_SIZE, g_fp);
            if(feof(g_fp) != 0)  //username not exist
            {
                while(1)
                {
                    CLEAR;
                    DISP("%s \n", STR_ERR_USER_NAME_NOT_EXIST);
                    DISP("1. %s \n2. %s \n%s", STR_RETRY, STR_BACK_HOME_PAGE, STR_INPUT);
                    scanf("%d", &g_flag);
                    CLEAR_IN_BUF;
                    if(1 == g_flag)
                    {
                        flag = 1; //make sure to re-input
                        break;
                    }
                    else if(2 == g_flag)
                    {
                        g_flag = FLAG_BACK_HOME_PAGE;
                        fclose(g_fp);
                        return STAT_OK;
                    }

                    CLEAR;
                    DISP("%s \n", STR_ERR_ILLGAL_INPUT);
                    DISP(STR_ANY_KEY);
                    WAIT_FOR_KEY;
                }

                break;
            }
            
            for(i = 0; i < tmp; i++)
            {
                if(g_input_username[i] != g_buf[i])
                {
                    flag = 1;
                    break;
                }
            }
            if(flag)
                continue;

            if((g_buf[i++] != ' ') || (g_buf[i++] != ':') || (g_buf[i++] != ' '))
            {
                continue;
            }
            else
                break;
        }
        if(0 == flag)
            break;
    }

    //get password in conf File
    tmp = 0;
    char correct_password[PASSWORD_SIZE];
    while((g_buf[i] != '\n') && (g_buf[i] != '\0'))
    {
        correct_password[tmp++] = g_buf[i++];        
    }
    correct_password[tmp] = '\0';

    //input password
    char input_password[PASSWORD_SIZE];
    while(1)
    {
        i = 0;
        flag = 0;
        memset(input_password, '\0', PASSWORD_SIZE);
        memset(g_buf, '\0', PASSWORD_SIZE);
        
        CLEAR;
        DISP("%s \n", STR_INPUT_PASSWOED);
        ch = getchar();
        while(1)
        {
            if('\n' == ch)
                break;
            input_password[i++] = ch;
            if(PASSWORD_SIZE == i)
            {
                flag = 1;
                CLEAR_IN_BUF;
                break;
            }
            ch= getchar();
        }

        if(flag)
        {
            CLEAR;
            DISP("%s \n", STR_ERR_PASSWORD_OUT_SIZE);
            DISP(STR_ANY_KEY);
            WAIT_FOR_KEY;
            continue;
        }

        if(strcmp(correct_password, input_password) != 0)
        {
            while(1)
            {
                CLEAR;
                DISP("%s \n", STR_ERR_PASSWORD_ERR);
                DISP("1. %s \n2. %s \n%s", STR_RETRY, STR_BACK_HOME_PAGE, STR_INPUT);
                scanf("%d", &g_flag);
                CLEAR_IN_BUF;
                if(1 == g_flag)
                {
                    flag = 1; //make sure to re-input
                    break;
                }
                else if(2 == g_flag)
                {
                    g_flag = FLAG_BACK_HOME_PAGE;
                    fclose(g_fp);
                    return STAT_OK;
                }

                CLEAR;
                DISP("%s \n", STR_ERR_ILLGAL_INPUT);
                DISP(STR_ANY_KEY);
                WAIT_FOR_KEY;
            }
        }
        else
            break;
    }

    CLEAR;
    DISP("%s \n", STR_LOGIN_SUCCESS);
    DISP(STR_ANY_KEY);
    WAIT_FOR_KEY;

    fclose(g_fp);
    return STAT_OK;
}


