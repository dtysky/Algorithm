//
//  selection_sort
//  Algorithm
//
//  Created by dtysky on 16/9/9.
//  Copyright © 2016 dtysky@outlook.com. All rights reserved.
//

#include <iostream>
#include "selection_sort.h"
#include "utils.h"


namespace my_algorithm {
    using std::cout;
    using std::endl;
    using std::vector;

    void testSelectionSort(){
        auto v1 = vector<uint32_t>(20);
        fillVectorWithRandomNumbers(v1, 10000);
        selectionSort(v1);
        printVector<uint32_t>(v1);
        selectionSort(v1, true);
        printVector<uint32_t>(v1);
    }
}