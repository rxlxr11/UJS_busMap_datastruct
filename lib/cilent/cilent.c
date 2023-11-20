#include "cilent.h"

//输入字符串，返回在字符串数组中的位置
int locate(char *s){
    int a, i = 0;
    while(busName[i] != NULL && i < bus_Num){
        a=strcmp(s,busName[i]);
        if(a==0){
            return i;
        }
        i++;
    }
    return -1;
}

void selectionSort(float *num, int arrLength,int *index) {
    float *x = num;
    float temp_num  = 0;
    int min = 0;
    int temp_index = 0;
    for (int i = 0; i < arrLength - 1; i++) {
        min = i;
        // 循环查找最小值
        for (int j = i + 1; j < arrLength; j++) {
            if (*(x+min) > *(x+j)) {
                min = j;
            }
        }
        if (min != i) {
            temp_num = *(num+i);
            *(num+i) = *(num+min);
            *(num+min) = temp_num;

            temp_index = *(index+i);
            *(index+i) = *(index+min);
            *(index+min) = temp_index;
        }
    }
}


float time_f(char* route,float dist){
    int flag = equal_f(route,"z");
    if(flag == 1)
        return dist/HUMANV;
    return dist/BUSV;
}

int change_f(char* route1,char* route2){
    int flag = equal_f(route1,route2);
    int flag2 = equal_f(route2,"z");
    if(flag != 1 && flag2 != 1){
        return 1;
    }
    return 0;
}

float price_f(char *route){
    float price = 0;
    int index = locate(route);
    if (index != -1)
        price = busPrice[index];
    return price;
}

void copyHead(headN* source, headN* dest){
    dest->start = source->start;
    strcpy(dest->name,source->name);
    dest->node = source->node;
    dest->distance = source->distance;
    dest->time = source->time;
    dest->price = source->price;
    dest->change = source->change;
}
//尾插法
void insert_wayNode(headN *n,int id,char *name,char *route,float distance){
    wayNode *x=(wayNode*)malloc(sizeof(wayNode));
    x->id=id;
    strcpy(x->name,name);
    strcpy(x->route,route);
    x->next=NULL;
    if(n->next!=NULL)
    {
        wayNode *t=(wayNode*)malloc(sizeof(wayNode));
        t = n->next;
        while(t->next!=NULL){
            t=t->next;
        }
        t->next = x;
        //if change bus
        if(change_f(t->route,route)){
            n->change++;
            n->price += price_f(route);
        }
    } else{
        n->next = x;
        if(equal_f(route,"z")!=1){
            n->change++;
            n->price += price_f(route);
        }
    }
    n->time += time_f(route,distance);
    n->node++;
    n->distance+=distance;

}

void copy_way(headN *source,headN *wcopy){
    wcopy->next=NULL;
    wayNode *wc=(wayNode*)malloc(sizeof(wayNode));
    wc=source->next;
    while(wc!=NULL){
        insert_wayNode(wcopy,wc->id,wc->name,wc->route,0);
        wc=wc->next;
    }
    copyHead(source,wcopy);
}

headN* createWay(int start, char* start_name) {
    headN *n;
    n = (headN *)malloc(sizeof(headN ));
    n->start = start;
    strcpy(n->name , start_name);
    n->next = NULL;
    n->distance = 0;
    n->change = 0;
    n->price = 0;
    n->time = 0;
    n->node = 1;
    return n;
}

void printWay(headN *h){
    printf("+－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－+\n");
    printf(" distance: %.2f m\n "
           "time:     %.2f min\n "
           "price:    %.2f RMB\n "
           "乘车次数:   %d\n",
           h->distance,h->time,h->price,h->change);
    printf(" %s", h->name);
    wayNode* n = h->next;
    while(n != NULL){
        printf("--%s-->",n->route);
        printf("%s",n->name);
        n=n->next;
    }
    printf("\n");
    printf("+－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－+\n");
}
//查询经过该点的所有公交路线
/*
 * brief:query bus routes which pass by the particular point
 * input:a correct point name
 * return: void
 */
void point_Bus() {
    char temp[10];
    int equal;
    printf("请输入站点名:");
    scanf("%s", temp);
    for (int i = 0; i < point_Num; i++) {
        equal = strcmp(temp, allPointName[i]);
        if (equal == 0) {
            break;
        }
    }
    int find_if = 0;
    if (equal != 0) {
        printf("未找到站点\n");
        return;
    } else {
        for (int i = 0; i < bus_Num; i++) {
            LNode* p = (LNode*)malloc(sizeof(LNode));
            p = busRoute[i]->next;
            while (p != NULL) {
                int equal_2 = equal_f(p->name, temp);
                if (equal_2) {
                    find_if = 1;
                    printBus(busRoute[i]);
                    break;
                } else {
                    p = p->next;
                }
            }
        }
        if (!find_if) {
            printf("没有经过该点的公交\n");
        }
    }
}
//所有公交路线
/*
 * brief:query all bus routes
 * input:void
 * return: void
 */
void allBus(){
    for(int i=0;i<bus_Num;i++){
        printBus(busRoute[i]);
    }
}
//所有可达路线
int allRoute(headN *allWay[10],int start,int end) {

    Neighbour *n;
    Point start_p1, p2, p, end_p;
    //routeCount:the number of route
    int  i = 0, routeCount = 0;
    int flag = 0;
    //the number of point
    int start1_num = 0;
    int end1_num = 0;
    int start2_num[10];
    int end2_num[10];
    //the id of the neighbour of start/end
    int start_1[10], end_1[10];
    start_1[0] = start;
    end_1[0] = end;
    int start_2[10][10], end_2[10][10];

    start_p1 = findPoint(start);
    end_p = findPoint(end);
    char startN[20];
    char endN[20];
    strcpy(startN,start_p1.name);
    strcpy(endN,end_p.name);

    //store all route
    for (int i = 0; i < 10; i++) {
        allWay[i] = createWay(start,startN);
    }


    i = 0;
    end_p = findPoint(end);
    n = start_p1.first;
    //起点第一次
    while (n != NULL) {
        //TODO
        start_1[++i] = n->id;
        n = n->next;
    }
    start1_num = i;
    for (; i >= 1; i--) {

        if (start_1[i] == end) {
            //TODO
            Neighbour *n = find_Neighbour(end, start_p1);
            //time[routeCount] = time_f(n->route,n->distance);
            insert_wayNode(allWay[routeCount], n->id, endN, n->route,n->distance);
            //printWay(allWay[routeCount]);
            start_1[i] = -1;
            routeCount++;
            break;
        }
    }
    int same[10];
    //从终点的搜索不可能有起点
    i = 0;
    //终点第一次
    n = end_p.first;
    while (n != NULL) {
        if(n->id!=start){
            end_1[++i] = n->id;
        }
        n = n->next;
    }
    //2条
    end1_num = i;
    int same_num = findSame(start_1, end_1, same, start1_num + 1, end1_num + 1);
    for (i = 0; i < same_num; i++) {
        Point pt = findPoint(same[i]);
        Neighbour *nt = find_Neighbour(same[i], start_p1);
        insert_wayNode(allWay[routeCount], same[i], pt.name, nt->route,nt->distance);
        //time[routeCount] = time_f(nt->route,nt->distance);
        nt = find_Neighbour(end, pt);
        insert_wayNode(allWay[routeCount], end, endN, nt->route,nt->distance);
        //time[routeCount] += time_f(nt->route,nt->distance);
        //printWay(allWay[routeCount]);
        routeCount++;
        for (int j = 0; j < start1_num; j++) {
            if (start_1[j] == same[i]) {
                start_1[j] = -1;
                break;
            }
        }
        for (int j = 0; j < end1_num; j++) {
            if (end_1[j] == same[i]) {
                end_1[j] = -1;
                break;
            }
        }
    }
    //找起点的邻居节点的邻居节点
    //若终点和起点有公共邻居，则将该邻居从数组中取出，表示已经找到经过该邻居站点最少的路径
    //reindex是根据邻居数组确定新的下标
    int reIndex = 0;
    for (i = 1; i <= start1_num; i++) {
        int j = 0;
        if (start_1[i] != -1) {

            p = findPoint(start_1[i]);
            n = p.first;
            start_2[reIndex][j++] = start_1[i];
            while (n != NULL) {

                if (n->id != start) {
                    start_2[reIndex][j++] = n->id;
                }
                n=n->next;
            }
            start2_num[reIndex] = j;
            reIndex++;
        }
    }
    //find 计找到的点的id
    int cnt=0;
    int find[10];
    for (i = 0; i < reIndex; i++) {
        same_num = findSame(start_2[i], end_1, same, start2_num[i], end1_num + 1);
        for (int j = 0; j < same_num; j++) {

            Point pt = findPoint(start_2[i][0]);
            Neighbour *nt = find_Neighbour(start_2[i][0], start_p1);
            insert_wayNode(allWay[routeCount], start_2[i][0], pt.name, nt->route,nt->distance);
            //time[routeCount] = time_f(nt->route,nt->distance);
            nt = find_Neighbour(same[j], pt);
            pt = findPoint(same[j]);
            insert_wayNode(allWay[routeCount], same[j], pt.name, nt->route,nt->distance);
            //time[routeCount] += time_f(nt->route,nt->distance);
            nt = find_Neighbour(end, pt);
            insert_wayNode(allWay[routeCount], end, endN, nt->route,nt->distance);
            routeCount++;
            //time[routeCount] += time_f(nt->route,nt->distance);
            //printWay(allWay[routeCount++]);
            find[cnt++]=same[j];
        }
    }
    for(int m=0;m<reIndex;m++){

        for(int n=0;n<start2_num[m];n++){
            for(int k=0;k<cnt;k++){
                if(find[k]==start_2[m][n]){
                    start_2[m][n]=-1;
                }
            }
        }
    }
//    for (int m = 0; m < end1_num; ++m) {
//        for(int k=0;k<cnt;k++){
//            if(find[k]==end_1[m]){
//                end_1[m] = -1;
//            }
//        }
//    }

    int reIndex2 = 0;
    for (i = 1; i <= end1_num; i++) {
        //TODO
        int j = 0;
        if (end_1[i] != -1) {
            p = findPoint(end_1[i]);
            n = p.first;
            end_2[reIndex2][j++] = end_1[i];
            while (n != NULL) {

                if (n->id != end) {
                    end_2[reIndex2][j++] = n->id;
                }
                n = n->next;
            }
            end2_num[reIndex2] = j;
            reIndex2++;
        }
    }
    for (i = 0; i < reIndex; i++) {
        for (int j = 0; j < reIndex2; j++) {
            same_num = findSame(start_2[i], end_2[j], same, start2_num[i], end2_num[j]);

            for (int k = 0; k < same_num; k++) {
                Neighbour *nt = find_Neighbour(start_2[i][0], start_p1);
                Point pt = findPoint(start_2[i][0]);
                insert_wayNode(allWay[routeCount], nt->id, pt.name, nt->route,nt->distance);
//                time[routeCount] = time_f(nt->route,nt->distance);
                nt = find_Neighbour(same[k], pt);
                pt = findPoint(same[k]);
                insert_wayNode(allWay[routeCount], nt->id, pt.name, nt->route,nt->distance);
//                time[routeCount] += time_f(nt->route,nt->distance);
                nt = find_Neighbour(end_2[j][0], pt);
                pt = findPoint(end_2[j][0]);
                insert_wayNode(allWay[routeCount], nt->id, pt.name, nt->route,nt->distance);
//                time[routeCount] += time_f(nt->route,nt->distance);
                nt = find_Neighbour(end, pt);
                insert_wayNode(allWay[routeCount], nt->id, endN, nt->route,nt->distance);
                routeCount++;
//                time[routeCount] += time_f(nt->route,nt->distance);
                //printWay(allWay[routeCount++]);
            }
        }
    }
    return routeCount;
}

//最短路线
void shortRoute(Point start, headN *allWay[point_Num]) {
    int i;
    Neighbour *n;
    n = start.first;
    int FindPoint[point_Num];
    float dist[point_Num];
    for (i = 0; i < point_Num; i++) {
        allWay[i] = (wayNode*)malloc(sizeof(wayNode));
        FindPoint[i] = 0;
        dist[i] = MAX;
        allWay[i]->start = start.id;
        strcpy(allWay[i]->name, start.name);
        allWay[i]->next = NULL;
    }
    while (n != NULL) {
        dist[locate_int(n->id, allPointId, point_Num)] = n->distance;
        Point pName = findPoint(n->id);
        insert_wayNode(allWay[locate_int(n->id, allPointId, point_Num)], n->id, pName.name, n->route,n->distance);
        n = n->next;
    }
    FindPoint[locate_int(start.id, allPointId, point_Num)] = 1;
    int v = locate_int(start.id, allPointId, point_Num);
    for (i = 0; i < point_Num - 1; i++) {
        int min = MAX;
        int u = v;
        for (int j = 0; j < point_Num; j++) {
            if (!FindPoint[j] && dist[j] < min) {
                u = j;
                min = dist[j];
            }
        }
        FindPoint[u] = 1;
        Point p = findPoint(allPointId[u]);
        n = p.first;
        while (n != NULL) {
            if (n->distance + dist[u] < dist[locate_int(n->id, allPointId, point_Num)] && !FindPoint[locate_int(n->id, allPointId, point_Num)]) {
                dist[locate_int(n->id, allPointId, point_Num)] = n->distance + dist[u];
                copy_way(allWay[u], allWay[locate_int(n->id, allPointId, point_Num)]);
                Point pName = findPoint(n->id);
                insert_wayNode(allWay[locate_int(n->id, allPointId, point_Num)], n->id, pName.name, n->route,n->distance);
            }
            n = n->next;
        }
    }
}

//best
void bestRoute(headN *allWay[10],int start,int end){
    int count = allRoute(allWay,start,end);
    float time[count],price[count],distance[count];
    int change[count];
    int time_index[count],price_index[count],distance_index[count],change_index[count];
    for (int i = 0; i < count; i++) {
        time[i] = allWay[i]->time;
        price[i] = allWay[i]->price;
        distance[i] = allWay[i]->distance;
        change[i] = allWay[i]->change;
        time_index[i] = i;
        price_index[i] = i;
        distance_index[i] = i;
        change_index[i] = i;
    }
    selectionSort(time,count,time_index);
    selectionSort(price,count,price_index);
    selectionSort(distance,count,distance_index);
    selectionSort(change,count,change_index);
    printf("最少时间\n");
    printWay(allWay[time_index[0]]);
    printf("最少价钱\n");
    printWay(allWay[price_index[0]]);
    printf("最短距离\n");
    printWay(allWay[distance_index[0]]);
    printf("最少乘车\n");
    printWay(allWay[change_index[0]]);
}
//最少时间
//void leastTime(Point start, wayNode *allWay[point_Num]) {
//    int i;
//    Neighbour *n;
//    n = start.first;
//    int FindPoint[point_Num];
//    float time[point_Num];
//    for (i = 0; i < point_Num; i++) {
//
//        allWay[i] = (wayNode*)malloc(sizeof(wayNode));
//        FindPoint[i] = 0;
//        time[i] = MAX;
//        allWay[i]->id = start.id;
//        strcpy(allWay[i]->name, start.name);
//        allWay[i]->next = NULL;
//    }
//    while (n != NULL) {
//
//        time[locate_int(n->id, allPointId, point_Num)] = time_f(n->route,n->distance);
//        Point pName = findPoint(n->id);
//        insert_wayNode(allWay[locate_int(n->id, allPointId, point_Num)], n->id, pName.name, n->route,n->distance);
//        n = n->next;
//    }
//    FindPoint[locate_int(start.id, allPointId, point_Num)] = 1;
//    int v = locate_int(start.id, allPointId, point_Num);
//    for (i = 0; i < point_Num - 1; i++) {
//        int min = MAX;
//        int u = v;
//        for (int j = 0; j < point_Num; j++) {
//
//            if (!FindPoint[j] && time[j] < min) {
//                u = j;
//                min = time[j];
//            }
//        }
//        FindPoint[u] = 1;
//        Point p = findPoint(allPointId[u]);
//        n = p.first;
//        while (n != NULL) {
//            float x = time_f(n->route,n->distance);
//
//            if (x + time[u] < time[locate_int(n->id, allPointId, point_Num)] && !FindPoint[locate_int(n->id, allPointId, point_Num)]) {
//
//                time[locate_int(n->id, allPointId, point_Num)] = x + time[u];
//                copy_way(allWay[u], allWay[locate_int(n->id, allPointId, point_Num)]);
//                Point pName = findPoint(n->id);
//                insert_wayNode(allWay[locate_int(n->id, allPointId, point_Num)], n->id, pName.name, n->route,n->distance);
//            }
//            n = n->next;
//        }
//    }
//}
//最少换乘
//void least_Change(int start,int end) {
//
//    int leastChaneCnt = MAX;
//    char routeT1[20];
//    char routeT2[20];
//    wayNode *change[10];
//    int count = allRoute(change,start,end);
//    int changeCount[count];
//
//    headN *w = createWay(start);
//    headN *leastChangeWay = createWay(start);
//
//    for (int i = 0; i < count; i++) {
//        //TODO
//        int cnt = 0;
//        w = change[i]->next;
//        while (w->next != NULL) {
//            //TODO
//            char **ss1;
//            char **ss2;
//            ss1 = (char**)malloc(sizeof(char*));
//            ss2 = (char**)malloc(sizeof(char*));
//            strcpy(routeT2, w->next->route);
//            strcpy(routeT1, w->route);
//            int cnt1 = splitComma(routeT1, ss1);
//            int cnt2 = splitComma(routeT2, ss2);
//            int flag = 0;
//            for (int j = 0; j < cnt1; j++) {
//                //TODO
//                for (int k = 0; k < cnt2; k++) {
//                    if (equal_f(ss1[j], ss2[k])) {
//                        //TODO
//                        flag = 1;
//                        break;
//                    }
//                }
//                if (flag)
//                    //TODO
//                    break;
//            }
//            if (!flag)
//                cnt++;
//            w = w->next;
//        }
//        changeCount[i] = cnt;
//        if (changeCount[i] < leastChaneCnt) {
//            //TODO
//            copy_way(change[i], leastChangeWay);
//        }
//    }
//    printWay(leastChangeWay);
//}

void Dijkstra(Point start, wayNode *allWay[point_Num]) {
    int i;
    Neighbour *n;
    n = start.first;
    int FindPoint[point_Num];
    float dist[point_Num];
    // init the way and the distance from start to other points
    for (i = 0; i < point_Num; i++) {
        allWay[i] = (wayNode*)malloc(sizeof(wayNode));
        FindPoint[i] = 0;
        dist[i] = MAX;
        allWay[i]->id = start.id;
        strcpy(allWay[i]->name, start.name);
        allWay[i]->next = NULL;
    }
    // assign corresponding data to the neighbour of the starting point
    while (n != NULL) {
        dist[locate_int(n->id, allPointId, point_Num)] = n->distance;
        Point pName = findPoint(n->id);
        insert_wayNode(allWay[locate_int(n->id, allPointId, point_Num)], n->id, pName.name, n->route,n->distance);
        n = n->next;
    }
    // the start has been found
    FindPoint[locate_int(start.id, allPointId, point_Num)] = 1;
    int v = locate_int(start.id, allPointId, point_Num);
    // seek the shortest path from start to each of the other points in turn
    for (i = 0; i < point_Num - 1; i++) {
        int min = MAX;
        int u = v;
        // seek the samllest distance
        for (int j = 0; j < point_Num; j++) {
            if (!FindPoint[j] && dist[j] < min) {
                u = j;
                min = dist[j];
            }
        }
        // set findPoint[u] equal to be 1
        FindPoint[u] = 1;
        Point p = findPoint(allPointId[u]);
        n = p.first;
        /*
          Start from the point with the shortest distance found this time to
          the neighbour point which the shortest route has not yet been found
          Determine whether the new distance is smaller than the original distance.
          If it is smaller, modify the path and distance
         */
        while (n != NULL) {
            if (n->distance + dist[u] < dist[locate_int(n->id, allPointId, point_Num)] && !FindPoint[locate_int(n->id, allPointId, point_Num)]) {
                dist[locate_int(n->id, allPointId, point_Num)] = n->distance + dist[u];
                copy_way(allWay[u], allWay[locate_int(n->id, allPointId, point_Num)]);
                Point pName = findPoint(n->id);
                insert_wayNode(allWay[locate_int(n->id, allPointId, point_Num)], n->id, pName.name, n->route,n->distance);
            }
            n = n->next;
        }
    }
}
//环线
void cycle(){
    int count=0;
    for(int i=0;i<bus_Num;i++){
        //TODO
        LNode* p=(LNode*)malloc(sizeof(LNode));
        p=busRoute[i];
        p=p->next;
        while(p->next!=NULL){
            //TODO
            int e=equal_f(p->name,p->next->name);
            if(e){
                printf("%s是环线",busRoute[i]->name);
                count++;
                break;
            }
            p=p->next;
        }
    }
    if(!count)
        printf("无环线\n");
    else
        printf("共有%d条环线\n",count);
}
