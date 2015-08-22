#include "StdAfx.h"
#include "DWLString.h"

int DWLStrLen(const char *cDest)
{
	if(NULL != cDest)
	{
	
		int nCount = 0;
		const char *pTemp = cDest;

		while('\0' != *pTemp)
		{
			nCount++;
			pTemp++;
		}
		return nCount;
	}

	return 0;
}

char *DWLStrCpy(char *cDest,const char *cSour)//��cDest����ĳ���>=cSour�����ݵĳ���ʱ����cSour��ȫ���Ƶ�cDest�У�
                                              //��cDest����ĳ���<cSour�����ݵĳ���ʱ����cSour��cDest����ĳ��ȸ��Ƶ�cDest�С�
{
	if(NULL != cSour && NULL!= cDest)
	{
		int i = 0;
		int nArraySize = ArraySize(cDest)-1;
		char *pDTemp = cDest;
		const char *pSTemp = cSour;

		if(nArraySize >= DWLStrLen(cSour))
		{
			while('\0' != *pSTemp)
			{
				*pDTemp++ = *pSTemp++;
			}
			return cDest;
		}
		else
		{
			for(; i < nArraySize; i++)
			{
				*pDTemp++ = *pSTemp++;
			}
			return cDest;
		}
	}
	return NULL;
}

int DWLStrCmp(const char *cStr1,const char *cStr2)//Str1=Str2,����0��Str1>Str2,����1��Str1<Str2,����-1
{
	if(NULL != cStr1 && NULL!= cStr2)
	{
		const char *pTemp1 = cStr1;
		const char *pTemp2 = cStr2;

		while('\0' != *pTemp1 && '\0' != *pTemp2)
		{
			if(*pTemp1++ == *pTemp2++)
			{
				continue;
			}
			else if(*(--pTemp1) > *(--pTemp2))
			{
				return 1;
			}
			else 
			{
				return -1;
			}
		}

		if('\0' == *pTemp1 && '\0' == *pTemp2)
			{
				return 0;
			}
			else if('\0' == *pTemp2)
			{
				return 1;
			}
			else
			{
				return -1;
			}
	}
	
}

char *DWLStrCat(char *cDest,const char *cSour)//��cDest����ĳ���>=��cSour�����ݵĳ���+cSour�����ݵĳ���)ʱ����cSour��ȫ��ӵ�cDest��
                                              //��cDest����ĳ���<��cSour�����ݵĳ���+cSour�����ݵĳ���)ʱ����cSour��cDest����ĳ�����ӵ�cDest�С�
{
	if(NULL != cSour && NULL!= cDest)
	{
		int i = 0;
		int nArraySize = ArraySize(cDest)-1;
		int nSourLen = DWLStrLen(cDest);
		char *pDTemp = cDest;
		const char *pSTemp = cSour;

		while('\0' != *pDTemp)
		{
			pDTemp++;
		}

		if(nArraySize >= (nSourLen+DWLStrLen(cSour)))
		{
			while('\0' != *pSTemp)
			{
				*pDTemp++ = *pSTemp++;
			}
			return cDest;
		}
		else
		{
			for(; i< (nArraySize-nSourLen);i++)
			{
				*pDTemp++ = *pSTemp++;
			}
		}
	}

	return NULL;
}


int ArraySize(const char *cSour)
{
	if(NULL != cSour)
	{
		int nCount = 0;
		const char *pTemp = cSour;

		
		while('\0' != *pTemp)
		{
			nCount++;
			pTemp++;
		}

		while('\0' == *pTemp)
		{
			nCount++;
			pTemp++;
		}

		return nCount;
	}

	return 0;
}