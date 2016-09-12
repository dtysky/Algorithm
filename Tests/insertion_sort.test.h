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
#include <ctime>


namespace my_algorithm {
    using std::cout;
    using std::endl;
    using std::vector;

    void testInsertionSort(){

        auto v1 = vector<uint32_t>(10000);
        fillVectorWithRandomNumbers(v1, 10000);

        auto tStart = clock();
        insertionSort(v1);
        printf("Time taken: %.6fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

        printVector<uint32_t>(v1);

        tStart = clock();
        insertionSort(v1, true);
        printf("Time taken: %.6fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

        printVector<uint32_t>(v1);
    }
}
