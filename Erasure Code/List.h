//
//  List.h
//  Erasure Code
//
//  Created by Jerry Wang on 2017/11/21.
//  Copyright © 2017年 Jerry Wang. All rights reserved.
//

#ifndef List_h
#define List_h

#define MAX_SIZE 100
#define INCREMENT_SIZE 10

struct List {
    float * elem;
    int listsize = 0;
    int length = 0;
};

//List dataList;

void initList(List &L);
void addElem(List &L, float elem);
void deleteElem(List &L, float position);
void readList(List &L);
float getElem(List &L, int position);

#endif /* List_h */
