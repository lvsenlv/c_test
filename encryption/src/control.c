/*************************************************************************
	> File Name: control.c
	> Author: lvsenlv
	> Mail: lvsen46000@163.com
	> Created Time: 2017年08月09日 星期三 08时49分11秒
 ************************************************************************/

#include "control.h"
#include "control_str.h"
#include "encryption.h"
#include <string.h>
#include <unistd.h>

char **g_pStr = pEnStr;
char g_FlagLanguage = 0; //0 is English and 1 is Chinese

#ifdef __LINUX
#include <locale.h>
void CTL_InitConsole(void)
{
    setlocale(LC_ALL,"");
    initscr();
    cbreak();
    nonl();
    noecho();
    keypad(stdscr, true);
    attron(A_REVERSE | A_BOLD);
    mvaddnstr(LINES-1, 0, g_pStr[CTL_STR_ESC_EXIT], COLS);
    attroff(A_REVERSE | A_BOLD);
    refresh();    
}

G_STATUS CTL_ChooseLanguage(void)
{   
    int lines = 6, cols = 20;
    WINDOW *win = newwin(lines, cols, (LINES-lines)/2, (COLS-cols)/2);
    wborder(win, '+', '+', '-', '-', '+', '+', '+', '+');    

    int EnStrStartX = 0;
    EnStrStartX = (cols - (sizeof(CTL_STR_CHOOSE_LANG_ENGLISH)-1)) / 2;
    int ChStrStartX = 0;
    ChStrStartX = (cols - ((sizeof(CTL_STR_CHOOSE_LANG_CHINESE)-1)*2/3)) / 2;
    mvwaddstr(win, 3, ChStrStartX, CTL_STR_CHOOSE_LANG_CHINESE);
    wattron(win, A_REVERSE);
    mvwaddstr(win, 2, EnStrStartX, CTL_STR_CHOOSE_LANG_ENGLISH);
    wattroff(win, A_REVERSE);    

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
            return STAT_EXIT;
        }
        else
            continue;
        
        if(flag)
        {
            mvwaddstr(win, 2, EnStrStartX, CTL_STR_CHOOSE_LANG_ENGLISH);            
            wattron(win, A_REVERSE);
            mvwaddstr(win, 3, ChStrStartX, CTL_STR_CHOOSE_LANG_CHINESE);
            wattroff(win, A_REVERSE);
        }
        else
        {
            mvwaddstr(win, 3, ChStrStartX, CTL_STR_CHOOSE_LANG_CHINESE);
            wattron(win, A_REVERSE);
            mvwaddstr(win, 2, EnStrStartX, CTL_STR_CHOOSE_LANG_ENGLISH);
            wattroff(win, A_REVERSE);
        }
    }

    g_pStr = (flag == 1) ? pChStr : pEnStr;
    g_FlagLanguage = flag;
    delwin(win);
    touchline(stdscr, (LINES-lines)/2, (COLS-cols)/2);
    refresh();
    return STAT_OK;
}

void CTL_DrawStdScreen(void)
{
    border('|', '|', '-', '-', '+', '+', '+', '+');
    int LabelSize = strlen(g_pStr[CTL_STR_LABEL]);

    attron(A_REVERSE);
    if(g_FlagLanguage)
    {
        mvaddstr(0, (COLS-LabelSize*2/3)/2, g_pStr[CTL_STR_LABEL]);
    }
    else
    {
        mvaddstr(0, (COLS-LabelSize)/2, g_pStr[CTL_STR_LABEL]);
    }

    attron(A_BOLD);
    mvaddnstr(LINES-2, 2, g_pStr[CTL_STR_END_LINE], COLS-3);
    attroff(A_REVERSE | A_BOLD);
    refresh();
}

G_STATUS CTL_ChooseFunc(char *pFunc)
{    
    mvaddnstr(2, 2, g_pStr[CTL_STR_MENU_FUNC2], COLS-3);
    mvaddnstr(3, 2, g_pStr[CTL_STR_MENU_FUNC3], COLS-3);
    mvaddnstr(4, 2, g_pStr[CTL_STR_MENU_FUNC4], COLS-3);
    mvaddnstr(5, 2, g_pStr[CTL_STR_MENU_FUNC5], COLS-3);
    attron(A_REVERSE);
    mvaddnstr(1, 2, g_pStr[CTL_STR_MENU_FUNC1], COLS-3);
    attroff(A_REVERSE);
    refresh();

    int key;
    int CurPosY = 1;
    while(1)
    {
        key = getch();        
        
        if(KEY_UP == key)
        {
            mvaddnstr(CurPosY, 2, g_pStr[CTL_STR_MENU_FUNC1-1+CurPosY], COLS-3);
            CurPosY--;
        }
        else if(KEY_DOWN == key)
        {
            mvaddnstr(CurPosY, 2, g_pStr[CTL_STR_MENU_FUNC1-1+CurPosY], COLS-3);
            CurPosY++;
        }
        else if(13 == key) //Enter key
            break;
        else if(27 == key) //Esc key
            return STAT_EXIT;
        else
            continue;

        if(0 == CurPosY)
        {
            CurPosY = CTL_MENU_FUNC_NUM;
        }
        else if(CurPosY > CTL_MENU_FUNC_NUM)
        {
            CurPosY = 1;
        }

        attron(A_REVERSE);
        mvaddnstr(CurPosY, 2, g_pStr[CTL_STR_MENU_FUNC1-1+CurPosY], COLS-3);
        attroff(A_REVERSE);            
    }

    *pFunc = (char)CurPosY;
    return STAT_OK;
}

G_STATUS CTL_ShowInstruction(void)
{
    WINDOW *win = newwin(LINES, COLS, 0, 0);
    wborder(win, '*', '*', '*', '*', '*', '*', '*', '*');    
    wattron(win, A_REVERSE | A_BOLD);
    mvwaddnstr(win, LINES-2, 2, g_pStr[CTL_STR_END_LINE], COLS-3);
    wattroff(win, A_REVERSE | A_BOLD);
    
    char **ptr = g_FlagLanguage ? pChInstruction : pEnInstruction;
    int CurPosY = 1;
    
    while(*ptr != NULL)
    {
        if(CurPosY < LINES-3) //there are other info at the last 3 lines
            mvwaddnstr(win, CurPosY++, 2, *ptr++, COLS-3);
        else
            break;
    }
    wattron(win, A_REVERSE);
    mvwaddnstr(win, CurPosY, 2, g_pStr[CTL_STR_BACK], COLS-3);
    wattroff(win, A_REVERSE);

    int key;
    keypad(win, true);  
    while(1)
    {
        key = wgetch(win);
        if(13 == key) //Enter key
            break;
        else if(27 == key) //Esc key
        {
            delwin(win);
            return STAT_EXIT;
        }
        else
            continue;
    }

    wrefresh(win);
    touchwin(stdscr);
    refresh();
    return STAT_OK;
}


G_STATUS CTL_GetFileName(char *pFileName)
{
    int lines = 7, cols = strlen(g_pStr[CTL_STR_INPUT_FILE_NAME]);
    if(g_FlagLanguage)
    {
        cols = cols * 2 / 3 + 4;    //4 chars on side edge
    }
    else
        cols += 4;                  //4 chars on side edge
    WINDOW *win = newwin(lines, cols, (LINES-lines)/2, (COLS-cols)/2);
    mvwhline(win, 0, 0, '*', cols);
    mvwhline(win, 6, 0, '*', cols);
       
    int key;    
    char flag;
    int Str1StartX = (cols-12)/3; //CTL_STR_RETRY and CTL_STR_BACK are about 12 bytes
    int Str2StartX = Str1StartX*2 + 6; //6 bytes per string        
    while(1)
    {   
        key = 0;
        flag = 0;
        echo();
        keypad(win, false); 
        mvwaddnstr(win, 1, 0, g_pStr[CTL_STR_INPUT_FILE_NAME], cols);
        mvwaddnstr(win, 2, 0, g_pStr[CTL_STR_INPUT_FILE_NAME_EG], cols);
        mvwaddnstr(win, 3, 0, g_pStr[CTL_STR_INPUT], cols);
        mvwgetnstr(win, 3, strlen(g_pStr[CTL_STR_INPUT]), pFileName, CYT_FILE_NAME_LENGTH-1);        
        if(access(pFileName, F_OK) == 0)
            break;
        
        keypad(win, true); 
        mvwhline(win, 1, 0, ' ', cols);
        mvwhline(win, 2, 0, ' ', cols);
        mvwhline(win, 3, 0, ' ', cols);
        mvwhline(win, 4, 0, ' ', cols);
        mvwhline(win, 5, 0, ' ', cols);
        if(g_FlagLanguage)
        {
            mvwaddstr(win, 2, (cols - strlen(g_pStr[CTL_STR_ERR_FILE_NOT_EXIST])*2/3)/2, 
                g_pStr[CTL_STR_ERR_FILE_NOT_EXIST]);
        }
        else
        {
            mvwaddstr(win, 2, (cols-strlen(g_pStr[CTL_STR_ERR_FILE_NOT_EXIST]))/2, 
                g_pStr[CTL_STR_ERR_FILE_NOT_EXIST]);
        }
        mvwaddstr(win, 4, Str2StartX, g_pStr[CTL_STR_BACK]);
        wattron(win, A_REVERSE);
        mvwaddstr(win, 4, Str1StartX, g_pStr[CTL_STR_RETRY]);
        wattroff(win, A_REVERSE);

        noecho();
        while(1)
        {
            key = wgetch(win);
            if((KEY_LEFT == key) || (KEY_RIGHT == key))
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
                mvwaddstr(win, 4, Str1StartX, g_pStr[CTL_STR_RETRY]);
                wattron(win, A_REVERSE);
                mvwaddstr(win, 4, Str2StartX, g_pStr[CTL_STR_BACK]);
                wattroff(win, A_REVERSE);
            }
            else
            {                
                mvwaddstr(win, 4, Str2StartX, g_pStr[CTL_STR_BACK]);
                wattron(win, A_REVERSE);
                mvwaddstr(win, 4, Str1StartX, g_pStr[CTL_STR_RETRY]);
                wattroff(win, A_REVERSE);
            }
        }

        if(flag)
        {
            delwin(win);
            touchline(stdscr, (LINES-lines)/2, (COLS-cols)/2);
            refresh();
            return STAT_GO_BACK;
        }            

        mvwhline(win, 1, 0, ' ', cols);
        mvwhline(win, 2, 0, ' ', cols);
        mvwhline(win, 3, 0, ' ', cols);
        mvwhline(win, 4, 0, ' ', cols);
        mvwhline(win, 5, 0, ' ', cols);
    }

    delwin(win);
    touchline(stdscr, (LINES-lines)/2, (COLS-cols)/2);
    refresh();

    return STAT_OK;
}

#elif defined __WINDOWS
#endif

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

