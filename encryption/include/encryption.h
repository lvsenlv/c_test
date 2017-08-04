/*************************************************************************
	> File Name: encryption.h
	> Author: lvsenlv
	> Mail: lvsen46000@163.com
	> Created Time: 2017年08月03日 星期四 08时38分01秒
 ************************************************************************/

#ifndef __ENCRYPTION_H
#define __ENCRYPTION_H

#include "common.h"

#define PASSWORD_LENGHT                     18
#define ENCRYPT_FILE_SUFFIX_NAME            ".encrypt"
#define DECRYPT_FILE_SUFFIX_NAME            ".decrypt"

#define BUF_SIZE_SMALL                      ((uint32_t)(1024*1024))         //1Mb
#define BUF_SIZE_MEDIUM                     ((uint32_t)(1024*1024*10))      //10Mb
#define BUF_SIZE_LARGE                      ((uint32_t)(1024*1024*100))     //100Mb

#define STR_NO_FREE_MEM_SPACE \
        "Fail to get free memory space, confirm you have enough free memory space"

G_STATUS Encrypt_KB_File(const char *ptr, const char *pPassword);
G_STATUS Encrypt_MB_File(const char *ptr, const char *pPassword);
G_STATUS Encrypt_GB_File(const char *ptr, const char *pPassword);

G_STATUS Decrypt_KB_File(const char *ptr, const char *pPassword);


#endif

