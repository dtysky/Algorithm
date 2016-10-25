//
//  binary_heap
//  Algorithm
//
//  Created by dtysky on 16/9/8.
//  Copyright © 2016 dtysky@outlook.com. All rights reserved.
//

#include "binary_heap.h"


namespace data_structures {
    using std::cout;
    using std::endl;

    void testBinaryHeap() {
        MaxBinaryHeap<uint32_t> max_heap;
        max_heap.insert(0)
            .insert(1)
            .insert(2)
            .insert(3)
            .insert(4)
            .insert(5)
            .insert(6)
            .insert(7)
            .insert(8)
            .insert(9)
            .insert(10);
        cout << max_heap << endl;
//        cout << max_heap.top() << endl;
//        auto max_heap1 = max_heap;
//        cout << max_heap1 << endl;
//        while (!max_heap.isEmpty()) {
//            cout << max_heap.deleteTop() << endl;
//            cout << max_heap << endl;
//        }
//        cout << max_heap.isEmpty() << endl;
//        max_heap1.clear();
//        cout << max_heap1 << endl;
//        MinBinaryHeap<uint32_t> min_heap;
//        min_heap.insert(0)
//            .insert(1)
//            .insert(2)
//            .insert(3)
//            .insert(4)
//            .insert(5)
//            .insert(6)
//            .insert(7)
//            .insert(8)
//            .insert(9)
//            .insert(10);
//        cout << min_heap << endl;
    }
}
