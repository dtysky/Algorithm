//
//  shell_sort
//  Algorithm
//
//  Created by dtysky on 16/9/13.
//  Copyright © 2016 dtysky@outlook.com. All rights reserved.
//

#include <iostream>
#include "shell_sort.h"
#include "utils.h"
#include <ctime>


namespace my_algorithm {
    using std::cout;
    using std::endl;
    using std::vector;

    void testShellSort(){

        vector<uint32_t> step_queue = {4, 3, 2, 1};

        auto v1 = vector<uint32_t>(10000);
        fillVectorWithRandomNumbers(v1, 10000);
        auto tmp = refSort<uint32_t>(v1);
        printVector<uint32_t>(tmp);

        auto tStart = clock();
        shellSort<uint32_t>(v1, step_queue);
        printf("Time taken: %.6fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

        printVector<uint32_t>(v1);

        tStart = clock();
        shellSort<uint32_t>(v1, step_queue, true);
        printf("Time taken: %.6fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

        printVector<uint32_t>(v1);

        v1 = vector<uint32_t>(20000);
        fillVectorWithRandomNumbers(v1, 20000);

        tStart = clock();
        shellSort<uint32_t>(v1, step_queue);
        printf("Time taken: %.6fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

        printVector<uint32_t>(v1);
    }
}
