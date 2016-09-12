//
//  main.cpp
//  Algorithm
//
//  Created by dtysky on 16/8/22.
//  Copyright © 2016年 dtysky@outlook.com. All rights reserved.
//

#include "main.h"

#include "selection_sort.test.h"
#include "insertion_sort.test.h"


int main(int argc, const char * argv[]) {
    my_algorithm::testInsertionSort();
    my_algorithm::testSelectionSort();
    return 0;
}