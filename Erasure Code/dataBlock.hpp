//
//  dataBlock.hpp
//  Erasure Code
//
//  Created by Jerry Wang on 2017/11/22.
//  Copyright © 2017年 Jerry Wang. All rights reserved.
//

#ifndef dataBlock_hpp
#define dataBlock_hpp

#include <iostream>
#include "List.h"
using namespace std;

struct DataBlock{
    int tag;
    List dataSet;
};

void initDataBlock(DataBlock & db,int tag,int dataNum,List &metadata);

#endif /* dataBlock_hpp */
