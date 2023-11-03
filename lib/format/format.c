#include "format.h"

//登录
void loginInter(){
	printf("+-------------------------------+\n");
	printf("|         线路问询系统            |\n");
	printf("+-------------------------------+\n");
	printf("|          1. 登录               |\n");
	printf("|          2. 注册               |\n");
	printf("|         -1. 退出               |\n");
	printf("+-------------------------------+\n");
}
//管理员菜单
void adminMenu(){
	printf("+-------------------------------+\n");
	printf("|         线路问询系统            |\n");
	printf("+-------------------------------+\n");
	printf("|1. 新增公交线路                  |\n");
	printf("|2. 修改已有公交线路               |\n");
	printf("|3. 删除公交线路站点               |\n");
	printf("|4. 新增站点                      |\n");
	printf("+-------------------------------+\n");
	printf("|5. 查询经过该点的所有公交路线       |\n");
	printf("|6. 查询所有公交路线               |\n");
	printf("|7. 查询所有可达路线               |\n");
	printf("|8. 最优路线规划                  |\n");
	printf("|9. 查询一点到其他站点的最短路线     |\n");
	printf("|10.查看是否有环线                 |\n");
	printf("|-1.退出                         |\n");
	printf("+-------------------------------+\n");
}
//学生端菜单
void stuMenu(){
	printf("+-------------------------------+\n");
	printf("|         线路问询系统            |\n");
	printf("+-------------------------------+\n");
	printf("|1. 查询经过该点的所有公交路线       |\n");
	printf("|2. 查询所有公交路线               |\n");
	printf("|3. 查询所有可达路线               |\n");
	printf("|4. 最优路线规划                  |\n");
	printf("|5. 查询一点到其他站点的最短路线     |\n");
	printf("|6. 查看是否有环线                 |\n");
	printf("|-1.退出                         |\n");
	printf("+-------------------------------+\n");
}
void printBus(LinkList* L){
	LNode* p=(LNode*)malloc(sizeof(LNode));
	char temp[10];
	strcpy(temp,L->name);
	char **contain;
	contain=(char**)malloc(sizeof(char*));
	splitComma(temp,contain);
	char busName[10];
	strcpy(busName,contain[0]);
	strcpy(temp,contain[1]);
	float f=atof(temp);
	p=L->next;
	printf("+－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－+\n");
	printf(" %s号线,车票:%.2f元	",busName,f);
	while(p != NULL){
		printf("%s",p->name);
		if(p->next!=NULL){
			printf("<-->");
		}
		p=p->next;
	}
	printf("\n");
    printf("+－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－+\n");
	
}
void printWay(wayNode *n){
    printf("+－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－+\n");
	printf(" %s", n->name);
	while(n != NULL){
		//TODO
		n=n->next;
		if(n != NULL){
			//TODO
			printf("--%s-->",n->route);
			printf("%s",n->name);
		}
	}
	printf("\n");
    printf("+－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－+\n");
}