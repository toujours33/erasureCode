//
//  dataBlock.cpp
//  Erasure Code
//
//  Created by Jerry Wang on 2017/11/22.
//  Copyright © 2017年 Jerry Wang. All rights reserved.
//

#include "dataBlock.hpp"

void initDataBlock(DataBlock & db,int tag,int dataNum,List &metadata){
    
    db.tag = tag;
    initList(db.dataSet);
    for (int i =6*(tag); i<6*(tag+1); i++) {
        addElem(db.dataSet, metadata.elem[i]);
    }
    
}
