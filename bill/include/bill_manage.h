/*************************************************************************
	> File Name: bill_manage.h
	> Author: lvsenlv
	> Mail: lvsen46000@163.com
	> Created Time: 2017年07月24日 星期一 10时08分36秒
 ************************************************************************/

#ifndef __BILL_MANAGE_H
#define __BILL_MANAGE_H

#include "common.h"

#define CONF_FILE                           "bill_files/conf.lv"
#define USERNAME_SIZE                       19 //It's actually 18
#define PASSWORD_SIZE                       19 //It's actually 18
#define BUF_SIZE                            512

#ifdef __LINUX
#define CLEAR                               {system("clear");}
#elif defined __WINDOWS        
#define CLEAR                               {system("cls");}
#else
#error "You need to define __LINUX or __WINDOWS to determine the platform"
#endif
#define CLEAR_IN_BUF                        {while(getchar() != '\n');}
#define WAIT_FOR_KEY                        CLEAR_IN_BUF

#define STR_ANY_KEY                         "请按回车键继续......"
#define STR_INPUT                           "请输入: "
#define STR_INPUT_USERNAME                  "请输入用户名: "
#define STR_INPUT_PASSWOED                  "请输入密码: "
#define STR_RETRY                           "重试"
#define STR_BACK_HOME_PAGE                  "返回主页"
#define STR_LOGIN_SUCCESS                   "登录成功"

#define STR_ERR_ILLGAL_INPUT                "输入不合法"
#define STR_ERR_CONF_FILE_CORRUPTION        "配置文件损坏"
#define STR_ERR_USER_NAME_OUT_SIZE          "用户名太长"
#define STR_ERR_PASSWORD_OUT_SIZE           "密码太长"
#define STR_ERR_USER_NAME_NOT_EXIST         "用户不存在"
#define STR_ERR_PASSWORD_ERR                "密码错误"

char *g_home_page[] = {
    "欢迎进入管理系统!",
    "1. 登录现有账户",
    "2. 创建新的账户",
    "3. 删除现有账户",
    "4. 退出",
    NULL,
};

typedef enum {
    FLAG_DO_NOTHING = 0,
    FLAG_LOGIN_EXISTTING_ACCOUNT,
    FLAG_CREATE_NEW_ACCOUNT,
    FLAG_DELETE_EXISTTING_ACCOUNT,
    FLAG_EXIST,
    FLAG_BACK_HOME_PAGE,
}G_FLAG;


//Storage format: #TY2017.08.01.16:30:20T#O333O#EdevelopE#R1024R#I512I#
//Parse: time=2017.08.01.16:30:20 ouput=333 entry_ptr=develop remain=1024 input=512
typedef struct bill_info {
    int time[6];
    float output;
    char *entry_ptr;
    float remain;
    float input;
}bill_info_t, *bill_info_pt;


typedef struct bill_link_list {
    bill_info_pt info;
    struct bill_link_list *next;
}bill_link_list_t, *bill_link_list_pt;

G_STATUS disp_home_page(void);
G_STATUS login(void);

#endif

