/*************************************************************************
	> File Name: bill_manage.c
	> Author: lvsenlv
	> Mail: lvsen46000@163.com
	> Created Time: 2017年07月24日 星期一 10时08分33秒
 ************************************************************************/

#include "bill_manage.h"
#include <unistd.h>
#include <locale.h>
#include <string.h>

volatile int g_cur_pos_y = 0;
volatile int g_cur_pos_x = 0;
FILE *g_conf_file_fp = NULL;
FILE *g_data_file_fp = NULL;
char g_conf_file[CONF_FILE_SIZE];
char g_buf[BUF_SIZE];

int main(void)
{   
    setlocale(LC_ALL,"");
    initscr();
    cbreak();
    nonl();    
    keypad(stdscr, true);

    refresh();  

    draw_std_screen();
    
    if(login() != STAT_OK)
        return -1;

    

    sleep(3);
    endwin();
    return 0;
}

void draw_std_screen(void)
{ 
    //border('|', '|', '-', '-', '-', '-', '-', '-');
    
    box(stdscr, ACS_VLINE, ACS_HLINE);
    attron(A_REVERSE);
#ifdef __CHINESE
    mvaddstr(STD_SCR_START_Y, (COLS-(sizeof(STR_LABEL)-1)*2/3)/2, STR_LABEL);
#else
    mvaddstr(STD_SCR_START_Y, (COLS-sizeof(STR_LABEL)-1)/2, STR_LABEL);
#endif
    attroff(A_REVERSE);
    move(++g_cur_pos_y, ++g_cur_pos_x);
    refresh();
}

G_STATUS login(void)
{    
    WINDOW *login_win = newwin(LOGIN_WIN_LINES, LOGIN_WIN_COLS, LOGIN_WIN_START_Y, LOGIN_WIN_START_X);
    int cur_pos_y = 1, cur_pos_x = 1;
    box(login_win, ACS_VLINE, ACS_HLINE);    
    
#ifdef __CHINESE
    mvwaddstr(login_win, cur_pos_y++, (LOGIN_WIN_COLS-(sizeof(STR_LOGIN)-1)*2/3)/2, STR_LOGIN);
#else
    mvwaddstr(login_win, cur_pos_y++, (LOGIN_WIN_COLS-sizeof(STR_LOGIN)-1)/2, STR_LOGIN);
#endif
    mvwaddstr(login_win, cur_pos_y++, cur_pos_x, STR_LOGIN_USER);
    mvwaddstr(login_win, cur_pos_y, cur_pos_x, STR_LOGIN_PASSWORD);
    cur_pos_y = 2;
    cur_pos_x = 1 + sizeof(STR_LOGIN_USER);
    wmove(login_win, cur_pos_y, cur_pos_x);  
    wrefresh(login_win);

    //input user name
    char user_name[LOGIN_WIN_USER_NAME_SIZE];
    cur_pos_y = 2;
    cur_pos_x = 1 + sizeof(STR_LOGIN_USER);
    wmove(login_win, cur_pos_y, cur_pos_x);
    wrefresh(login_win);    
    wgetnstr(login_win, user_name, LOGIN_WIN_USER_NAME_SIZE-1);
    do
    {
        snprintf(g_conf_file, CONF_FILE_SIZE, "./.%s.conf", user_name);
        if(0 == access(g_conf_file, F_OK)) //if exist
        {
            break;
        }
        win_disp(login_win, g_err_info[STR_ERR_USER_NOT_EXIST]);
        mvwaddstr(login_win, cur_pos_y, cur_pos_x, LOGIN_WIN_EMPTY_STR);
        wmove(login_win, cur_pos_y, cur_pos_x);
        wrefresh(login_win);
        wgetnstr(login_win, user_name, LOGIN_WIN_USER_NAME_SIZE-1);
    }while(1);

    //get password in the conf file
    g_conf_file_fp = fopen(g_conf_file, "r");
    if(NULL == g_conf_file_fp)
    {
        delwin(login_win);
        endwin();
        DISP_ERR(g_err_info[STR_ERR_CONF_FILE]);
        return STAT_ERR;
    }
    if(NULL == fgets(g_buf, BUF_SIZE, g_conf_file_fp))
    {
        delwin(login_win);
        endwin();
        DISP_ERR(g_err_info[STR_ERR_CONF_FILE]);
        return STAT_ERR;
    }
        
    if((g_buf[0] != 'p') || (g_buf[1] != 'a') || (g_buf[2] != 's') || 
        (g_buf[3] != 's') || (g_buf[4] != 'w') || (g_buf[5] != 'o') || 
        (g_buf[6] != 'r') || (g_buf[7] != 'd') || (g_buf[8] != '='))
    {
        delwin(login_win);
        endwin();
        DISP_ERR(g_err_info[STR_ERR_GET_PASSWORD]);
        return STAT_ERR;
    }
    
    char correct_password[LOGIN_WIN_PASSWORD_SIZE];
    char *ptr = &g_buf[9], *tmp_ptr = correct_password;
    while((*ptr != '\n') && (*ptr != '\0'))
    {
        *tmp_ptr++ = *ptr++; //it may overflow if password is too long in conf file
    }
    tmp_ptr = '\0';
    fclose(g_conf_file_fp);

    //input password
    char password[LOGIN_WIN_PASSWORD_SIZE];
    cur_pos_y = 3;
    cur_pos_x = 1 + sizeof(STR_LOGIN_PASSWORD);
    wmove(login_win, cur_pos_y, cur_pos_x);
    wrefresh(login_win);
    noecho();
    keypad(login_win, true);
    int ch, i;
    tmp_ptr = password;
    do
    {
        i = 0;
        while(1)
        {
            ch = wgetch(login_win);
            if((ch >= KEY_CODE_YES) && (ch < KEY_BACKSPACE))
                continue;
            else if(ch > KEY_BACKSPACE)
                continue;
            else if(KEY_BACKSPACE == ch)
            {
                mvwaddch(login_win, cur_pos_y, --cur_pos_x, ' ');
                i--;
            }
            else if(13 == ch) //enter key
            {
                break;
            }
            else
            {
                if(i >= (LOGIN_WIN_PASSWORD_SIZE-1))
                    continue;
                waddch(login_win, '*');
                cur_pos_x++;
                tmp_ptr[i++] = (char)ch;
            }
            wmove(login_win, cur_pos_y, cur_pos_x);
        }

        tmp_ptr[i] = '\0';
        if(0 == strcmp(correct_password, password))
        {
            break;
        }
        win_disp(login_win, g_err_info[STR_ERR_PASSWORD_ERR]);
        cur_pos_x = 1 + sizeof(STR_LOGIN_PASSWORD);
        mvwaddstr(login_win, cur_pos_y, cur_pos_x, LOGIN_WIN_EMPTY_STR);
        wmove(login_win, cur_pos_y, cur_pos_x);
        //wrefresh(login_win); //It will auto refresh when the next time of using wgetch
    }while(1);
    echo();
    
    delwin(login_win);
    touchline(stdscr, LOGIN_WIN_START_Y, LOGIN_WIN_LINES);
    refresh();
    return STAT_OK;
}

void win_disp(WINDOW *win, const char *ptr)
{    
    WINDOW *tmp_win = newwin(LINES, COLS, STD_SCR_START_Y, STD_SCR_START_X);
    box(tmp_win, '*', '*');        

    int len = strlen(ptr);
    if(len < sizeof(STR_ANY_KEY)) 
    {
        len = sizeof(STR_ANY_KEY);
    }
    
    int tmp_pos_y = LINES / 2 - 1;
#ifdef __CHINESE
    int tmp_pos_x = (COLS - len*2/3) / 2;
#else
    int tmp_pos_x = (COLS - len) / 2;
#endif    
    mvwaddstr(tmp_win, tmp_pos_y++, tmp_pos_x, ptr);
    mvwaddstr(tmp_win, tmp_pos_y, tmp_pos_x, STR_ANY_KEY);
    wrefresh(tmp_win);
    wgetch(tmp_win);
    delwin(tmp_win);
    touchwin(stdscr);
    refresh();
    touchwin(win);
    wrefresh(win);
}

