#include "struct.h"

/*
    brief:  create list by iheadinsert
    para :  filename
    return :buslist 
*/
LinkList* createLink(char *s){
	LinkList* L;
	L=(LNode*)malloc(sizeof(LNode));
	L->next = NULL;
	L->prior = NULL;
	FILE *f;
	f=fopen(s,"r");
	fscanf(f,"%s",L->name);
	char str[20];
	while(fscanf(f,"\n%s",str) != EOF){
		LNode* p=(LNode*)malloc(sizeof(LNode));
		strcpy(p->name,str);
		p->next=L->next;
		p->prior=L;
		if(L->next!=NULL)
			L->next->prior=p;
		L->next=p;
	}
	fclose(f);
	return L;
}



Neighbour* find_Neighbour(int id, Point p) {
    Neighbour *n = p.first;
    while (n != NULL) {
        //TODO
        if (id == n->id) {
            //TODO
            break;
        }
        n = n->next;
    }
    return n;
}

