//
//  functions.h
//  Erasure Code
//
//  Created by Jerry Wang on 2017/11/21.
//  Copyright © 2017年 Jerry Wang. All rights reserved.
//

#ifndef functions_h
#include "List.h"
#include "dataBlock.hpp"
#define functions_h
#define COL 6
#define ROW 4
#define Random(x) (rand()%x)

#define DATA_NUM 24
#define BLOCK_NUM 4
#define ECBLOCK_NUM 2

extern int ** metadataMatrix;
extern int ** encodeMatrix;
extern int ** encodedDataMatrix;
extern int encodeMatrixData[BLOCK_NUM+ECBLOCK_NUM][BLOCK_NUM];

//数据准备工作，包括初始化数据和数据分片，元数据编码
void dataInitial();
void testReadData();
void dataPartition();
void dataPrepare(List &L,char * buffer);
void erasureCode();
void dataDeploy();
//清除元数据矩阵，编码之后的数据矩阵，保留编码矩阵


//矩阵运算
void printMatrix(int **m1,int row,int col);
int ** addMatrix(int **m1,int **m2,int row,int col);
int ** multiplyMatrix(int **m1,int **m2,int row,int col1,int col2);
int ** reverseMatirx(int **m1,int row,int col);
void deleteMatrix(int **m1,int row);

//模拟服务器宕机（文件丢失）
void simulator();

//解码过程
//获取幸存的数据，构成数据矩阵，并获取解码矩阵M
void serializeData(List &tagList);
//依据数据矩阵和解码矩阵，求出原始数据矩阵，重构metadataMatrix
int ** decodeToMetaData();
//编码元数据矩阵，构成完整的数据矩阵
int ** encodeMetaData();
void recovery(List &tagList);

void testSplit();

struct dataBlock{
    int blockNun;
    int * data;
};


#endif /* functions_h */
