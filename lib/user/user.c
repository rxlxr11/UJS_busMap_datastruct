#include "user.h"

user* user_exist(char *name){
    int flag = -1;
    user *u;
    u=(user*)malloc(sizeof(user));
    /*
        read userfile
        do a loop to verify if the username exists
        if it exists verify the password
        else print "cant find the user"
    */
    FILE *f=fopen(USERFILE,"r");
    if(f==NULL)
    {
        printf("open file error");
        return NULL;
    }else {
        int a;
        while (fscanf(f, "%s %s %d\n", u->name, u->password, &u->access) != EOF) {
            a = strcmp(u->name, name);
            if (a == 0) {
                return u;
            }
        }
    }
    return NULL;
}
/*
	implement user login function
	return user rank
		-1: fail to login
		0 : student
		1 : admin
*/
int login(user *u){
    int flag =-1;
    if(u != NULL){
        char s[20];
        int i = 2;
        for(; i>=0; i--){
            //TODO
            int b;
            printf("请输入密码：");
            scanf("%s", s);
            b=strcmp(u->password, s);
            if(b == 0){
                printf("登录成功\n");
                flag = u->access;
                break;
            }
            else{
                printf("密码错误,你还有%d次机会\n", i);
            }
        }
    }
    return flag;
}

//注册
void registe(){
	int a=-1, flag=0, b=-1;
	user *u;
	u=(user*)malloc(sizeof(user));
	FILE *f=fopen(USERFILE,"a+");
	char name[20];
	char password[20];
	printf("请输入用户名：");
	scanf("%s",name);
	/*
		user have to input username until the 
		length of the user name is smaller than 20 
	*/
	while(1){
		int len=strlen(name);
		if(len>20){
			printf("不符合规则，请重新输入：");
			scanf("%s",name);
		}
		else{
			break;
		}
	}
	/*
		users need to input a unique username
	*/
	while(flag != 1){
		rewind(f);
		b = -1;
		while(fscanf(f,"%s %s %d\n",u->name, u->password, &u->access) != EOF){
			a = strcmp(u->name, name);
			if(a == 0){
				//TODO
				printf("用户名已存在,请重新输入\n");
				b = 0;
			}
		}
		if(b != 0){
			flag = 1;
			strcpy(u->name, name);
			break;
		}
		printf("请输入用户名：");
		scanf("%s", name);
	}
	/*
		the pwd should obey the rules(shorter than 20 characters)
	*/
	printf("请输入密码：");
	scanf("%s",password);
	while(1){
		int len = strlen(password);
		if(len > 20){
			printf("不符合规则，请重新输入：");
			scanf("%s", password);
		}
		else{
			strcpy(u->password, password);
			break;
		}
	}
	fprintf(f,"%s %s %d\n",u->name, u->password, 0);
	fclose(f);
	printf("注册成功");
}