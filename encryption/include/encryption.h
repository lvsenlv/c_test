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

#ifdef __CHINESE
#define STR_INPUT_FILE_NAME                 "请输入文件名（文件若不在当前文件夹，请输入完整路径）: \n"
#define STR_INPUT_PASSWORD                  "请输入加密秘钥： \n"

#define STR_ERR_MALLOC_BUF_SMALL            "错误：运行内存空间不足，请确保至少剩余1Mb的内存空间"
#define STR_ERR_MALLOC_BUF_MEDIUM           "错误：运行内存空间不足，请确保至少剩余10Mb的内存空间"
#define STR_ERR_MALLOC_BUF_LARGE            "错误：运行内存空间不足，请确保至少剩余100Mb的内存空间"
#define STR_ERR_READ_FILE_ERR               "错误：读取文件失败，请确保文件可读"
#define STR_ERR_PASSWORD_NULL               "错误：密码长度不能为0"
#define STR_ERR_CREATE_OPEN_ERR             "错误：无法创建或打开文件"
#define STR_ERR_WRITE_FILE_ERR              "错误：写入文件失败，请确保文件可写"
#define STR_ERR_INPUT_LEN_OUT_SIZE          "错误：输入长度超出限制"
#define STR_ERR_INPUT_NULL                  "错误：输入不能为空"
#define STR_ERR_GET_FILE_SIZE_ERR           "错误：获取文件大小失败"

#else //__CHINESE
#define STR_INPUT_FILE_NAME                 "Please input filename with full path: \n"
#define STR_INPUT_PASSWORD                  "Please input key: \n"

#define STR_ERR_MALLOC_BUF_SMALL            "Error: No enough running memory space, it needs 1Mb at least"
#define STR_ERR_MALLOC_BUF_MEDIUM           "Error: No enough running memory space, it needs 10Mb at least"
#define STR_ERR_MALLOC_BUF_LARGE            "Error: No enough running memory space, it needs 100Mb at least"
#define STR_ERR_READ_FILE_ERR               "Error: Fail to read file, make sure it is readable"
#define STR_ERR_PASSWORD_NULL               "Error: Length of key could not be null"
#define STR_ERR_CREATE_OPEN_ERR             "Error: Fail to create or open file"
#define STR_ERR_WRITE_FILE_ERR              "Error: Fail to write to file, make sure it is writeable"
#define STR_ERR_INPUT_LEN_OUT_SIZE          "Error: Input length is out of limit"
#define STR_ERR_INPUT_NULL                  "Error: Input could not be null"
#define STR_ERR_GET_FILE_SIZE_ERR           "Error: Fail to get file size"
#endif //__CHINESE

#endif

