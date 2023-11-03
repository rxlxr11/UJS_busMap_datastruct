#ifndef FUNC_H
#define FUNC_H
#include <stdio.h>
#include <string.h>
int equal_f(char*,char*);
int locate(char *,char **);
int locate_int(int,int a[25],int); 
int splitComma(char *,char **);
int findSame(int a[10],int b[10],int c[10],int,int);
void selectionSort(int *,int); 
#endif