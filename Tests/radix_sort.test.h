//
//  bucket_sort.hpp
//  Algorithm
//
//  Created by dtysky on 16/8/31.
//  Copyright © 2016年 dtysky@outlook.com. All rights reserved.
//

#include <iostream>
#include "radix_sort.h"
#include "utils.h"
#include <ctime>


namespace my_algorithm {
    using std::cout;
    using std::endl;
    using std::vector;
    
    void testRadixSort(){

        auto v1 = vector<uint32_t>(10000);
        fillVectorWithRandomNumbers(v1, 10000);
        auto tmp = refSort<uint32_t>(v1);
        printVector<uint32_t>(tmp);

        auto tStart = clock();
        radixSort(v1, 4, 10);
        printf("Time taken: %.6fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

        printVector<uint32_t>(v1);

        tStart = clock();
        radixSort(v1, 4, 10, true);
        printf("Time taken: %.6fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

        printVector<uint32_t>(v1);

        v1 = vector<uint32_t>(20000);
        fillVectorWithRandomNumbers(v1, 20000);

        tStart = clock();
        radixSort(v1, 5, 10);
        printf("Time taken: %.6fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

        printVector<uint32_t>(v1);
    }
}