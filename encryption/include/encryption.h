/*************************************************************************
	> File Name: encryption.h
	> Author: lvsenlv
	> Mail: lvsen46000@163.com
	> Created Time: 2017年08月03日 星期四 08时38分01秒
 ************************************************************************/

#ifndef __ENCRYPTION_H
#define __ENCRYPTION_H

#include "common.h"

#define FILE_NAME_LENGTH                    128
#define PASSWORD_LENGHT                     18
#define ENCRYPT_FILE_SUFFIX_NAME            ".encrypt"
#define DECRYPT_FILE_SUFFIX_NAME            ".decrypt"

#define BUF_SIZE_SMALL                      ((uint32_t)(1024*1024))         //1Mb
#define BUF_SIZE_MEDIUM                     ((uint32_t)(1024*1024*10))      //10Mb
#define BUF_SIZE_LARGE                      ((uint32_t)(1024*1024*100))     //100Mb


#define STR_INPUT_FILE_NAME                 "请输入文件名（文件若不在当前文件夹，请输入完整路径）: \n"
#define STR_INPUT_PASSWORD                  "请输入加密秘钥： \n"

#define STR_ERR_MALLOC_BUF_SMALL            "错误：运行内存空间不足，请确保至少剩余2Mb的内存空间"
#define STR_ERR_MALLOC_BUF_MEDIUM           "错误：运行内存空间不足，请确保至少剩余20Mb的内存空间"
#define STR_ERR_MALLOC_BUF_LARGE            "错误：运行内存空间不足，请确保至少剩余100Mb的内存空间"
#define STR_ERR_READ_FILE_ERR               "错误：读取文件失败，请确保文件可读"
#define STR_ERR_PASSWORD_NULL               "错误：密码长度为0"
#define STR_ERR_CREATE_OPEN_ERR             "错误：无法创建或打开文件"
#define STR_ERR_WRITE_FILE_ERR              "错误：写入文件失败，请确保文件可写"
#define STR_ERR_INPUT_LEN_OUT_SIZE          "错误：输入长度超出限制"
#define STR_ERR_INPUT_NULL                  "错误：输入不能为空"

G_STATUS InputFileName(char *pFileName);
G_STATUS InputPassword(char *pPassword);
G_STATUS Encrypt_KB_File(const char *pFileName, const char *pPassword);
G_STATUS Encrypt_MB_File(const char *pFileName, const char *pPassword);
G_STATUS Encrypt_GB_File(const char *pFileName, const char *pPassword);

G_STATUS Decrypt_KB_File(const char *pFileName, const char *pPassword);


#endif

