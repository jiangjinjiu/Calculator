#ifndef __DWLSTRING_H__
#define  __DWLSTRING_H__

int DWLStrLen(const char *cDest);
char *DWLStrCpy(char *cDest,const char *cSour);
int DWLStrCmp(const char *cStr1,const char *cStr2);
char *DWLStrCat(char *cDest,const char *cSour);

int ArraySize(const char *cSour);//返回数组的大小

#endif