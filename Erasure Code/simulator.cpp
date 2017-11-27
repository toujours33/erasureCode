//
//  simulator.cpp
//  Erasure Code
//
//  Created by Jerry Wang on 2017/11/23.
//  Copyright © 2017年 Jerry Wang. All rights reserved.
//

#include <iostream>
#include "functions.h"

void simulator(){
    List tagList;
    char * filename;
    //1.数据块和校验块分别丢失一个数据块
    initList(tagList);
    int dataBlock=0,ecBlock=0;
    addElem(tagList, dataBlock);
    addElem(tagList, ecBlock+BLOCK_NUM);
    //删除数据块对应的文件，模拟失效
    filename = new char[1];
    filename[0]=(char) ((int)'0'+dataBlock);
    remove(filename);
    delete [] filename;
    filename = new char[1];
    filename[0]=(char)((int)'0'+ecBlock+BLOCK_NUM);
    remove(filename);
    delete [] filename;
    
    recovery(tagList);
    
    //2.数据块丢失两个数据块
    initList(tagList);
    int * dataBlocks = new int[2];
    dataBlocks[0]=1;
    dataBlocks[1]=2;
    addElem(tagList, dataBlocks[0]);
    addElem(tagList, dataBlocks[1]);
    //删除数据块对应的文件，模拟失效
    for (int i =0; i<2; i++) {
        filename = new char[1];
        filename[0]=(char) ((int)'0'+dataBlocks[i]);
        remove(filename);
        delete [] filename;
    }
    
    recovery(tagList);
}

