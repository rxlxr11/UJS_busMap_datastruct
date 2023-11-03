
#ifndef DATASTRUCT_CILENT_H
#define DATASTRUCT_CILENT_H

#include "constant.h"
#include "format.h"

void point_Bus(void);
void allBus(void);
int allRoute(wayNode *allWay[10],int ,int);
void shortRoute(Point, wayNode *allWay[point_Num]);
void leastTime(Point , wayNode *allWay[point_Num]);
//void least_Change(int ,int );
void cycle(void);

#endif //DATASTRUCT_CILENT_H
