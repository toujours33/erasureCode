//
//  ListOperation.cpp
//  Erasure Code
//
//  Created by Jerry Wang on 2017/11/21.
//  Copyright © 2017年 Jerry Wang. All rights reserved.
//


#include <iostream>
#include <stdlib.h>
#include "List.h"

using namespace std;

void initList(List &L){
    L.elem = (float *)malloc(sizeof(float)*MAX_SIZE);
    L.listsize=MAX_SIZE;
    L.length=0;
}
void addElem(List &L,float elem){
    if (L.length>=L.listsize) {
        L.elem = (float *)realloc(L.elem, sizeof(float)*(INCREMENT_SIZE+L.listsize));
    }
    L.elem[L.length]=elem;
    L.length++;
}
void deleteElem(List &L, int position){
    for (int i = position; i<L.length-1; i++) {
        L.elem[i]=L.elem[i+1];
    }
    L.length--;
}
void readList(List &L){
    for (int i=0; i<L.length; i++) {
        cout<<getElem(L, i)<<endl;
    }
}
float getElem(List &L, int position){
    return L.elem[position];
}

