/*************************************************************************
	> File Name: control_str.h
	> Author: 
	> Mail: 
	> Created Time: 2017年08月10日 星期四 13时42分50秒
 ************************************************************************/

#ifndef __CONTROL_STR_H
#define __CONTROL_STR_H

#define CTL_STR_CHOOSE_LANG_ENGLISH         "English"
#define CTL_STR_CHOOSE_LANG_CHINESE         "中文"
#define CTL_STR_NULL                        "                            "

typedef enum CTL_STR_INFO
{
    CTL_STR_EXIT = 0,
    CTL_STR_LABEL,
    CTL_STR_END_LINE,
}CTL_STR;


static char *g_pEnStr[] = {
    "Press Esc to exit",
    "Encryption System",
    "Press Esc to exit | Encryption System | Version 1.0.0 | Copyright lvsenlv",
};
    
static char *g_pChStr[] = {
    "按Esc键退出",
    "加密系统",
    "按Esc键退出 | 加密系统 | 版本号 1.0.0 | 版权 lvsenlv",
};


#endif

