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
    CTL_STR_ESC_EXIT = 0,
    CTL_STR_LABEL,
    CTL_STR_END_LINE,
    CTL_STR_MENU_FUNC1,
    CTL_STR_MENU_FUNC2,
    CTL_STR_MENU_FUNC3,
    CTL_STR_MENU_FUNC4,
    CTL_STR_MENU_FUNC5,
    CTL_STR_INPUT_FILE_NAME,
    CTL_STR_INPUT_FILE_NAME_EG,
    CTL_STR_INPUT,
    CTL_STR_RETRY,
    CTL_STR_BACK,
    CTL_STR_ERR_FILE_NOT_EXIST,
}CTL_STR;


static char *pEnStr[] = {
    "Press Esc to exit project",
    "Encryption System",
    "Press Esc to exit project | Version 1.0.0 | ©2017-2017 lvsenlv",
    "1. Encrypt single file",
    "2. Encrypt folder",
    "3. Decrypt single file",
    "4. Decrypt folder",
    "5. Instruction",
    "Please input the file name with full path",
    "E.g, C:/User/Adminstrator/file.txt",
    "Input: ",
    "[Retry]",
    "[Back]",
    "Error: The file does not exist",
};
    
static char *pChStr[] = {
    "按Esc键退出程序",
    "加密系统",
    "按Esc键退出程序 | 版本号 1.0.0 | ©2017-2017 lvsenlv",
    "1. 加密单个文件",
    "2. 加密文件夹",
    "3. 解密单个文件",
    "4. 解密文件夹",
    "5. 使用说明",
    "请输入文件名，若不在当前文件夹则需完整路径",
    "例如, C:/User/Adminstrator/文件.txt",
    "输入: ",
    "[重试]",
    "[返回]",
    "错误：此文件不存在",
};

static char *pEnInstruction[] = {
    "No more info temporarily",
    NULL,
};

static char *pChInstruction[] = {
    "暂无说明",
    NULL,
};


#endif

