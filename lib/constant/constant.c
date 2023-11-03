
#include "constant.h"
int bus_Num;
 int point_Num;

 char **pointFileName, **busFileName;
 Point allPoint[MAXSIZE];
 LinkList* busRoute[MAXSIZE];

//纪录公交线路名称
 char busName[MAXSIZE][20];
//记录对应公交价格
 float busPrice[MAXSIZE];
//记录所有站点名称
 char allPointName[MAXSIZE][20];
//记录站点id
 int allPointId[MAXSIZE];

//根据名称找id
int findID_byName(char *s) {
    int id = -1;
    for (int i = 0; i < point_Num; i++) {
        if (equal_f(allPointName[i], s)) {
            id = allPointId[i];
            break;
        }
    }
    return id;
}

Point findPoint(int id){
    Point p;
    for(int i=0;i<point_Num;i++){
        if(id==allPoint[i].id){
            p=allPoint[i];
        }
    }
    return p;
}