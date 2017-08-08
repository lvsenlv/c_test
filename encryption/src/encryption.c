/*************************************************************************
	> File Name: encryption.c
	> Author: lvsenlv
	> Mail: lvsen46000@163.com
	> Created Time: 2017年08月03日 星期四 08时37分45秒
 ************************************************************************/

#ifdef __LINUX
#define _FILE_OFFSET_BITS 64 //make sure st_size is 64bits instead of 32bits
#endif

#include "encryption.h"
#include <string.h>
#include <sys/stat.h>

static char g_buf[BUF_SIZE];
static FILE *g_fp = NULL;
__IO static int64_t g_FileSize = 0;

int main(void)
{
    char FileName[FILE_NAME_LENGTH];
    char password[PASSWORD_LENGHT];

    if(InputFileName(FileName) != STAT_OK)
        return -1;
        
    g_fp = fopen(FileName, "rb");
    if(NULL == g_fp)
    {
#ifdef __CHINESE        
        DISP_ERR_PLUS("错误：打开文件 \"%s\" 失败 \n请检查文件是否存在以及路径是否正确 \n", FileName);
#else
        DISP_ERR_PLUS("Error: Fail to open \"%s\" \nPlease make sure it does exist and path is available", FileName);
#endif
        return -1;
    }
    
    if(InputPassword(password) != STAT_OK)
        return -1;
    
#ifdef __LINUX
    fseeko(g_fp, 0, SEEK_END);
    g_FileSize = ftello(g_fp);
#elif defined __WINDOWS
    _fseeki64(g_fp, 0, SEEK_END);
    g_FileSize = _ftelli64(g_fp);
#endif
    Encrypt_KB_File(FileName, password);
    fclose(g_fp);
    g_fp = NULL;
    return 0;
}

G_STATUS InputFileName(char *pFileName)
{
    char ch, flag = 0;
    int i = 0;    

    memset(pFileName, '\0', FILE_NAME_LENGTH);
    CLEAR;
    DISP(STR_INPUT_FILE_NAME);
    ch = getchar();
    while(1)
    {
        if('\n' == ch)
            break;
        pFileName[i++] = ch;
        if(FILE_NAME_LENGTH == i)
        {
            flag = 1;
            CLEAR_IN_BUF;
            break;
        }
        ch= getchar();
    }
    
    if(flag)
    {
        return STAT_ERR;
        DISP_ERR(STR_ERR_INPUT_LEN_OUT_SIZE);
    }
    
    if(0 == i)
    {
        DISP_ERR(STR_ERR_INPUT_NULL);
        return STAT_ERR;            
    }

    return STAT_OK;
}

G_STATUS InputPassword(char *pPassword)
{
    char ch, flag;
    int i;
    char TmpBuf[2];

    while(1)
    {
        flag = 0;
        i = 0;
        memset(pPassword, '\0', PASSWORD_LENGHT);
        CLEAR;
        DISP(STR_INPUT_PASSWORD);
        ch = getchar();
        while(1)
        {
            if('\n' == ch)
                break;
            pPassword[i++] = ch;
            if(PASSWORD_LENGHT == i)
            {
                flag = 1;
                CLEAR_IN_BUF;
                break;
            }
            ch= getchar();
        }
        
        if(flag)
        {
            DISP_ERR(STR_ERR_INPUT_LEN_OUT_SIZE);
            return STAT_ERR;
        }  
        
        if(0 == i)
        {
            DISP_ERR(STR_ERR_INPUT_NULL);
            return STAT_ERR;            
        }

#ifdef __CHINESE
        DISP("警告：请再次确认你的秘钥是否为：\n%s \n", pPassword);
        DISP("1. 继续：请输入 y 或 Y 并回车 \n");
        DISP("2. 重新输入：请输入 r 或 R 并回车 \n");
        DISP("3. 退出程序：请输入其他按键并回车 \n");
#else
        DISP("Warning: Confirm your key is: \n%s \n", pPassword);
        DISP("1. Continue: Press y or Y and Enter \n");
        DISP("2. Retry: Press r or R and Enter \n");
        DISP("3. Exit: Press other keys and Enter \n");
#endif
        i = 0;
        flag = 0;
        ch = getchar(); 
        while(1)
        {
            if('\n' == ch)
                break;
            TmpBuf[i++] = ch;
            if(i > 1)
            {
                flag = 1;
                CLEAR_IN_BUF;
                break;
            }
            ch= getchar();
        }
        
        if(flag)
            return STAT_ERR;
        
        if(('Y' == TmpBuf[0]) || ('y' == TmpBuf[0]))
            break;
        else if(('R' == TmpBuf[0]) || ('r' == TmpBuf[0]))
            continue;
        else
            return STAT_ERR;
        
    }
    
    return STAT_OK;
}

G_STATUS GetFileSize(const char *pFileName)
{
    struct stat FileInfo;
    
    return STAT_OK;
}


G_STATUS Encrypt_KB_File(const char *pFileName, const char *pPassword)
{
    if((0 == g_FileSize) || (g_FileSize > BUF_SIZE_SMALL)) //Do not handle this circumstance
    {
        return STAT_OK;
    }

    //read data from original file
    uint8_t *pData = NULL;
    pData = (uint8_t *)malloc(sizeof(uint8_t) * BUF_SIZE_SMALL);
    if(NULL == pData)
    {
        DISP_ERR(STR_ERR_MALLOC_BUF_SMALL);
        return STAT_ERR;
    }
    
    memset(pData, 0, sizeof(uint8_t)*BUF_SIZE_SMALL);
    fseek(g_fp, 0, SEEK_SET);
    uint64_t size = 0;
    size = fread(pData, sizeof(uint8_t), g_FileSize, g_fp);
    if(size != g_FileSize)
    {
        DISP_ERR(STR_ERR_READ_FILE_ERR);
        free(pData);
        return STAT_ERR;
    }

/*************************************************************************
                   Core codes of encryption algorithm
************************************************************************/

    //get encrypt factor
    uint32_t EncyptFactor = 0;
    uint32_t PasswordLenght = 0;
    const char *pTmpPassword = pPassword;
    while(*pTmpPassword != '\0')
    {
        EncyptFactor += *pTmpPassword++;
        PasswordLenght++;
    }
    if(0 == PasswordLenght)
    {
        DISP_ERR(STR_ERR_PASSWORD_NULL);
        free(pData);
        return STAT_ERR;
    }
    EncyptFactor %= 8;
    if(0 == EncyptFactor)
        EncyptFactor = 1;

    uint8_t *pTmp, *pTmp2;
    uint8_t TmpData;
    uint32_t i = 0;

    //encrypt proccess 1
    pTmp = pData;
    for(i = 0; i < g_FileSize; i++)
    {
        TmpData = 0;
        TmpData = *pTmp & (0xFF >> (8-EncyptFactor));
        TmpData <<= 8 - EncyptFactor;
        TmpData |= *pTmp >> ((uint8_t)EncyptFactor);
        *pTmp++ = TmpData;
    }    

    //encrypt proccess 2
    if(g_FileSize > PasswordLenght)
    {
        uint8_t *pBackupData = (uint8_t *)malloc(PasswordLenght * sizeof(uint8_t));
        if(NULL == pBackupData)
        {
            DISP_ERR(STR_ERR_MALLOC_BUF_SMALL);
            free(pData);
            return STAT_ERR;
        }
        uint32_t RestDataCount = 0;

        pTmp2 = pBackupData;
        pTmp = pData + g_FileSize - 1;
        for(i = 0; i < PasswordLenght; i++)
        {
            *pTmp2++ = *pTmp--;
        }

        RestDataCount = g_FileSize - PasswordLenght;
        pTmp2 = pData + g_FileSize - 1;
        pTmp = pData + RestDataCount - 1;
        for(i = 0; i < RestDataCount; i++)
        {
            *pTmp2-- = *pTmp--;
        }

        pTmp2 = pData;
        pTmp = pBackupData;
        for(i = 0; i < PasswordLenght; i++)
        {
            *pTmp2++ = *pTmp++;
        }

        free(pBackupData);
    }
    else
    {
        pTmp = pData;
        pTmpPassword = pPassword;
        for(i = 0; i < g_FileSize; i++)
        {
            *pTmp ^= *pTmpPassword;
            pTmp++;
            pTmpPassword++;
        }
    }

    //encrypt proccess 3
    if(g_FileSize > 256)
    {
        pTmp = pData;
        pTmp2 = pData + g_FileSize - 1;
        pTmpPassword = pPassword;
        for(i = 0; i < PasswordLenght; i++)
        {
            TmpData = *pTmp2;
            *pTmp2 = pTmp[(uint32_t)(*pTmpPassword)];
            pTmp[(uint32_t)(*pTmpPassword)] = TmpData;
            pTmp2--;
            pTmpPassword++;
        }
    }

    //write encyption data to new file
    snprintf(g_buf, sizeof(g_buf), "%s%s", pFileName, ENCRYPT_FILE_SUFFIX_NAME);
    FILE *fp = fopen(g_buf, "wb+");
    if(NULL == fp)
    {
        DISP_ERR_PLUS("%s%s \n", STR_ERR_CREATE_OPEN_ERR, g_buf);
        free(pData);
        fclose(fp);
        return STAT_ERR;
    }
    
    size = fwrite(pData, sizeof(uint8_t), g_FileSize, fp);
    if(size != g_FileSize)
    {
        DISP_ERR(STR_ERR_WRITE_FILE_ERR);
        free(pData);
        fclose(fp);
        return STAT_ERR;
    }

    free(pData);
    fclose(fp);
    return STAT_OK;
}

G_STATUS Encrypt_MB_File(const char *pFileName, const char *pPassword)
{
    return STAT_OK;
}

G_STATUS Encrypt_GB_File(const char *pFileName, const char *pPassword)
{
    return STAT_OK;
}

G_STATUS Decrypt_KB_File(const char *pFileName, const char *pPassword)
{
    if((0 == g_FileSize) || (g_FileSize > BUF_SIZE_SMALL)) //Do not handle this circumstance
    {
        return STAT_OK;
    }

    //read data from original file
    uint8_t *pData = NULL;
    pData = (uint8_t *)malloc(sizeof(uint8_t) * BUF_SIZE_SMALL);
    if(NULL == pData)
    {
        DISP_ERR(STR_ERR_MALLOC_BUF_SMALL);
        return STAT_ERR;
    }
    
    memset(pData, 0, sizeof(uint8_t)*BUF_SIZE_SMALL);
    fseek(g_fp, 0, SEEK_SET);
    uint64_t size = 0;
    size = fread(pData, sizeof(uint8_t), g_FileSize, g_fp);
    if(size != g_FileSize)
    {
        DISP_ERR(STR_ERR_READ_FILE_ERR);
        free(pData);
        return STAT_ERR;
    }

/*************************************************************************
                   Core codes of encryption algorithm
************************************************************************/

    //get encrypt factor
    uint32_t EncyptFactor = 0;
    uint32_t PasswordLenght = 0;
    const char *pTmpPassword = pPassword;
    while(*pTmpPassword != '\0')
    {
        EncyptFactor += *pTmpPassword++;
        PasswordLenght++;
    }
    if(0 == PasswordLenght)
    {
        DISP_ERR(STR_ERR_PASSWORD_NULL);
        free(pData);
        return STAT_ERR;
    }
    EncyptFactor %= 8;
    if(0 == EncyptFactor)
        EncyptFactor = 1;

    uint8_t *pTmp, *pTmp2;
    uint8_t TmpData = 0;
    uint32_t i = 0;

    //encrypt proccess 3
    if(g_FileSize > 256)
    {
        pTmp = pData;
        pTmp2 = pData + g_FileSize - 1;
        pTmpPassword = pPassword;
        for(i = 0; i < PasswordLenght; i++)
        {
            TmpData = *pTmp2;
            *pTmp2 = pTmp[(uint32_t)(*pTmpPassword)];
            pTmp[(uint32_t)(*pTmpPassword)] = TmpData;
            pTmp2--;
            pTmpPassword++;
        }
    }

    //encrypt proccess 2
    if(g_FileSize > PasswordLenght)
    {
        uint8_t *pBackupData = (uint8_t *)malloc(PasswordLenght * sizeof(uint8_t));
        if(NULL == pBackupData)
        {
            DISP_ERR(STR_ERR_MALLOC_BUF_SMALL);
            free(pData);
            return STAT_ERR;
        }
        uint32_t RestDataCount = 0;

        pTmp2 = pBackupData;
        pTmp = pData;
        for(i = 0; i < PasswordLenght; i++)
        {
            *pTmp2++ = *pTmp++;
        }

        RestDataCount = g_FileSize - PasswordLenght;
        pTmp2 = pData;
        pTmp = pData + PasswordLenght;
        for(i = 0; i < RestDataCount; i++)
        {
            *pTmp2++ = *pTmp++;
        }

        pTmp2 = pData + g_FileSize - 1;
        pTmp = pBackupData;
        for(i = 0; i < PasswordLenght; i++)
        {
            *pTmp2-- = *pTmp++;
        }

        free(pBackupData);
    }
    else
    {
        pTmp = pData;
        pTmpPassword = pPassword;
        for(i = 0; i < g_FileSize; i++)
        {
            *pTmp ^= *pTmpPassword;
            pTmp++;
            pTmpPassword++;
        }
    }

    //encrypt proccess 1
    pTmp = pData;
    for(i = 0; i < g_FileSize; i++)
    {
        TmpData = 0;
        TmpData = *pTmp & (0xFF >> EncyptFactor);
        TmpData <<= EncyptFactor;
        TmpData |= *pTmp >> (8 - EncyptFactor);
        *pTmp++ = TmpData;
    }

    //write encyption data to new file
    snprintf(g_buf, sizeof(g_buf), "%s%s", pFileName, DECRYPT_FILE_SUFFIX_NAME);
    FILE *fp = fopen(g_buf, "wb+");
    if(NULL == fp)
    {
        DISP_ERR_PLUS("%s%s \n", STR_ERR_CREATE_OPEN_ERR, g_buf);
        free(pData);
        fclose(fp);
        return STAT_ERR;
    }
    
    size = fwrite(pData, sizeof(uint8_t), g_FileSize, fp);
    if(size != g_FileSize)
    {
        DISP_ERR(STR_ERR_WRITE_FILE_ERR);
        free(pData);
        fclose(fp);
        return STAT_ERR;
    }

    free(pData);
    fclose(fp);
    return STAT_OK;
}
