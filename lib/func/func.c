#include "func.h"

//equal
int equal_f(char *s1,char *s2){
	int a;
	a = strcmp(s1,s2);
	if(a==0){
		return 1;
	}
	return 0;
}


int locate_int(int m,int a[25],int num){
	int flag=-1;
	int i;
	for(i=0;i<num;i++){
		//TODO
		if(m==a[i]){
			//TODO
			flag=i;
			break;
		}
	}
	return flag;
}

//用逗号分开字符串
int splitComma(char *s,char **split){
	char* token = strtok(s,",");
	int i=0;
	split[i]=token;
	i++;
	while(token != NULL){
		token=strtok(NULL,",");
		if(token==NULL)
			break;
		split[i]=token;
		i++;
	}
	return i;
}

//找出两个数组中的相同元素
int findSame(int a[10],int b[10],int c[10],int a_num,int b_num){
	int *p=c;
	int n=0,i=1,j=1;
	for(;i<a_num;i++){
		//TODO
		j=0;
		for(;j<b_num;j++){
			//TODO
			if(a[i] == b[j]){
				//TODO
				*p=a[i];
				p++;
				n++;
				break;
			}
		}
		//printf("\n");
	}
	return n;
}

