#include "dataio.h"

//追加数据
void append(char* name,char* s) {
	FILE *f;
	f = fopen(name,"a+");
	fprintf(f,"%s\n",s);
	fclose(f);
}
//读取节点数据
void readPoint(char *name,Point *p){
	FILE *f;
	f = fopen(name,"r");
	if(f==NULL){
		printf("read file error");
		exit(0);
	}
	else{
		fscanf(f,"%d %s\n",&p->id,p->name);
        //printf("%s",p->name);
		p->first=NULL;
		int x;
		float y;
		char s[10];
		while(fscanf(f,"%d %f %s\n",&x,&y,s) != EOF){
			Neighbour *n;
			n=(Neighbour*)malloc(sizeof(Neighbour));
			n->id=x;
			n->next=p->first;
			n->distance=y;
			strcpy(n->route,s);
			p->first=n;
		}
	}
	fclose(f);
}
//写入节点数据
void write_Point(char *name,Point p){
	FILE *f;
	f = fopen(name,"w+");
	if(f==NULL){
		printf("error");
		exit(0);
	}
	else{
		fprintf(f,"%d %s\n",p.id,p.name);
		Neighbour *n=p.first;
		while(n!=NULL){
			fprintf(f,"%d %.2f %s\n",n->id,n->distance,n->route);
			n=n->next;
		}
	}
	fclose(f);
}
//读取all文件
void readAll(char *name,char **s){
	FILE *f;
	f = fopen(name,"r");
	if(f==NULL){
		printf("error");
		exit(0);
	}
	else{
		int i=0;
		s[i]=(char*)malloc(100*sizeof(char));
		while(fscanf(f,"%s\n",s[i]) != EOF){
			i++;
			s[i]=(char*)malloc(100*sizeof(char));
		}
	}
	fclose(f);
}
void write_bus(char *s,LinkList* L){
	LinkList *T=L;
	FILE *F=fopen(s,"w+");
	while(T->next!=NULL){
		//TODO
		fprintf(F,"%s\n",T->name);
		T=T->next;
	}
}

//写入demo文件
void write_demo(){
    FILE *f=fopen(DEMOFILE,"w+");
    if(f==NULL){
        printf("error");
        exit(0);
    }
    else{
        fprintf(f,"%d\n",point_Num);
        fprintf(f,"%d\n",bus_Num);
    }
    fclose(f);
}
