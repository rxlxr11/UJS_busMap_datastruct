
#ifndef DATASTRUCT_CILENT_H
#define DATASTRUCT_CILENT_H

#include "constant.h"
#include "format.h"

//路线规划
typedef struct head{
    int start;
    char name[20];
    int node;
    float distance;
    float time;
    float price;
    int change;
    struct way *next;
}headN;

typedef struct way{
    int id;
    char name[20];
    char route[20];
    struct way *next;
}wayNode;


void insert_wayNode(headN *,int,char *,char *,float );

headN* createWay(int, char*);
void printWay(headN*);
void point_Bus(void);
void allBus(void);
int allRoute(headN *allWay[10],int ,int);
void shortRoute(Point, headN *allWay[point_Num]);
void bestRoute(headN *allWay[10],int ,int);
//void leastTime(Point , wayNode *allWay[point_Num]);
//void least_Change(int ,int );
void cycle(void);

#endif //DATASTRUCT_CILENT_H
