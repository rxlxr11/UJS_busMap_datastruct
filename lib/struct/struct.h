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



	//定义公交链表节点
	typedef struct node{
		char name[20];
		struct node *prior;
		struct node *next;
	}LNode,LinkList;

	LinkList* createLink(char *);
	Neighbour* find_Neighbour(int , Point);


#endif
