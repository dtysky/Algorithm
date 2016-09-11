//
//  insertion_sort
//  Algorithm
//
//  Created by dtysky on 16/9/11.
//  Copyright © 2016 dtysky@outlook.com. All rights reserved.
//

#include <iostream>
#include "insertion_sort.h"
#include "utils.h"


namespace my_algorithm {
    using std::cout;
    using std::endl;
    using std::vector;

    void testInsertionSort(){
        auto v1 = vector<uint32_t>(20);
        fillVectorWithRandomNumbers(v1, 10000);
        insertionSort(v1);
        printVector<uint32_t>(v1);
        insertionSort(v1, true);
        printVector<uint32_t>(v1);
    }
}
