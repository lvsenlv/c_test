/*************************************************************************
	> File Name: main.c
	> Author: lvsenlv
	> Mail: lvsen46000@163.com
	> Created Time: 2017年08月09日 星期三 08时48分52秒
 ************************************************************************/

#include "common.h"
#include "control.h"

int main(void)
{
    CTL_InitConsole();
    if(CTL_ChooseLanguage() != STAT_OK)
    {
        CTL_ExitConsole();
        return 0;
    }
    CTL_ShowMenu();

    while(1);
    CTL_ExitConsole();
    return 0;
}


