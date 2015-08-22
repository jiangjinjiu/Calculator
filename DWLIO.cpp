#include "StdAfx.h"
#include <STDIO.H>
#include "DWLIO.h"
#include "DWLString.h"

char *DWLitoa(int value, char *cDest, int radix)
{
	//int nTemp = 0;
	char *pHead = cDest;
	char *pEnd = cDest;
	

	if(value ==0 || radix == -0)
	{
		*pEnd++ = '0';
		*pEnd = '\0';
		
	}

	if(value <0)
	{
		*pHead++ = *pEnd++ = '-';
		//int nTemp = value;
		//value=-value;
		value = -value;
	}

	if(value > 0)
	{
		char t;
		int i;
		int nCount = 0; 

		while(value!=0)
		{
			int nRemainder = value%radix;
			if(radix > nRemainder&&nRemainder<10)
			{
				*pEnd++ =nRemainder+ '0';
			}
			else if(radix > nRemainder && nRemainder >= 10)
			{
				*pEnd++ = nRemainder-10+ 'a';
			}
			
			 nCount++;
			 value=value/radix;
		}

			*pEnd-- = '\0';
	
		for(i = 0; i<nCount/2; i++)
		{
		   t = *pHead;
		   *pHead = *pEnd;
		   *pEnd = t;
		   *pEnd--;
		   *pHead++;
		 }
	}		
	return cDest;
}

int DWLatoi(const char *npStr)
{
	if(NULL != npStr)
	{
		const char *pTemp = npStr;
		int nDest = 0;
		int nSign = 1;
		int nCount = 0;//用于记录第二次遇到“-”或“+“时，做正确的处理

		while(32 == *pTemp)
		{
			pTemp++;
		}


		while('\0' != *pTemp)
		{
			if(nCount == 0)
			{
				if(*pTemp == '-' )
				{
					nSign = -1;	
				}

				if(*pTemp == '-' || *pTemp == '+')
				{
					*pTemp++;
				}
				else if(*pTemp <= '0' && *pTemp >= '9')
				{
					return 0;
				}
				nCount++;
			}
			else
			{
				if(*pTemp == '-' || *pTemp == '+')
				{
					return (nSign*nDest);
				}

				if(*pTemp < '0' || *pTemp > '9')
				{
					return (nSign*nDest);
				}
			}

			if(*pTemp >= '0' && *pTemp <= '9')
			{
				nDest = nDest*10+(*pTemp-'0');
			}
			pTemp++;
		}

		return (nSign*nDest);
	}
	return 0;
}

char *DWLftoa(double value, char *cDest, int radix)
{
	int nCount = 1;
	int nInteger = 0;
	double dFloat = 0.0;

	char cInteger[255] = "";
	char cDecimal[255] = "";

	if(value < 0.0)
	{
		value = -value;
	    DWLStrCpy(cDest, "-");
		
	}

	    nInteger = (int)value;
		DWLitoa(nInteger,cInteger,radix);
		DWLStrCat(cDest,cInteger);
		dFloat = value -nInteger;
		
		if(dFloat != 0.0000)
		{
			cDecimal[0] = '.';
		}

		while( dFloat !=0.0&&nCount<20)
		{
			nInteger = (int)(dFloat*=radix);

			if(nInteger >= 0 && nInteger <= 9)
			{
				cDecimal[nCount++]= nInteger + '0';
			}
			else
			{
				cDecimal[nCount++]= nInteger + 0x57;//在ascii中与“a”相隔9个字符
			}

			dFloat-= nInteger;
		}
		cDecimal[nCount]= '\0';
		
	
	return DWLStrCat(cDest, cDecimal);
}

double DWLatof(const char *npStr)
{
	if(NULL != npStr)
	{
		const char *pTemp = npStr;
	
		double nDest = 0.0;
		int nSign = 1;
		int nCount = 0;//用于记录第二次遇到“-”,“。”,“+“等时，做正确的处理
		int nDecpoint = 0;//用于区分小数点前后的处理
		int nTemp =10;

		while(32 == *pTemp)
		{
			pTemp++;
		}

		while('\0' != *pTemp)
		{
				if( nCount==0&&*pTemp == '-' )
				{
					if(*(pTemp-1) == 32||(*(pTemp+1) >= '0' && *(pTemp+1) <= '9'))
					{
						nSign = -1;	
						nCount++;
						pTemp++;
					}
					else
					{
						break;
					}
				}
				else if(nCount == 1&&*pTemp == '-')
				{
					break;
				}
				
				if(nDecpoint == 0 && *pTemp >= '0' && *pTemp <= '9')
				{
					nDest = nDest*10+(*pTemp-'0');
				}

				if((nDecpoint == 0&& *pTemp == '.') || (nDecpoint == 1&& *pTemp == '.'))
				{
					nDecpoint++;
					pTemp++;
				}
				
				if(nDecpoint == 0 && (*pTemp < '0' || *pTemp > '9'))
				{
					break;
				}


				if(nDecpoint == 1 && *pTemp >= '0' && *pTemp <= '9')
				{
					nDest = nDest+((double)(*pTemp-'0'))/nTemp;
					nTemp*=10;
				}

				if(nDecpoint == 1 && (*pTemp < '0' || *pTemp > '9'))
				{
					break;
				}


				pTemp++;
		}

		return (nSign*nDest);
	}
	return 0;
}


void DWLprintf(const char *pFormat,...)
{
	const char **p=&pFormat;
	p++;
	const char *pTemp=pFormat;
	while('\0'!=*pTemp)
	{
		if('%'==*pTemp)
		{
			pTemp++;
	
			switch(*pTemp)
			{
				case 'c':
					putchar(*((char *)p));
					pTemp++;
					break;
					
				case 'd':
					{
						int nInteger = *((int *)p);
						char szBuf[50] ="";
						
						DWLitoa(nInteger,szBuf,10);
						//printf("%s\n",szBuf);
						char *cpInt = szBuf;

						while('\0' != *cpInt)
						{
							putchar(*cpInt);
							cpInt++;
						}
						
					}
					pTemp++;
					break;
					
				case 's':
					{
						char *cpTemp = (char *)(*p);
						while('\0' != *cpTemp)
						{
							putchar(*cpTemp);
							cpTemp++;
						}
						cpTemp++;
					}
					pTemp++;
					break;

				case 'f':
					{
						double dFloat = *((double *)p);
						char szBuf[50] ="";
						
						DWLftoa(dFloat,szBuf,10);
						//DWLftoa(1234.57856,szBuf,10);;
						//printf("%s\n",szBuf);
						char *pTemp = szBuf;

						while('\0' != *pTemp)
						{
							putchar(*pTemp);
							pTemp++;
						}
						//pTemp++;
					}
					pTemp++;
					break;
				
				default:
					pTemp--;
					break;
			}
		}
		putchar(*pTemp);
		pTemp++;
	}
}


void DWLscanf(const char *pFormat, ...)
{
	const char **p=&pFormat;
	p++;
	const char *pTemp=pFormat;
	while('\0'!=*pTemp)
	{
		if('%' == *pTemp)
		{
			pTemp++;
	
			switch(*pTemp)
			{
				case 'c':
					{
						char cTemp;
						if((cTemp = getchar()) != '\n')
						{
							*((char*)(*p))=cTemp;
							getchar();
						}	
					}
					break;
				case 'd':
					{
						char szBuff[255]="";
						char *pTemp = szBuff;
						while((*pTemp = getchar()) != '\n')
						{
							pTemp++;
						}
						*(++pTemp) = '\0';
						int a=DWLatoi(szBuff);
						//printf("%d\n",a);
						
						*((int*)(*p))=a;
					}
					break;
				case 'f':
					{
						char szBuff[255]="";
						char *pTemp = szBuff;
						while((*pTemp = getchar()) != '\n')
						{
							pTemp++;
						}
						*(++pTemp) = '\0';
						float a=DWLatof(szBuff);
						//printf("%d\n",a);
						
						*((float*)(*p))=a;
					}
					break;
				case 's':
					{
						char szBuff[255]="";
						char *pTemp = szBuff;
						while((*pTemp = getchar()) != '\n')
						{
							*((char*)((*p)++))=*pTemp++;
						}	
						*((char*)((*p)))='\0';
					}
					break;
			}
		}
		pTemp++;
	}
}