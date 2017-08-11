/*************************************************************************
	> File Name: control.h
	> Author: lvsenlv
	> Mail: lvsen46000@163.com
	> Created Time: 2017年08月09日 星期三 08时49分29秒
 ************************************************************************/

#ifndef __CONTROL_H
#define __CONTROL_H

#include "common.h"

#define CTL_MENU_FUNC_NUM                   5

#ifdef __LINUX
#include <ncurses.h>
#define CTL_ExitConsole()                   endwin()
#define CTL_MakeCursorInvis()               {move(LINES-1, COLS-1);refresh();}

#elif defined __WINDOWS
#include <conio.h>
#define CTL_ExitConsole()                   exit(0)
#endif

void CTL_InitConsole(void);
G_STATUS CTL_ChooseLanguage(void);
void CTL_DrawStdScreen(void);
G_STATUS CTL_ChooseFunc(char *pFunc);
G_STATUS CTL_ShowInstruction(void);
G_STATUS CTL_GetFileName(char *pFileName);


#endif

