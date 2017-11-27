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

float ** correctDataMatrix;
float ** decodeCheckMatrix;

float ** decodeMatrix_2_3;
float ** decodeMatrix_1_5;
float matrixData_2_3[BLOCK_NUM][BLOCK_NUM] = {
    {1,0,0,0},
    {-1.5,2,2,-0.5},
    {0.5,-3,-1,0.5},
    {0,1,0,0}
};
float matrixData_1_5[BLOCK_NUM][BLOCK_NUM] = {
    {-2,-4,-8,1},
    {1,0,0,0},
    {0,1,0,0},
    {0,0,1,0}
};
int judge = 0;


void initDecodeMatrix(){
    decodeMatrix_1_5 = new float *[BLOCK_NUM];
    decodeMatrix_2_3 = new float *[BLOCK_NUM];
    for (int i = 0 ; i<BLOCK_NUM; i++) {
        decodeMatrix_1_5[i] = new float[BLOCK_NUM];
        decodeMatrix_2_3[i] = new float[BLOCK_NUM];
        for (int j = 0; j<BLOCK_NUM; j++) {
            decodeMatrix_1_5[i][j] = matrixData_1_5[i][j];
            decodeMatrix_2_3[i][j] = matrixData_2_3[i][j];
        }
    }
}


void serializeData(List &tagList){
    
    if(getElem(tagList, 0)>=BLOCK_NUM||getElem(tagList, 1)>=BLOCK_NUM)
        judge=1;
    else
        judge=0;
    correctDataMatrix = new float*[BLOCK_NUM];
    decodeCheckMatrix = new float * [BLOCK_NUM];
    for(int i=0;i<BLOCK_NUM;i++){
        correctDataMatrix[i] = new float[DATA_NUM/BLOCK_NUM];
        decodeCheckMatrix[i] = new float[BLOCK_NUM];
    }
    int block=0;
    //读取数据，形成数据矩阵和编码矩阵
    for (int i =0; i<BLOCK_NUM+ECBLOCK_NUM; i++) {
        if (i != getElem(tagList, 0) && i != getElem(tagList, 1)) {
            List temp;
            initList(temp);
            char * filename = new char [4];
            filename[0] = (char) ((int)'0'+i);
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
            }
            for (int j = 0; j<BLOCK_NUM; j++) {
                decodeCheckMatrix[block][j] = encodeMatrixData[i][j];
            }
            remove(filename);
            block++;
        }
    }
    
    cout<<"编码矩阵："<<endl;
    printMatrix(decodeCheckMatrix, BLOCK_NUM, BLOCK_NUM);
    cout<<"正常数据矩阵："<<endl;
    printMatrix(correctDataMatrix, BLOCK_NUM, DATA_NUM/BLOCK_NUM);
    
}
void decodeToMetaData(){
    initDecodeMatrix();
    metadataMatrix = new float * [BLOCK_NUM];
    for (int i = 0 ; i<BLOCK_NUM; i++) {
        metadataMatrix[i] = new float[DATA_NUM/BLOCK_NUM];
    }
    if (judge==1) {
        metadataMatrix = multiplyMatrix(decodeMatrix_1_5, correctDataMatrix, BLOCK_NUM,BLOCK_NUM,DATA_NUM/BLOCK_NUM);
    }
    else{
        metadataMatrix = multiplyMatrix(decodeMatrix_2_3, correctDataMatrix, BLOCK_NUM,BLOCK_NUM,DATA_NUM/BLOCK_NUM);
    }
    cout<<"恢复元数据："<<endl;
    printMatrix(metadataMatrix, BLOCK_NUM, DATA_NUM/BLOCK_NUM);
}
void encodeMetaData(){
    encodedDataMatrix = new float *[BLOCK_NUM+ECBLOCK_NUM];
    for (int i =0; i<BLOCK_NUM+ECBLOCK_NUM; i++) {
        encodedDataMatrix[i]=new float [DATA_NUM/BLOCK_NUM];
    }
    
    encodedDataMatrix = multiplyMatrix(encodeMatrix, metadataMatrix, (BLOCK_NUM+ECBLOCK_NUM), BLOCK_NUM, (DATA_NUM/BLOCK_NUM));
    
    cout<<"编码数据："<<endl;
    printMatrix(encodedDataMatrix, BLOCK_NUM+ECBLOCK_NUM, DATA_NUM/BLOCK_NUM);
    
}
void recovery(List &tagList){
    
    serializeData(tagList);
    decodeToMetaData();
    encodeMetaData();
    dataDeploy();
}

