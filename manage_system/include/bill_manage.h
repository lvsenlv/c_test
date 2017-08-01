/*************************************************************************
	> File Name: bill_manage.h
	> Author: lvsenlv
	> Mail: lvsen46000@163.com
	> Created Time: 2017年07月24日 星期一 10时08分36秒
 ************************************************************************/

#ifndef __BILL_MANAGE_H
#define __BILL_MANAGE_H

#include "common.h"


/*************************************************************************
                            about window
 ************************************************************************/

#include <ncurses.h>

#define BUF_SIZE                            256
#define CONF_FILE_SIZE                      64

#if __CHINESE
//string
#define STR_LABEL                           "管理系统"
#define STR_LOGIN                           "登录"
#define STR_LOGIN_USER                      "用户名 :"
#define STR_LOGIN_PASSWORD                  "密码   :"
#define STR_LOGIN_USER_NOT_EXIST            "用户不存在"
#define STR_ANY_KEY                         "按任意键继续"
#else
#define STR_LABEL                           "Management System"
#define STR_LOGIN                           "Login"
#define STR_LOGIN_USER                      "User :"
#define STR_LOGIN_PASSWORD                  "password :"
#define STR_LOGIN_USER_NOT_EXIST            "The user does not exsit"

#define STR_ANY_KEY                         "Press any key to continue"
#endif

//standard screen
#define STD_SCR_START_Y                     0
#define STD_SCR_START_X                     0

//login win
#define LOGIN_WIN_LINES                     (5)
#define LOGIN_WIN_COLS                      (36)
#define LOGIN_WIN_START_Y                   ((LINES - LOGIN_WIN_LINES) / 2)
#define LOGIN_WIN_START_X                   ((COLS - LOGIN_WIN_COLS)   / 2)
#define LOGIN_WIN_USER_NAME_SIZE            19 //real size if 18 because of endding with '\0'
#define LOGIN_WIN_PASSWORD_SIZE             19 //real size if 18 because of endding with '\0'
//the size of LOGIN_WIN_EMPTY_STR is user name size or password size
#define LOGIN_WIN_EMPTY_STR                 "                  "

typedef enum {
    STR_ERR_USER_NOT_EXIST = 0,
    STR_ERR_CONF_FILE,
    STR_ERR_GET_PASSWORD,
    STR_ERR_PASSWORD_ERR,
}STR_ERR;

#if __CHINESE
char *g_err_info[] = {
    "用户不存在",
    "读取配置文件失败或配置文件损坏",
    "获取密码失败，请检查配置文件",
    "密码错误",
};
#else
char *g_err_info[] = {
    "The user does not exsit",    
    "Failed to read conf file or conf file corrupted",
    "Failed to get password, please check the conf file",
    "Password error",
};
#endif

void draw_std_screen(void);
G_STATUS login(void);
void win_disp(WINDOW *win, const char *ptr);

#endif

