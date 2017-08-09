/*************************************************************************
	> File Name: control.c
	> Author: lvsenlv
	> Mail: lvsen46000@163.com
	> Created Time: 2017年08月09日 星期三 08时49分11秒
 ************************************************************************/

#include "control.h"

static char *g_pEnStr[] = {
    "Press Esc to exit. Encryption system designed by lvsenlv",
};
static char *g_pChStr[] = {
    "按Esc键退出。本加密系统由lvsenlv设计。",
};
char **g_pStr = g_pEnStr;



#ifdef __LINUX
#include <locale.h>
void CTL_InitConsole(void)
{
    setlocale(LC_ALL,"");
    initscr();
    cbreak();
    nonl();    
    //keypad(stdscr, true);
    attron(A_REVERSE | A_BOLD);
    mvaddstr(LINES-1, 0, g_pStr[CTL_STR_EXIT]);
    attroff(A_REVERSE | A_BOLD);
    refresh();    
}

G_STATUS CTL_ChooseLanguage(void)
{   
    int lines = 6, cols = 20;
    WINDOW *win = newwin(lines, cols, (LINES-lines)/2, (COLS-cols)/2);
    wborder(win, '+', '+', '-', '-', '+', '+', '+', '+');
    noecho();

    int EnStrStartX = 0;
    EnStrStartX = (cols - (sizeof(CTL_STR_CHOOSE_LANG_ENGLISH)-1)) / 2;
    int ChStrStartX = 0;
    ChStrStartX = (cols - ((sizeof(CTL_STR_CHOOSE_LANG_CHINESE)-1)*2/3)) / 2;
    wattron(win, A_REVERSE);
    mvwaddstr(win, 2, EnStrStartX, CTL_STR_CHOOSE_LANG_ENGLISH);
    wattroff(win, A_REVERSE);
    mvwaddstr(win, 3, ChStrStartX, CTL_STR_CHOOSE_LANG_CHINESE);
    wrefresh(win);
    CTL_MakeCursorInvis();

    keypad(win, true);
    int key = 0;
    char flag = 0;
    while(1)
    {
        key = wgetch(win);
        if((KEY_UP == key) || (KEY_DOWN == key))
        {
            flag ^= 1;
        }
        else if(13 == key) //Enter key
        {
            break;
        }
        else if(27 == key) //Esc key
        {
            delwin(win);
            return STAT_ERR;
        }
        else
            continue;
        
        if(flag)
        {
            mvwaddstr(win, 2, EnStrStartX, CTL_STR_CHOOSE_LANG_ENGLISH);            
            wattron(win, A_REVERSE);
            mvwaddstr(win, 3, ChStrStartX, CTL_STR_CHOOSE_LANG_CHINESE);
            wattroff(win, A_REVERSE);
            wrefresh(win);
            CTL_MakeCursorInvis();
        }
        else
        {
            wattron(win, A_REVERSE);
            mvwaddstr(win, 2, EnStrStartX, CTL_STR_CHOOSE_LANG_ENGLISH);
            wattroff(win, A_REVERSE);
            mvwaddstr(win, 3, ChStrStartX, CTL_STR_CHOOSE_LANG_CHINESE);
            wrefresh(win);
            CTL_MakeCursorInvis();
        }
    }

    g_pStr = (flag == 1) ? g_pChStr : g_pEnStr;
    delwin(win);
    touchline(stdscr, (LINES-lines)/2, (COLS-cols)/2);
    refresh();
    return STAT_OK;
}
#elif defined __WINDOWS
#endif

G_STATUS CTL_ShowMenu(void)
{
    return STAT_OK;
}




#if 0
 G_STATUS InputFileName(char *pFileName)
 {
     char ch, flag = 0;
     int i = 0;    
 
     memset(pFileName, '\0', FILE_NAME_LENGTH);
     CLEAR;
     DISP(STR_INPUT_FILE_NAME);
     ch = getchar();
     while(1)
     {
         if('\n' == ch)
             break;
         pFileName[i++] = ch;
         if(FILE_NAME_LENGTH == i)
         {
             flag = 1;
             CLEAR_IN_BUF;
             break;
         }
         ch= getchar();
     }
     
     if(flag)
     {
         return STAT_ERR;
         DISP_ERR(STR_ERR_INPUT_LEN_OUT_SIZE);
     }
     
     if(0 == i)
     {
         DISP_ERR(STR_ERR_INPUT_NULL);
         return STAT_ERR;            
     }
 
     return STAT_OK;
 }
 
 G_STATUS InputPassword(char *pPassword)
 {
     char ch, flag;
     int i;
     char TmpBuf[2];
 
     while(1)
     {
         flag = 0;
         i = 0;
         memset(pPassword, '\0', PASSWORD_LENGHT);
         CLEAR;
         DISP(STR_INPUT_PASSWORD);
         ch = getchar();
         while(1)
         {
             if('\n' == ch)
                 break;
             pPassword[i++] = ch;
             if(PASSWORD_LENGHT == i)
             {
                 flag = 1;
                 CLEAR_IN_BUF;
                 break;
             }
             ch= getchar();
         }
         
         if(flag)
         {
             DISP_ERR(STR_ERR_INPUT_LEN_OUT_SIZE);
             return STAT_ERR;
         }  
         
         if(0 == i)
         {
             DISP_ERR(STR_ERR_INPUT_NULL);
             return STAT_ERR;            
         }
 
#ifdef __CHINESE
         DISP("警告：请再次确认你的秘钥是否为：\n%s \n", pPassword);
         DISP("1. 继续：请输入 y 或 Y 并回车 \n");
         DISP("2. 重新输入：请输入 r 或 R 并回车 \n");
         DISP("3. 退出程序：请输入其他按键并回车 \n");
#else
         DISP("Warning: Confirm your key is: \n%s \n", pPassword);
         DISP("1. Continue: Press y or Y and Enter \n");
         DISP("2. Retry: Press r or R and Enter \n");
         DISP("3. Exit: Press other keys and Enter \n");
#endif
         i = 0;
         flag = 0;
         ch = getchar(); 
         while(1)
         {
             if('\n' == ch)
                 break;
             TmpBuf[i++] = ch;
             if(i > 1)
             {
                 flag = 1;
                 CLEAR_IN_BUF;
                 break;
             }
             ch= getchar();
         }
         
         if(flag)
             return STAT_ERR;
         
         if(('Y' == TmpBuf[0]) || ('y' == TmpBuf[0]))
             break;
         else if(('R' == TmpBuf[0]) || ('r' == TmpBuf[0]))
             continue;
         else
             return STAT_ERR;
         
     }
     
     return STAT_OK;
 }

#endif

