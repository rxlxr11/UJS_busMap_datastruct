#ifndef DATAIO_H
#define DATAIO_H

#include "constant.h"
//追加数据
void append(char* ,char* );
void write_Point(char*,Point);
void readPoint(char *,Point *);
void readAll(char *,char **);
void write_all(char*,char **);
void write_bus(char*, LinkList*);
void write_demo(void);
#endif