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

static G_STATUS GetFileSize(const char *pFileName, int64_t *pFileSize);
static G_STATUS Encrypt_KB_File(FILE *fp, const char *pFileName, int64_t FileSize);
static G_STATUS Encrypt_MB_File(FILE *fp, const char *pFileName, int64_t FileSize);
static G_STATUS Encrypt_GB_File(FILE *fp, const char *pFileName, int64_t FileSize);
static G_STATUS Decrypt_KB_File(FILE *fp, const char *pFileName, int64_t FileSize);


char g_password[PASSWORD_LENGHT];

#ifdef __LINUX
static G_STATUS GetFileSize(const char *pFileName, int64_t *pFileSize)
{
    struct stat FileInfo;
    int res = 0;

    res = stat(pFileName, &FileInfo);
    if(res != 0)
    {
        DISP_ERR(STR_ERR_GET_FILE_SIZE_ERR);
        return STAT_ERR;
    }

    *pFileSize = FileInfo.st_size;
    
    return STAT_OK;
}
#elif defined __WINDOWS
static G_STATUS GetFileSize(const char *pFileName, int64_t *pFileSize)
{    
    return STAT_ERR;
}
#endif

static G_STATUS Encrypt_KB_File(FILE *fp, const char *pFileName, int64_t FileSize)
{
    //read data from original file
    uint8_t *pData = NULL;
    pData = (uint8_t *)malloc(sizeof(uint8_t) * BUF_SIZE_SMALL);
    if(NULL == pData)
    {
        DISP_ERR(STR_ERR_MALLOC_BUF_SMALL);
        return STAT_ERR;
    }
    
    memset(pData, 0, sizeof(uint8_t)*BUF_SIZE_SMALL);
    fseek(fp, 0, SEEK_SET);
    uint64_t size = 0;
    size = fread(pData, sizeof(uint8_t), FileSize, fp);
    if(size != FileSize)
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
    const char *pTmpPassword = g_password;
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
    for(i = 0; i < FileSize; i++)
    {
        TmpData = 0;
        TmpData = *pTmp & (0xFF >> (8-EncyptFactor));
        TmpData <<= 8 - EncyptFactor;
        TmpData |= *pTmp >> ((uint8_t)EncyptFactor);
        *pTmp++ = TmpData;
    }    

    //encrypt proccess 2
    if(FileSize > PasswordLenght)
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
        pTmp = pData + FileSize - 1;
        for(i = 0; i < PasswordLenght; i++)
        {
            *pTmp2++ = *pTmp--;
        }

        RestDataCount = FileSize - PasswordLenght;
        pTmp2 = pData + FileSize - 1;
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
        pTmpPassword = g_password;
        for(i = 0; i < FileSize; i++)
        {
            *pTmp ^= *pTmpPassword;
            pTmp++;
            pTmpPassword++;
        }
    }

    //encrypt proccess 3
    if(FileSize > 256)
    {
        pTmp = pData;
        pTmp2 = pData + FileSize - 1;
        pTmpPassword = g_password;
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
    char NewFileName[FILE_NAME_LENGTH];
    snprintf(NewFileName, sizeof(NewFileName), "%s%s", pFileName, ENCRYPT_FILE_SUFFIX_NAME);
    FILE *NewFp = fopen(NewFileName, "wb+");
    if(NULL == NewFp)
    {
        DISP_ERR_PLUS("%s%s \n", STR_ERR_CREATE_OPEN_ERR, NewFileName);
        free(pData);
        fclose(NewFp);
        return STAT_ERR;
    }
    
    size = fwrite(pData, sizeof(uint8_t), FileSize, NewFp);
    if(size != FileSize)
    {
        DISP_ERR(STR_ERR_WRITE_FILE_ERR);
        free(pData);
        fclose(NewFp);
        return STAT_ERR;
    }

    free(pData);
    fclose(NewFp);
    return STAT_OK;
}

static G_STATUS Encrypt_MB_File(FILE *fp, const char *pFileName, int64_t FileSize)
{
    return STAT_OK;
}

static G_STATUS Encrypt_GB_File(FILE *fp, const char *pFileName, int64_t FileSize)
{
    return STAT_OK;
}

static G_STATUS Decrypt_KB_File(FILE *fp, const char *pFileName, int64_t FileSize)
{
    if((0 == FileSize) || (FileSize > BUF_SIZE_SMALL)) //Do not handle this circumstance
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
    fseek(fp, 0, SEEK_SET);
    uint64_t size = 0;
    size = fread(pData, sizeof(uint8_t), FileSize, fp);
    if(size != FileSize)
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
    const char *pTmpPassword = g_password;
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
    if(FileSize > 256)
    {
        pTmp = pData;
        pTmp2 = pData + FileSize - 1;
        pTmpPassword = g_password;
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
    if(FileSize > PasswordLenght)
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

        RestDataCount = FileSize - PasswordLenght;
        pTmp2 = pData;
        pTmp = pData + PasswordLenght;
        for(i = 0; i < RestDataCount; i++)
        {
            *pTmp2++ = *pTmp++;
        }

        pTmp2 = pData + FileSize - 1;
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
        pTmpPassword = g_password;
        for(i = 0; i < FileSize; i++)
        {
            *pTmp ^= *pTmpPassword;
            pTmp++;
            pTmpPassword++;
        }
    }

    //encrypt proccess 1
    pTmp = pData;
    for(i = 0; i < FileSize; i++)
    {
        TmpData = 0;
        TmpData = *pTmp & (0xFF >> EncyptFactor);
        TmpData <<= EncyptFactor;
        TmpData |= *pTmp >> (8 - EncyptFactor);
        *pTmp++ = TmpData;
    }

    //write encyption data to new file
    char NewFileName[FILE_NAME_LENGTH];
    snprintf(NewFileName, sizeof(NewFileName), "%s%s", pFileName, DECRYPT_FILE_SUFFIX_NAME);
    FILE *NewFp = fopen(NewFileName, "wb+");
    if(NULL == NewFp)
    {
        DISP_ERR_PLUS("%s%s \n", STR_ERR_CREATE_OPEN_ERR, NewFileName);
        free(pData);
        fclose(NewFp);
        return STAT_ERR;
    }
    
    size = fwrite(pData, sizeof(uint8_t), FileSize, NewFp);
    if(size != FileSize)
    {
        DISP_ERR(STR_ERR_WRITE_FILE_ERR);
        free(pData);
        fclose(NewFp);
        return STAT_ERR;
    }

    free(pData);
    fclose(NewFp);
    return STAT_OK;
}
