/*************************************************************************
	> File Name: bill_manage.c
	> Author: lvsenlv
	> Mail: lvsen46000@163.com
	> Created Time: 2017年07月24日 星期一 10?08分33秒
 ************************************************************************/

#include "bill_manage.h"
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>
#include <string.h>

volatile int g_cur_pos_y = 0;
volatile int g_cur_pos_x = 0;
char buf[BUF_SIZE];
char *g_user_name_ptr = NULL;
char *g_password_ptr = NULL;

int main(void)
{   
    setlocale(LC_ALL,"");
    initscr();
    cbreak();
    nonl();
    //noecho();
    keypad(stdscr, true);

    refresh();  

    draw_std_screen();
    login();
    

    sleep(10);
    endwin();
    return 0;
}

void draw_std_screen(void)
{ 
    //border('|', '|', '-', '-', '-', '-', '-', '-');
    
    box(stdscr, ACS_VLINE, ACS_HLINE);
    attron(A_REVERSE);
    mvaddstr(STD_SCR_START_Y, (COLS-sizeof(STR_LABEL))/2, STR_LABEL);
    attroff(A_REVERSE);
    move(++g_cur_pos_y, ++g_cur_pos_x);
    refresh();
}

void login(void)
{    
    WINDOW *login_win = newwin(LOGIN_WIN_LINES, LOGIN_WIN_COLS, LOGIN_WIN_START_Y, LOGIN_WIN_START_X);
    int cur_pos_y = 1, cur_pos_x = 1;
    box(login_win, ACS_VLINE, ACS_HLINE);
    keypad(login_win, true);
    
    mvwaddstr(login_win, cur_pos_y++, (LOGIN_WIN_COLS-sizeof(STR_LOGIN))/2, STR_LOGIN);
    mvwaddstr(login_win, cur_pos_y++, cur_pos_x, STR_LOGIN_USER);
    mvwaddstr(login_win, cur_pos_y, cur_pos_x, STR_LOGIN_PASSWORD);
    cur_pos_y = 2;
    cur_pos_x = 1 + sizeof(STR_LOGIN_USER);
    wmove(login_win, cur_pos_y, cur_pos_x);  
    wrefresh(login_win);

    g_user_name_ptr = (char *)malloc(LOGIN_WIN_USER_NAME_SIZE);       
    if(g_user_name_ptr == NULL)
    {
        delwin(login_win);
        endwin();
        DISP_ERR(ERR_MALLOC);
        exit(-1);
    }
    g_password_ptr = (char *)malloc(LOGIN_WIN_PASSWORD_SIZE); 
    if(g_password_ptr == NULL)
    {
        free(g_user_name_ptr);
        delwin(login_win);
        endwin();
        DISP_ERR(ERR_MALLOC);
        exit(-1);
    }    

    do
    {
        wgetnstr(login_win, g_user_name_ptr, LOGIN_WIN_USER_NAME_SIZE-1);
        cur_pos_y = 3;
        cur_pos_x = 1 + sizeof(STR_LOGIN_PASSWORD);
        wmove(login_win, cur_pos_y, cur_pos_x);
        wrefresh(login_win);

        snprintf(buf, BUF_SIZE, "./%s.conf", g_user_name_ptr);
        if(access(buf, F_OK))
        {
            win_disp(STR_LOGIN_USER_NOT_EXIST);
            touchwin(login_win);
            continue;
        }
        break;
    }while(1);
    
    sleep(10);
    free(g_user_name_ptr);
    free(g_password_ptr);
    delwin(login_win);
    touchline(stdscr, LOGIN_WIN_START_Y, LOGIN_WIN_LINES);
    refresh();
}

void win_disp(const char *ptr)
{    
    int len = strlen(ptr);
    if(len < sizeof(STR_ANY_KEY)) 
    {
        len = sizeof(STR_ANY_KEY);
    }
    int tmp_win_lines = LINES/4, tmp_win_cols = len+2;
    int tmp_pos_y = 0, tmp_pos_x = 0;
    
    WINDOW *tmp_win = newwin(tmp_win_lines, tmp_win_cols, STD_SCR_START_Y, STD_SCR_START_X);
    box(tmp_win, '*', '*');        
    
    tmp_pos_y = tmp_win_lines / 2 - 1;
    tmp_pos_x = (tmp_win_cols - len) / 2;
    mvwaddstr(tmp_win, tmp_pos_y++, tmp_pos_x, ptr);
    mvwaddstr(tmp_win, tmp_pos_y, tmp_pos_x, STR_ANY_KEY);
    wrefresh(tmp_win);
    wgetch(tmp_win);
    delwin(tmp_win);
}

