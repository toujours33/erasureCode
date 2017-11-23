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
    int * elem;
    int listsize = 0;
    int length = 0;
};

//List dataList;

void initList(List &L);
void addElem(List &L, int elem);
void deleteElem(List &L, int position);
void readList(List &L);
int getElem(List &L, int position);

#endif /* List_h */
