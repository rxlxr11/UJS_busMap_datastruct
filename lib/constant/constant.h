#ifndef CONSTANT_H  
#define CONSTANT_H
#include "struct.h"
#include "func.h"
#define MAX 99999999
#define MAXSIZE 25

#define HUMANV 1
#define BUSV 10

#define FILENAME         "E:/codeTest/datastruct"
#define BUSFOLDEER       "E:/codeTest/datastruct/data/bus/"
#define POINTFOLDER      "E:/codeTest/datastruct/data/point/"
#define BUSALLFILENAME   "E:/codeTest/datastruct/data/bus/all.txt"
#define POINTALLFILENAME "E:/codeTest/datastruct/data/point/all.txt"
#define DEMOFILE         "E:/codeTest/datastruct/data/demo.txt"


extern int bus_Num;
extern int point_Num;

extern char **pointFileName, **busFileName;
extern Point allPoint[MAXSIZE];
extern LinkList* busRoute[MAXSIZE];

//纪录公交线路名称
extern char busName[MAXSIZE][20];
//记录对应公交价格
extern float busPrice[MAXSIZE];
//记录所有站点名称
extern char allPointName[MAXSIZE][20];
//记录站点id
extern int allPointId[MAXSIZE];

int findID_byName(char *s);
Point findPoint(int id);
#endif                                             
