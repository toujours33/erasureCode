//
//  decoded.cpp
//  Erasure Code
//
//  Created by Jerry Wang on 2017/11/23.
//  Copyright © 2017年 Jerry Wang. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "functions.h"
using namespace std;

int ** correctDataMatrix;
int ** decodeCheckMatrix;


void serializeData(List &tagList){
    correctDataMatrix = new int*[BLOCK_NUM];
    decodeCheckMatrix = new int * [BLOCK_NUM];
    for(int i=0;i<BLOCK_NUM;i++){
        correctDataMatrix[i] = new int[BLOCK_NUM];
        decodeCheckMatrix[i] = new int[BLOCK_NUM];
    }
    //读取数据，形成数据矩阵和编码矩阵
    for (int i =0; i<BLOCK_NUM+ECBLOCK_NUM; i++) {
        int block=0;
        if (i != getElem(tagList, 0) && i != getElem(tagList, 1)) {
            List temp;
            initList(temp);
            int tag = getElem(tagList, i);
            char * filename = new char [4];
            filename[0] = (char) ((int)'0'+tag);
            ifstream infile(filename);
            if(!infile.is_open()){
                cout<<"文件打开失败"<<endl;
                exit(0);
            }
            while (!infile.eof()) {
                char * buffer = new char[256];
                infile.getline(buffer, 256);
                dataPrepare(temp, buffer);
            };
            for (int j = 0 ;j<DATA_NUM/BLOCK_NUM; j++) {
                correctDataMatrix[block][j] = getElem(temp, j);
                decodeCheckMatrix[block][j] = encodeMatrixData[i][j];
            }
            block++;
        }
    }
}
int ** decodeToMetaData();
int ** encodeMetaData();
void recovery(List &tagList){
    
    serializeData(tagList);
    decodeToMetaData();
    encodeMetaData();
    
}
