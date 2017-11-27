//
//  matrixOperation.cpp
//  Erasure Code
//
//  Created by Jerry Wang on 2017/11/22.
//  Copyright © 2017年 Jerry Wang. All rights reserved.
//

#include <iostream>
using namespace std;

void printMatrix(float **m1,int row,int col){
    for (int i=0; i<row; i++) {
        for (int j=0; j<col; j++) {
            cout<<m1[i][j]<<" ";
        }
        cout<<endl;
    }
}
float ** addMatrix(float **m1,float **m2,int row,int col){
    float ** result ;
    result = new float* [row];
    for (int i=0; i<row; i++) {
        result[i] = new float[col];
    }
    for(int i=0;i<row;i++){
        for (int j=0; j<col; j++) {
            result[i][j]=m1[i][j]+m2[i][j];
        }
    }
    return result;
}
float ** multiplyMatrix(float **m1,float **m2,int row,int col1,int col2){
    float ** result ;
    result = new float* [row];
    for (int i=0; i<row; i++) {
        result[i] = new float[col2];
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
void deleteMatrix(float **m1,int row){
    for (int i=row-1; i>=0; i--) {
        delete [] m1[i];
    }
    delete [] m1;
}

float ** reverseMatirx(float **m1,int row,int col){
    float ** result;
    
    float ** L = new float *[row];
    float ** L_reverse = new float *[row];
    float ** U = new float *[row];
    float ** U_reverse = new float *[row];
    //1.初始化L，U矩阵
    for(int i = 0;i<row;i++){
        L[i]=new float[row];
        L_reverse[i] = new float[row];
        L[i][i]=1.0;//下三角单位矩阵
        U[i]=new float[row];
        U_reverse[i] = new float[row];
    }
    //2.求U矩阵第一行
    for (int i =0; i<row; i++) {
        U[0][i]=m1[0][i];
    }
    //3.求L矩阵第一列
    for (int i = 1; i<row; i++) {
        L[i][0]=m1[i][0]/U[0][0];
    }
    for (int i =1 ; i<row;i++) {
        //4.求U矩阵的i行元素
        for (int j=i; j<row; j++) {
            float sum =0.0;
            for (int k =0; k<i; k++) {
                sum += (L[i][k]*U[k][j]);
            }
            U[i][j] = m1[i][j]-sum;
        }
        //5.求L矩阵的i列元
        for (int j = i+1; j<row; j++) {
            float sum = 0.0;
            for (int k = 0; k<i; k++) {
                sum += (L[j][k]*U[k][i]);
            }
            L[j][i] = (m1[j][i]-sum)/U[i][i];
        }
        for (int j = 1; j<row; j++) {
            if (j>i) {
                L[i][j]=0.0;
                U[j][i]=0.0;
            }
        }
    }
    cout<<"L 矩阵："<<endl;
    printMatrix(L, row, row);
    cout<<"U 矩阵："<<endl;
    printMatrix(U, row, row);
    
    cout<<"LU 矩阵的积："<<endl;
    printMatrix(multiplyMatrix(L, U, row,row,row), row, row);
    
    //求L，U矩阵的逆矩阵
    for (int i =0; i<row; i++) {
        L_reverse[i][i]=1.0/L[i][i];
        U_reverse[i][i]=1.0/U[i][i];
    }
    //6.求L矩阵的逆矩阵
    for (int i = 1; i<row; i++) {
        for (int j = 0; j<row-i; j++) {
            float sum =0.0;
            for (int k = i; k>0; k--) {
                sum += (L[j+k][i-k]*L_reverse[i-k][j]);
            }
            L_reverse[i+j][j]=-sum;
        }
    }
    cout<<"L 矩阵的逆矩阵："<<endl;
    printMatrix(L_reverse, row, row);
    //7.求U矩阵的逆矩阵
    for (int i = 1; i<row; i++) {
        for (int j = 0; j<row-i; j++) {
            float sum = 0.0;
            for (int k = 1; k<= i; k++) {
                sum += (L[j][k+j]*U_reverse[k+j][i+j]);
            }
            U_reverse[j][j+i] = -sum/L[j][j];
        }
    }
    cout<<"U 矩阵的逆矩阵："<<endl;
    printMatrix(U_reverse, row, row);
    
    result = multiplyMatrix(U_reverse, L_reverse, row,row,row);
    
    
    return result;
    
}

