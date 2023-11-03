#ifndef USER_H
#define USER_H
#define USERFILE "E:/codeTest/datastruct/data/user/all.txt"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
	//定义用户
	typedef struct{
		char name[20];
		char password[20];
		int access;
	}user;
    user* user_exist(char *);
    int login(user *);
	void registe(void);

#endif