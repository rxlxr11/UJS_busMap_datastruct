#ifndef STRUCT_H
#define STRUCT_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
	//定义邻居节点结构
	//id为唯一标识
	//distance为节点到邻居节点距离 
	//route为节点到邻居节点的可用方式
	typedef struct neighbour{
		int id;
		float distance;
		char route[20];
		struct neighbour *next;
	}Neighbour; 

	//定义各点 
	//name节点名称
	//n为邻居节点的集合 
	typedef struct point{
		int id;
		char name[20];
		Neighbour *first;
	}Point;

	//路线规划
	typedef struct way{
		int id;
		char name[20];
		char route[20];
		struct way *next;
	}wayNode;

	//定义公交链表节点
	typedef struct node{
		char name[20];
		struct node *prior;
		struct node *next;
	}LNode,LinkList;

	LinkList* createLink(char *);
	
	void insert_wayNode(wayNode *,int,char *,char *);
	void copy_way(wayNode*,wayNode*);
	wayNode* createWay(void);
	Neighbour* find_Neighbour(int , Point);

	char* edit_point_file_name(int);
	char* edit_bus_file_name(char *);
#endif