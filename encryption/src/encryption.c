/*************************************************************************
	> File Name: encryption.c
	> Author: lvsenlv
	> Mail: lvsen46000@163.com
	> Created Time: 2017年08月03日 星期四 08时37分45秒
 ************************************************************************/

#include "encryption.h"
#include <string.h>

static char g_buf[BUF_SIZE];
static FILE *g_fp = NULL;
__IO static uint64_t g_FileSize = 0;

int main(void)
{
    g_fp = fopen("test.lv", "rb");
    if(NULL == g_fp)
    {
        DISP_ERR_PLUS("Fail to create or open \n");
        return -1;
    }
    fseek(g_fp, 0, SEEK_END);
    g_FileSize = ftell(g_fp);
    Encrypt_KB_File("test.lv", "lvsen");    
    fclose(g_fp);
    g_fp = NULL;
    
    g_fp = fopen("test.lv.encrypt", "rb");
    if(NULL == g_fp)
    {
        DISP_ERR_PLUS("Fail to create or open \n");
        return -1;
    }
    fseek(g_fp, 0, SEEK_END);
    g_FileSize = ftell(g_fp);
    Decrypt_KB_File("test.lv.encrypt", "lvsen");    
    fclose(g_fp);
    g_fp = NULL;
    return 0;
}

G_STATUS Encrypt_KB_File(const char *pFileName, const char *pPassword)
{
    if((g_FileSize < 4) || (g_FileSize > BUF_SIZE_SMALL)) //Do not handle this circumstance
    {
        return STAT_OK;
    }

    //read data from original file
    uint8_t *pData = NULL;
    pData = (uint8_t *)malloc(sizeof(uint8_t) * BUF_SIZE_SMALL);
    if(NULL == pData)
    {
        DISP_ERR_PLUS("%s. It needs at least 1MB \n", STR_NO_FREE_MEM_SPACE);
        return STAT_ERR;
    }
    
    memset(pData, 0, sizeof(uint8_t)*BUF_SIZE_SMALL);
    fseek(g_fp, 0, SEEK_SET);
    uint64_t size = 0;
    size = fread(pData, sizeof(uint8_t), g_FileSize, g_fp);
    if(size != g_FileSize)
    {
        DISP_ERR_PLUS("Fail to read %s \n", pFileName);
        free(pData);
        return STAT_ERR;
    }

/*************************************************************************
                   Core codes of encryption algorithm
************************************************************************/

    //get encrypt factor
    uint32_t EncyptFactor = 0;
    uint32_t PasswordLenght = 0;
    const char *pTmpPassword = pTmpPassword;
    while(*pTmpPassword != '\0')
    {
        EncyptFactor += *pTmpPassword++;
        PasswordLenght++;
    }
    EncyptFactor %= 8;
    if(0 == EncyptFactor)
        EncyptFactor = 1;

    //encrypt proccess 1
    uint32_t i = 0;
    uint8_t TmpData = 0, *pTmp = pData;
    for(i = 0; i < g_FileSize; i++)
    {
        TmpData = 0;
        TmpData = *pTmp & ((uint8_t)EncyptFactor);
        TmpData <<= (uint8_t)(8 - EncyptFactor);
        TmpData |= *pTmp >> ((uint8_t)EncyptFactor);
        *pTmp++ = TmpData;
    }    

    //encrypt proccess 2
    uint8_t *pBackupData = (uint8_t *)malloc(PasswordLenght * sizeof(uint8_t));
    if(NULL == pBackupData)
    {
        DISP_ERR_PLUS("%s \n", STR_NO_FREE_MEM_SPACE);
        free(pData);
        return STAT_ERR;
    }

    uint8_t *pTmp2 = pBackupData;
    pTmp = pData + g_FileSize - 1;
    uint32_t RestDataCount = 0;
    if(g_FileSize > PasswordLenght)
    {
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
        pTmp = pData;
        pTmp2 = pBackupData;
        for(i = 0; i < PasswordLenght; i++)
        {
            *pTmp++ = *pTmp2++;
        }
    }
    else
    {
        pTmp = pData + RestDataCount;
        pTmpPassword = pPassword;
        for(i = 0; i < PasswordLenght; i++)
        {
            *pTmp ^= *pTmpPassword;
            pTmp++;
            pTmpPassword++;
        }
    }

    //encrypt proccess 3
    if(g_FileSize > (BUF_SIZE_SMALL/2))
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
        DISP_ERR_PLUS("Fail to create or open %s \n", g_buf);
        free(pBackupData);
        free(pData);
        fclose(fp);
        return STAT_ERR;
    }
    
    size = fwrite(pData, sizeof(uint8_t), g_FileSize, fp);
    if(size != g_FileSize)
    {
        DISP_ERR_PLUS("Fail to write to %s \n", g_buf);
        free(pBackupData);
        free(pData);
        fclose(fp);
        return STAT_ERR;
    }

    free(pBackupData);
    free(pData);
    fclose(fp);
    return STAT_OK;
}

G_STATUS Encrypt_MB_File(const char *ptr, const char *pPassword)
{
    return STAT_OK;
}


G_STATUS Encrypt_GB_File(const char *ptr, const char *pPassword)
{
    return STAT_OK;
}


G_STATUS Decrypt_KB_File(const char *pFileName, const char *pPassword)
{
    if((g_FileSize < 4) || (g_FileSize > BUF_SIZE_SMALL)) //Do not handle this circumstance
    {
        return STAT_OK;
    }

    //read data from original file
    uint8_t *pData = NULL;
    pData = (uint8_t *)malloc(sizeof(uint8_t) * BUF_SIZE_SMALL);
    if(NULL == pData)
    {
        DISP_ERR_PLUS("%s. It needs at least 1MB \n", STR_NO_FREE_MEM_SPACE);
        return STAT_ERR;
    }
    
    memset(pData, 0, sizeof(uint8_t)*BUF_SIZE_SMALL);
    fseek(g_fp, 0, SEEK_SET);
    uint64_t size = 0;
    size = fread(pData, sizeof(uint8_t), g_FileSize, g_fp);
    if(size != g_FileSize)
    {
        DISP_ERR_PLUS("Fail to read %s \n", pFileName);
        free(pData);
        return STAT_ERR;
    }

/*************************************************************************
                   Core codes of encryption algorithm
************************************************************************/

    //get encrypt factor
    uint32_t EncyptFactor = 0;
    uint32_t PasswordLenght = 0;
    const char *pTmpPassword = pTmpPassword;
    while(*pTmpPassword != '\0')
    {
        EncyptFactor += *pTmpPassword++;
        PasswordLenght++;
    }
    EncyptFactor %= 8;
    if(0 == EncyptFactor)
        EncyptFactor = 1;

    //encrypt proccess 1
    uint32_t i = 0;
    uint8_t TmpData = 0, *pTmp = pData;
    for(i = 0; i < g_FileSize; i++)
    {
        TmpData = 0;
        TmpData = *pTmp & ((uint8_t)(8 - EncyptFactor));
        TmpData <<= (uint8_t)EncyptFactor;
        TmpData |= *pTmp >> ((uint8_t)(8 - EncyptFactor));
        *pTmp++ = TmpData;
    }    

    //encrypt proccess 3
    uint8_t *pTmp2;
    if(g_FileSize > (BUF_SIZE_SMALL/2))
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
    uint8_t *pBackupData = (uint8_t *)malloc(PasswordLenght * sizeof(uint8_t));
    if(NULL == pBackupData)
    {
        DISP_ERR_PLUS("%s \n", STR_NO_FREE_MEM_SPACE);
        free(pData);
        return STAT_ERR;
    }

    uint32_t RestDataCount = 0;
    if(g_FileSize > PasswordLenght)
    {
        pTmp = pData;
        pTmp2 = pBackupData;
        for(i = 0; i < PasswordLenght; i++)
        {
            *pTmp++ = *pTmp2++;
        }
        RestDataCount = g_FileSize - PasswordLenght;
        pTmp2 = pData;
        pTmp = pData + PasswordLenght;
        for(i = 0; i < RestDataCount; i++)
        {
            *pTmp2++ = *pTmp++;
        }
        pTmp = pBackupData;
        pTmp2 = pData + RestDataCount;
        for(i = 0; i < PasswordLenght; i++)
        {
            *pTmp2-- = *pTmp++;
        }
    }
    else
    {
        pTmp = pData + RestDataCount;
        pTmpPassword = pPassword;
        for(i = 0; i < PasswordLenght; i++)
        {
            *pTmp ^= *pTmpPassword;
            pTmp++;
            pTmpPassword++;
        }
    }

    //write encyption data to new file
    snprintf(g_buf, sizeof(g_buf), "%s%s", pFileName, ENCRYPT_FILE_SUFFIX_NAME);
    FILE *fp = fopen(g_buf, "wb+");
    if(NULL == fp)
    {
        DISP_ERR_PLUS("Fail to create or open %s \n", g_buf);
        free(pBackupData);
        free(pData);
        fclose(fp);
        return STAT_ERR;
    }
    
    size = fwrite(pData, sizeof(uint8_t), g_FileSize, fp);
    if(size != g_FileSize)
    {
        DISP_ERR_PLUS("Fail to write to %s \n", g_buf);
        free(pBackupData);
        free(pData);
        fclose(fp);
        return STAT_ERR;
    }

    free(pBackupData);
    free(pData);
    fclose(fp);
    return STAT_OK;
}
