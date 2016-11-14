//
//  binary_search
//  Algorithm
//
//  Created by dtysky on 16/9/13.
//  Copyright © 2016 dtysky@outlook.com. All rights reserved.
//

#include <iostream>
#include "binary_search.h"
#include "utils.h"
#include <ctime>


namespace my_algorithm {
    using std::cout;
    using std::endl;
    using std::vector;

    void testBinarySearch(){
        auto v1 = vector<uint32_t>(10000);
        fillVectorWithRangeNumbers(v1, 10000);
        auto tmp = refSort<uint32_t>(v1);

        auto tStart = clock();
        cout << binarySearch<uint32_t>(v1, 9328) << endl;
        printf("Time taken: %.6fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

        v1 = vector<uint32_t>(20000);
        fillVectorWithRangeNumbers(v1, 20000);

        tStart = clock();
        cout << binarySearch<uint32_t>(v1, 19328) << endl;
        printf("Time taken: %.6fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    }
}
