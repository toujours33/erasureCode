//
//  matrixOperation.cpp
//  Erasure Code
//
//  Created by Jerry Wang on 2017/11/22.
//  Copyright © 2017年 Jerry Wang. All rights reserved.
//

#include <iostream>
using namespace std;

void printMatrix(int **m1,int row,int col){
    for (int i=0; i<row; i++) {
        for (int j=0; j<col; j++) {
            cout<<m1[i][j]<<" ";
        }
        cout<<endl;
    }
}
int ** addMatrix(int **m1,int **m2,int row,int col){
    int ** result ;
    result = new int* [row];
    for (int i=0; i<row; i++) {
        result[i] = new int[col];
    }
    for(int i=0;i<row;i++){
        for (int j=0; j<col; j++) {
            result[i][j]=m1[i][j]+m2[i][j];
        }
    }
    return result;
}
int ** multiplyMatrix(int **m1,int **m2,int row,int col1,int col2){
    int ** result ;
    result = new int* [row];
    for (int i=0; i<row; i++) {
        result[i] = new int[col2];
    }
    for (int i=0; i<row; i++) {
        for (int j=0; j<col2; j++) {
            result[i][j]=0;
            for (int k=0; k<col1; k++) {
                result[i][j]+=m1[i][k]*m2[k][j];
            }
        }
    }
    
    return result;
}

void deleteMatrix(int **m1,int row){
    for (int i=row-1; i>=0; i--) {
        delete [] m1[i];
    }
    delete [] m1;
}

int ** reverseMatirx(int **m1,int row,int col){
    int ** result;
    
    return result;
    
}

