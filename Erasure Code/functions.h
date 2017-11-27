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
#define Random(x) (float)(rand()%x)

#define DATA_NUM 24
#define BLOCK_NUM 4
#define ECBLOCK_NUM 2

extern float ** metadataMatrix;
extern float ** encodeMatrix;
extern float ** encodedDataMatrix;
extern float encodeMatrixData[BLOCK_NUM+ECBLOCK_NUM][BLOCK_NUM];

//数据准备工作，包括初始化数据和数据分片，元数据编码
//数据初始化，随机生成数据，写入metadata.txt
void dataInitial();
//数据分片，从文件读取
void dataPartition();
//数据分片预处理，格式化从文件读取的数据
void dataPrepare(List &L,char * buffer);
//数据编码
void erasureCode();
//数据部署
void dataDeploy();
//清除元数据矩阵，编码之后的数据矩阵，保留编码矩阵



//矩阵运算
void printMatrix(float **m1,int row,int col);
//void printMatrix(double ** m1,int row,int col);
float ** addMatrix(float **m1,float **m2,int row,int col);
float ** multiplyMatrix(float **m1,float **m2,int row,int col1,int col2);
float ** reverseMatirx(float **m1,int row,int col);
void deleteMatrix(float **m1,int row);
//int ** multiplyMatrix_double_int(float **m1,float **m2,int row);

//模拟服务器宕机（文件丢失）
void simulator();

//解码过程
//解码调用方法，入口参数：失效数据块号
void recovery(List &tagList);
//获取幸存的数据，构成数据矩阵，并获取解码矩阵M
void serializeData(List &tagList);
//依据数据矩阵和解码矩阵，求出原始数据矩阵，重构metadataMatrix
void decodeToMetaData();
//编码元数据矩阵，构成完整的数据矩阵
void  encodeMetaData();


void testSplit();

struct dataBlock{
    int blockNun;
    int * data;
};


#endif /* functions_h */
