//
//  prepare.cpp
//  Erasure Code
//
//  Created by Jerry Wang on 2017/11/21.
//  Copyright © 2017年 Jerry Wang. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "functions.h"
using namespace std;

#define MEATDATA "metadata.txt"

List dataList;
DataBlock dataBlocks[4];
DataBlock ecBlocks[2];
float ** metadataMatrix;
float ** encodeMatrix;
float ** encodedDataMatrix;
float encodeMatrixData[BLOCK_NUM+ECBLOCK_NUM][BLOCK_NUM] = {
    {1,0,0,0},
    {0,1,0,0},
    {0,0,1,0},
    {0,0,0,1},
    {1,1,1,1},
    {1,2,4,8}
};

//随机生成原始数据，分割为4*6的原始数据块
void dataInitial(){
    ifstream file(MEATDATA);
    if(!file){
        ofstream file(MEATDATA);
        for (int i=0; i<24; i++) {
            file<<Random(10)<<" ";
        }
        file.close();
    }
    else{
        cout<<"元数据已创建"<<endl;
    }
    metadataMatrix = new float * [BLOCK_NUM];
    for (int i = 0; i<BLOCK_NUM; i++) {
        metadataMatrix[i]=new float[DATA_NUM/BLOCK_NUM];
    }
    encodeMatrix = new  float * [BLOCK_NUM+ECBLOCK_NUM];
    for (int i = 0; i<BLOCK_NUM+ECBLOCK_NUM; i++) {
        encodeMatrix[i]= new float [BLOCK_NUM];
        for (int j=0; j<BLOCK_NUM; j++) {
            encodeMatrix[i][j]=encodeMatrixData[i][j];
        }
    }
}

void dataPrepare(List &L, char * buffer){
    const char * split = " ";
    char * value = strtok(buffer, split);
    while (value!=NULL) {
        float metadata;
        sscanf(value, "%f",&metadata);
        addElem(L, metadata);
        value = strtok(NULL, split);
    }
}

void dataPartition(){
    //将元数据从文件中读出，并转换为int数组,存储于dataList中
    ifstream file(MEATDATA);
    char * buffer;
    if (!file.is_open()) {
        cout<<"文件打开失败！"<<endl;
        exit(0);
    }
    else{
        initList(dataList);
        while (!file.eof()) {
            buffer = new char[256];
            file.getline(buffer, 256);
            dataPrepare(dataList, buffer);
        }
    }
    
    //数据分片，以4个数据块为例,并构建元数据矩阵（4*6）
    const int dataNum =dataList.length/BLOCK_NUM;
    for (int i = 0; i<BLOCK_NUM; i++) {
        initDataBlock(dataBlocks[i], i, dataNum, dataList);
        for (int j=0; j<dataNum; j++) {
            metadataMatrix[i][j]=dataBlocks[i].dataSet.elem[j];
        }
    }
    cout<<"元数据矩阵："<<endl;
    printMatrix(metadataMatrix, BLOCK_NUM, DATA_NUM/BLOCK_NUM);
    
    encodedDataMatrix = new float *[BLOCK_NUM+ECBLOCK_NUM];
    for (int i =0; i<BLOCK_NUM+ECBLOCK_NUM; i++) {
        encodedDataMatrix[i]=new float [DATA_NUM/BLOCK_NUM];
    }
    
    encodedDataMatrix = multiplyMatrix(encodeMatrix, metadataMatrix, (BLOCK_NUM+ECBLOCK_NUM), BLOCK_NUM, (DATA_NUM/BLOCK_NUM));
    
    cout<<"编码数据："<<endl;
    printMatrix(encodedDataMatrix, BLOCK_NUM+ECBLOCK_NUM, DATA_NUM/BLOCK_NUM);
    
    for (int i =0;i<ECBLOCK_NUM; i++) {
        ecBlocks[i].tag= BLOCK_NUM+i+1;
        initList(ecBlocks[i].dataSet);
        for (int j=0; j<DATA_NUM/BLOCK_NUM; j++) {
            addElem(ecBlocks[i].dataSet, encodedDataMatrix[i][j]);
        }
    }
}

//保存数据段在不同的文件中，使用tag命名

void dataDeploy(){
    for (int i =0; i<BLOCK_NUM+ECBLOCK_NUM; i++) {
        char* filename;
        filename = new char [1];
        filename[0] = char((int)'0'+i);
        ifstream infile(filename);
        if (infile) {
            cout<<"文件已存在，准备删除并重新创建数据文件"<<endl;
            remove(filename);
        }
        ofstream outfile(filename);
        for (int j=0; j<DATA_NUM/BLOCK_NUM; j++) {
            outfile<<encodedDataMatrix[i][j]<<" ";
        }
        outfile.close();
    }
    deleteMatrix(metadataMatrix, BLOCK_NUM);
    deleteMatrix(encodedDataMatrix, BLOCK_NUM+ECBLOCK_NUM);
}

