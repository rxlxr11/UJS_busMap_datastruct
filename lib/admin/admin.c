#include "admin.h"


char* edit_point_file_name(int id){
    char *fileN;
    fileN=(char*)malloc(200*sizeof(char));
    strcpy(fileN,POINTFOLDER);
    char name[10];
    sprintf(name,"%d",id);
    strcat(fileN,name);
    strcat(fileN,".txt");
    return fileN;
}

char* edit_bus_file_name(char *name){
    char *fileN;
    fileN=(char*)malloc(200*sizeof(char));
    strcpy(fileN,BUSFOLDEER);
    strcat(fileN,name);
    strcat(fileN,".txt");
    return fileN;
}
/*
 * brief:add neighbour for a point and change the related files
 * para :the name of neighbour
 *       pointer to p
 * return: void
 */
void add_neighbor(char *neighbourName,Point *p){
    while(findID_byName(neighbourName) == -1){
        //TODO
        printf("error");
        scanf("%s",neighbourName);
    }
    //n is a neighbour node to p
    //n2 is a neighbour node to the point which represent to neighbourname
    //neighbour is mutual relationship
    Neighbour *n=(Neighbour*)malloc(sizeof(Neighbour));
    Neighbour *n2=(Neighbour*)malloc(sizeof(Neighbour));
    n->id = findID_byName(neighbourName);
    strcpy(n->route,"z");
    strcpy(n2->route,"z");
    printf("请输入距离");
    float d;
    scanf("%f",&d);
    getchar();
    n2->distance=d;
    n2->id = p->id;
    n2->next = allPoint[(locate_int(n->id,allPointId,point_Num))].first;
    allPoint[(locate_int(n->id,allPointId,point_Num))].first = n2;
    n->distance=d;
    n->next=p->first;
    p->first=n;
    char *fileN = edit_point_file_name(n->id);
    write_Point(fileN,allPoint[(locate_int(n->id,allPointId,point_Num))]);
}

//新增公交线路
/*
 * brief:add a new bus route
 * input:a busname which is not repeated
 *       float price
 *       point name in order (separated by comma)
 * return: void
 */
void addBus() {
    char busname[10];
    float busPrice_f;
    char busPrice_s[10];
    char input[200];
    char **pointName;
    pointName = (char**)malloc(sizeof(char*));
    int a = 0;
    printf("请输入公交线路名称：");
    scanf("%s", busname);
    //判断公交路线名是否存在
    while (1) {
        a=0;
        for (int i = 0; i < bus_Num; i++) {
            printf("%s",busName[i]);
            if (equal_f(busname,busName[i])) {
                printf("该公交线路名称已存在，请重新输入");
                a=1;
                break;
            }
        }
        if(!a)
            break;
        printf("请输入公交线路名称：");
        scanf("%s", busname);
    }
    printf("请输入公交线路价格：");
    scanf("%f", &busPrice_f);
    printf("请依次输入公交站点\n");
    scanf("%s", input);
    //将输入的站点分割
    int count = splitComma(input, pointName);
    int point_exist_flag = 1;
    int i = 0;
    Neighbour *n;
    int location[MAXSIZE];
    while (i < count) {
        location[i]=findID_byName(pointName[i]);
        if (location[i] == -1) {
            //若有不存在的站点则退出
            printf("不存在%s", pointName[i]);
            point_exist_flag = 0;
            break;
        }
        i++;
    }
    i = 0;
    int if_reach_flag = 1;
    while (point_exist_flag && i < count - 1) {
        //开始判断能否到达下一站
        n=find_Neighbour(findID_byName(pointName[i+1]),findPoint(findID_byName(pointName[i])));
        if (n == NULL) {
            //TODO
            if_reach_flag = 0;
            printf("%s%s请重新规划路线\n", pointName[i], pointName[i + 1]);
            break;
        }
        i++;
    }
    if (if_reach_flag && point_exist_flag) {
        //写入文件
        char newFile[200];
        char first[10];
        sprintf(busPrice_s, "%.2f", busPrice_f);
        strcpy(first, busname);
        strcat(first, ",");
        strcat(first, busPrice_s);
        strcpy(newFile,edit_bus_file_name(busname));


        busRoute[bus_Num++] = createLink(newFile);
        for(i=0;i<count-1;i++){
            //TODO
            Neighbour *nt2 =find_Neighbour(findID_byName(pointName[i]), allPoint[locate_int(findID_byName(pointName[i+1]),allPointId,point_Num)]);
            Neighbour *nt1 =find_Neighbour(findID_byName(pointName[i+1]), allPoint[locate_int(findID_byName(pointName[i]),allPointId,point_Num)]);
            if(equal_f(nt1->route,"z")){
                //TODO
                strcpy(nt1->route, busname);
                strcpy(nt2->route, busname);
            }
            else{
                strcat(strcat(nt1->route,","),busname);
                strcat(strcat(nt2->route,","),busname);
            }
            char name1[10];
            char name2[10];
            sprintf(name1,"%d",findID_byName(pointName[i]));
            sprintf(name2,"%d",findID_byName(pointName[i+1]));
            char fileN1[200];
            char fileN2[200];
            strcpy(fileN1,FILENAME);
            strcpy(fileN2,FILENAME);
            strcat(strcat(strcat(fileN1,"/point/"),name1),".txt");
            strcat(strcat(strcat(fileN2,"/point/"),name2),".txt");
            write_Point(fileN1,findPoint(findID_byName(pointName[i])));
            write_Point(fileN2,findPoint(findID_byName(pointName[i+1])));
        }

        //写入demo
        write_demo();
        append(BUSALLFILENAME, newFile);
        //写入公交文件
        append(newFile, first);
        i = 0;
        while (i < count) {
            //TODO
            append(newFile, pointName[i]);
            i++;
        }
    }
    printf("新增公交线路已完成！！！");
}
//修改已有公交线路
//还有改名称后公交线路里面的名称也要改掉；
/*
 * brief:change the property of a point and write to the file
 * input:a correct point name
 *       if you want to change the particular property please input Y else N
 * return: void
 */
void alterPoint() {
    char name[10];
    char newName[10];
    int location;
    printf("请输入要修改的站点名称：");
    scanf("%s", name);
    while(findID_byName(name)==-1){
        //TODO
        printf("未找到站点，请重新输入：");
        scanf("%s",name);
    }
    //save the location of the point that needs to be changed
    location = locate_int(findID_byName(name),allPointId,point_Num);
    //save the first neighbour node
    Neighbour *n=findPoint(findID_byName(name)).first;
    printf("是否要修改名称？[Y/N]:");
    char ins;
    scanf("%c",&ins);
    getchar();
    //need to change the name of the point
    if(ins == 'Y'){
        //TODO
        printf("请输入新名称：");
        scanf("%s",newName);
        // preserve the old name
        char oldName[10];
        strcpy(oldName, allPointName[location]);
        for (int i = 0; i < bus_Num; i++) {
            int need=0;
            LNode* p = (LNode*)malloc(sizeof(LNode));
            p = busRoute[i]->next;
            while (p != NULL) {
                // judge if there is a need to change the bus route
                if (equal_f(p->name, oldName)) {
                    need = 1;
                    // modify the name that corresponds to it
                    strcpy(p->name, newName);
                }
                p = p->next;
            }
            // if there is a need to change the bus route
            if(need){
                char head[20];
                strcpy(head,busRoute[i]->name);
                char **contain=(char**)malloc(sizeof(char*));
                splitComma(head,contain);
                char *fileN = edit_bus_file_name(contain[0]);
                // write to the file of bus
                write_bus(fileN,busRoute[i]);
            }
        }
        strcpy(allPointName[location],newName);
        strcpy(allPoint[location].name,newName);
    }
    // change the distance between a and b
    while(n != NULL){
        printf("是否修改%s到%s的距离？[Y/N]:",allPointName[location],findPoint(n->id).name);
        scanf(" %c",&ins);
        if(ins == 'Y'){
            //TODO
            printf("请输入新距离：");
            float dis;
            scanf("%f",&dis);
            getchar();
            Neighbour *nn=find_Neighbour(allPoint[location].id,findPoint(n->id));
            nn->distance=dis;
            char *fn=edit_point_file_name(n->id);
            write_Point(fn,findPoint(n->id));
            n->distance=dis;
        }
        n=n->next;
    }
    // wirte to the file to the point
    char idS[10];
    sprintf(idS,"%d",findID_byName(newName));
    printf("id is %s",idS);
    char *newFileN=edit_point_file_name(findID_byName(allPointName[location]));
    write_Point(newFileN,allPoint[location]);
    printf("修改站点信息成功\n");
}
//删除站点
/*
 * brief:delete a point and change related point
 * input:a correct point name
 * return: void
 */
void delPoint() {
    char name[10];
    printf("请输入站点名：");
    scanf_s("%s",name);
    //查找该站点是否存在
    while(findID_byName(name) == -1){
        //TODO
        printf("重新输入");
        scanf_s("%s",name);
    }
    //记录站点id
    int id = findID_byName(name);
    int location = locate_int(id,allPointId,point_Num);
    allPointId[location] = -1;
    strcpy(allPointName[location],"null");
    //记录要删除的文件名
    char *delfileN = edit_point_file_name(id);
    //从all文件中删去文件名
    FILE *f=fopen(POINTALLFILENAME,"w+");
    for(int i=0;i<point_Num;i++){
        if(equal_f(pointFileName[i],delfileN) != 1){
            fprintf(f,"%s\n",pointFileName[i]);
        }
    }
    //删除文件
    remove(delfileN);
    //对删除站点的邻居站点进行修改
    Neighbour *n = allPoint[location].first;
    //依次修改邻居站点
    while(n != NULL){
        //delpoint作为point的邻居节点，找出他的前一个和后一个邻居节点
        Neighbour *front,*rear;
        //找出point的第一个邻居节点
        Neighbour *t = allPoint[locate_int(n->id,allPointId,point_Num)].first;
        //找出delpoint对应的邻居节点
        Neighbour *nt =find_Neighbour(id, allPoint[locate_int(n->id,allPointId,point_Num)]);
        //如果delpoint对应的邻居节点是point的首个邻居节点
        if(nt->id == t->id){
            //point的首个邻居节点指向delpoint对应的邻居节点的下一个邻居节点
            allPoint[locate_int(n->id,allPointId,point_Num)].first = nt->next;
        }
        else{
            front = NULL;
            rear = nt->next;
            //找出point邻居节点中next指向delpoint对应的邻居节点
            while(t->id != nt->id){
                //TODO
                front = t;
                t = t->next;
            }
            front->next = rear;
        }
        //修改delpoint的邻居站点的point文件
        char *pointFN = edit_point_file_name(allPoint[locate_int(n->id,allPointId,point_Num)].id);
        write_Point(pointFN, allPoint[locate_int(n->id,allPointId,point_Num)]);
        n = n->next;
    }
    //修改存在delpoint的公交线路
    LNode *del = (LNode*)malloc(sizeof(LNode));
    for(int i=0;i<bus_Num;i++){
        int flag = 0;
        del = busRoute[i]->next;
        //判断该线路内是否有delpoint
        while(del!=NULL){
            if(equal_f(del->name,name)){
                flag = 1;
                break;
            }
            del = del->next;
        }
        if(flag){
            //TODO
            LNode *temp = del->prior;
            del->prior->next = del->next;
            del->next->prior = temp;
            char *fileBN = edit_bus_file_name(busName[i]);
            write_bus(fileBN, busRoute[i]);
        }
    }
    point_Num--;
    //向文件中重新写入站点数
    write_demo();
    printf("删除站点成功");
}

//新增站点
/*
 * brief:add a point and create a new file to store
 * input:a not repeated point name
 *      :neighbour name
 * return: void
 */
void addPoint() {
    char name[10];
    printf("请输入站点名：");
    scanf_s("%s",name);
    while(findID_byName(name) != -1){
        //TODO
        printf("重新输入");
        scanf_s("%s",name);
    }
    allPoint[point_Num].id=allPoint[point_Num-1].id+1;
    allPointId[point_Num]=allPoint[point_Num].id;
    strcpy(allPoint[point_Num].name,name);
    strcpy(allPointName[point_Num],name);
    char neighbourName[10];
    char choice='Y';
    do{
        //TODO
        printf("请输入邻居名称");
        scanf("%s",neighbourName);
        add_neighbor(neighbourName,&allPoint[point_Num]);
        printf("是否继续添加邻居?[Y/N]");
        scanf("%c",&choice);
    }while(choice != 'N');
    char *newFile;
    char allFile[200];
    strcpy(allFile,FILENAME);
    strcat(allFile,"data/point/all.txt");
    newFile = edit_point_file_name(allPointId[point_Num]);
    write_Point(newFile,allPoint[point_Num]);
    append(allFile,newFile);
    printf("error");
    point_Num++;
    write_demo();
    printf("添加站点成功");
}