/*************************************************************************
	> File Name: control.h
	> Author: lvsenlv
	> Mail: lvsen46000@163.com
	> Created Time: 2017年08月09日 星期三 08时49分29秒
 ************************************************************************/

#ifndef __CONTROL_H
#define __CONTROL_H

#include "common.h"

#ifdef __LINUX
#include <ncurses.h>
#define CTL_ExitConsole()                   endwin()
#define CTL_MakeCursorInvis()               {move(LINES-1, COLS-1);refresh();}

#elif defined __WINDOWS
#include <conio.h>
#define CTL_ExitConsole()                   exit(0)
#endif

#define CTL_STR_CHOOSE_LANG_ENGLISH         "English"
#define CTL_STR_CHOOSE_LANG_CHINESE         "中文"

typedef enum CTL_STR_INFO
{
    CTL_STR_EXIT = 0,

}CTL_STR;

void CTL_InitConsole(void);
G_STATUS CTL_ChooseLanguage(void);

G_STATUS CTL_ShowMenu(void);


#endif

