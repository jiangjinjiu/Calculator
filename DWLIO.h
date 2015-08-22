#ifndef __DWLIO_H__
#define  __DWLIO_H__

char *DWLitoa(int value, char *cDest, int radix);
int DWLatoi(const char *npStr);
char *DWLftoa(double value, char *cDest, int radix);
double DWLatof(const char *npStr);

void DWLprintf(const char *pFormat,...);
void DWLscanf(const char *pFormat, ...);


#endif