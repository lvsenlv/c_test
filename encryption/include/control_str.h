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
    CTL_STR_MENU_FUNC6,
    CTL_STR_INPUT_FILE_NAME,
    CTL_STR_INPUT_FILE_NAME_EG,
    CTL_STR_INPUT,
    CTL_STR_RETRY,
    CTL_STR_BACK,
    CTL_STR_FILE_NOT_EXIST,
    CTL_STR_INPUT_PASSWORD,
    CTL_STR_PASSWORD_TOO_SHORT,
    CTL_STR_INPUT_PASSWORD_CONFIRM,
    CTL_STR_PASSWORD_NOT_MATCH,
    CTL_STR_ENTER_KEY_GO_BACK,
}CTL_STR;

static char *pEnStr[] = {
    "Press Esc to exit project",
    "Encryption System",
    "Press Esc to exit project | Version 1.0.0 | Copyright 2017-2017",
    "1. Instruction",
    "2. Encrypt single file",
    "3. Encrypt folder",
    "4. Decrypt single file",
    "5. Decrypt folder",
    "6. Change language",    
    "Please input the file name with full path",
    "E.g, C:/User/Administrator/file.txt",
    "Input: ",
    "[Retry]",
    "[Back]",
    "The file does not exist",
    "Password: ",
    "Password too short, at least 8 bits",
    "Confirm password: ",
    "Two password do not match",
    "[ Enter key to go back ]",
};
    
static char *pChStr[] = {
    "按Esc键退出程序",
    "加密系统",
    "按Esc键退出程序 | 版本号 1.0.0 | Copyright 2017-2017",
    "1. 使用说明", 
    "2. 加密单个文件",
    "3. 加密文件夹",
    "4. 解密单个文件",
    "5. 解密文件夹",
    "6. 更改语言",       
    "请输入文件名，若不在当前文件夹则需完整路径",
    "例如, C:/User/Administrator/文件.txt",
    "输入: ",
    "[重试]",
    "[返回]",
    "此文件不存在",
    "密码：",
    "密码太短，至少8位",
    "确认密码：",
    "两次密码不匹配",
    "[ 按Enter键返回 ]",
};

static char *pEnInstruction[] = {
    "No more info temporarily",
    NULL,
};

static char *pChInstruction[] = {
    "数据无价，请认真阅读",
    "1. 此版本目前仅可用于Linux系统，所有功能均处于测试阶段；",
    "2. 本软件采用\"无存储\"式加密方法，即不存储用户密码，",
    "   软件会根据用户密码，生成加密因子进行加密，解密时同理，",
    "   因此，任意密码均可解密，但与加密密码不一致时，将得到损坏的文件，",
    "   故，请牢记您的密码，密码丢失将永久无法解密；",
    "3. 为保证数据的安全性，本软件仅在原先文件的基础上生成加密文件，",
    "   原先文件依旧存在，可通过新的加密文件，解密得到原先的文件，",
    "   建议用户完成加密后，手动将旧文件删除，否则解密时会将其覆盖，",
    "   同理，解密完成后，确认得到正确文件后，建议删除原先的加密文件，",
    "   用户可通过菜单下的对应选项，进行快速清理旧文件；",
    "",
    "温馨提示：",
    "   本软件可加密单个文件，即可针对不同文件使用不同的加密密码，",
    "   但不建议这么做，过多的密码易混淆且遗忘，易造成无法解密",
    "",
    "若有任何使用问题，请发送邮件至lvsen46000@163.com",
    NULL,
};


#endif
