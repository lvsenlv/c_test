/*************************************************************************
	> File Name: bill_manage.h
	> Author: lvsenlv
	> Mail: lvsen46000@163.com
	> Created Time: 2017年07月24日 星期一 10?08分36秒
 ************************************************************************/

#ifndef __BILL_MANAGE_H
#define __BILL_MANAGE_H

#include "common.h"


/*************************************************************************
                            about window
 ************************************************************************/

#include <ncurses.h>

#define BUF_SIZE                            64

#if __CHINESE
//string
#define STR_LABEL                           "管理系统"
#define STR_LOGIN                           "登录"
#define STR_LOGIN_USER                      "用户名 :"
#define STR_LOGIN_PASSWORD                  "密码   :"
#define STR_LOGIN_USER_NOT_EXIST            "此用户不存在 :"
#define STR_ANY_KEY                         "按任意键继续"
#else
#define STR_LABEL                           "Management System"
#define STR_LOGIN                           "Login"
#define STR_LOGIN_USER                      "User :"
#define STR_LOGIN_PASSWORD                  "password :"
#define STR_LOGIN_USER_NOT_EXIST            "The user does not exsit :"

#define STR_ANY_KEY                         "press any key to continue"
#endif

//standard screen
#define STD_SCR_START_Y                     0
#define STD_SCR_START_X                     0

//login win
#define LOGIN_WIN_LINES                     (5)
#define LOGIN_WIN_COLS                      (40)
#define LOGIN_WIN_START_Y                   ((LINES - LOGIN_WIN_LINES) / 2)
#define LOGIN_WIN_START_X                   ((COLS - LOGIN_WIN_COLS)   / 2)
#define LOGIN_WIN_USER_NAME_SIZE            18
#define LOGIN_WIN_PASSWORD_SIZE             18


void draw_std_screen(void);
void login(void);
void win_disp(const char *ptr);

#endif

