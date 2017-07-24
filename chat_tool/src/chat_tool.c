/*************************************************************************
	> File Name: chat_tool.c
	> Author: 
	> Mail: 
	> Created Time: 2017年07月18日 星期二 15?43分33秒
 ************************************************************************/

//#if 0
#include "chat_tool.h"
#include <stdlib.h>
#include <unistd.h>
#include <locale.h>

WINDOW *g_input_win;
int g_cur_out_pos_y = OUTPUT_START_X;
int g_cur_out_pos_x = OUTPUT_START_Y;
int g_cur_in_pos_y = INPUT_START_Y;
int g_cur_in_pos_x = INPUT_START_X;

int main(void)
{   
    setlocale(LC_ALL,"");
    initscr();                  //start curses mode
    cbreak();                   //read all keys on keyboard but DELETE and CTRL
    nonl();                     //disable ENTER key as newline
    //noecho();                   //do not dispaly the char when input from keyboard
    keypad(stdscr, true);       //use some definiton such as KEY_... to manage some logical keys

    refresh();                  //clear screen here. It is typically used to make all actions effect   

    draw_std_screen();
    draw_input_box();

    char buf[64];
    wgetstr(g_input_win, buf);
    mvwaddstr(g_input_win, g_cur_in_pos_y+1, g_cur_in_pos_x, buf);
    wrefresh(g_input_win);

    sleep(5);
    delwin(g_input_win);
    endwin();
    return 0;
}

void draw_std_screen(void)
{ 
    //border('|', '|', '-', '-', '-', '-', '-', '-');
    char label[] = "Chatting Room";
    
    box(stdscr, ACS_VLINE, ACS_HLINE);
    attron(A_REVERSE);
    mvaddstr(OUTPUT_START_Y, (COLS-sizeof(label))/2, label);
    attroff(A_REVERSE);
    refresh();
}

void draw_input_box(void)
{
    if((OUTPUT_END_Y - INPUT_BOX_START_Y) <= 2)
    {   
        delwin(g_input_win);
        endwin();
        DISP_ERR("invalid size of input box");
        exit(-1);
    }
    
    g_input_win = newwin(INPUT_BOX_LINES, COLS-2, INPUT_BOX_START_Y, INPUT_BOX_START_X);
    box(g_input_win, '*', '*');
    keypad(g_input_win, true);
    wmove(g_input_win, INPUT_START_Y, INPUT_START_X);

    wrefresh(g_input_win);
}
//#endif

#if 0
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#define StartY 1
#define StartY 1
void initial();
int main()
{
   int x = StartY;
   int y = StartY;
   int ch;
   initial();
   box(stdscr,'|','-');
   attron(A_REVERSE);
   mvaddstr(0,20,"curses program");
   attroff(A_REVERSE);
   move(x,y);
   do{
      ch = getch();
      switch(ch)
      {
        case KEY_UP:
           --y;
           break;
            case KEY_DOWN: 
                ++y; 
                break;
            case KEY_RIGHT: 
                ++x; 
                break;
            case KEY_LEFT: 
                --x; 
                break;
            case ' ': 
                ++y;
                x=0;
                break;
            case '\t': 
                x+=7;
                break;
            case KEY_BACKSPACE: 
                mvaddch(y,--x,' ');
                break;
            case 27: 
                endwin(); 
                exit(1); 
            default: 
                addch(ch); 
                x++;
               break;
      }
      move(y,x);
   }while(1);
}

void initial()
{
 initscr();
 cbreak();
 nonl();
 noecho();
 intrflush(stdscr,false);
 keypad(stdscr,true);
 refresh();
}
#endif

#if 0
#include "chat_tool.h"
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>

FILE *g_hist_msg_fp = NULL;
FILE *g_msg_fp = NULL;
char g_buf[BUF_SIZE] = {0};

int main(void) 
{
    system("clear");

    g_hist_msg_fp = fopen(HISTORY_MESSAGE_FILE, "a+");
    if(!g_hist_msg_fp)
    {
        DISP_ERR("error in fopen");
        exit(-1);
    }

    g_msg_fp = fopen(MESSAGE_FILE, "a+");
    if(!g_msg_fp)
    {
        DISP_ERR("error in fopen");
        fclose(g_hist_msg_fp);
        exit(-1);
    }
    
    pthread_t pthread_id1, pthread_id2;
    void *pthread_ret = NULL;
	int ret = 0;
	
	ret = pthread_create(&pthread_id1, NULL, send_message, NULL);
	if(ret)
	{
		fprintf(stderr, "error in pthread_create : %s\n", strerror(ret));
		exit(-1);
	}

	ret = pthread_create(&pthread_id2, NULL, receive_message, NULL);
	if(ret)
	{
		fprintf(stderr, "error in pthread_create : %s\n", strerror(ret));
		exit(-1);
	}

	ret = pthread_join(pthread_id1, &pthread_ret);
	if(ret)
	{
		fprintf(stderr, "error in pthread_join: %s\n", strerror(ret));
		exit(-1);
	}

	ret = pthread_join(pthread_id2, &pthread_ret);
	if(ret)
	{
		fprintf(stderr, "error in pthread_join: %s\n", strerror(ret));
		exit(-1);
	}

    return 0;
}

void *receive_message(void *arg)
{

    return NULL;
}

void *send_message(void *arg)
{
    time_t ti;
    struct tm *tm;
    
    while(1)
    {
        ti = time(NULL);
        tm = localtime(&ti);
    }
    
    /*
    fprintf(g_log_file, "%4d-%02d-%02d %02d:%02d:%02d [%s] | [%s][%d] : ", \
        tm->tm_year+1900, tm->tm_mon, tm->tm_mday, tm->tm_hour, tm->tm_min, \
        tm->tm_sec, *(log_str+level), __func__, __LINE__); 
        */
    return NULL;
}
#endif
