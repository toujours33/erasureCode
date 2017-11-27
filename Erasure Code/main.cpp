//
//  main.cpp
//  Erasure Code
//
//  Created by Jerry Wang on 2017/11/21.
//  Copyright © 2017年 Jerry Wang. All rights reserved.
//
#include <iostream>
#include "functions.h"


int main(){
    
    dataInitial();
    dataPartition();
    dataDeploy();
    
    simulator();

    
    return 0;
}
