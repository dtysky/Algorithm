//
//  priority_queue
//  Algorithm
//
//  Created by dtysky on 16/9/20.
//  Copyright © 2016 dtysky@outlook.com. All rights reserved.
//

#include "priority_queue.h"


namespace data_structures {
    using std::endl;

    void testPriorityQueue(){
        auto queue = PriorityQueue<uint32_t>();
        queue.enqueue(0)
            .enqueue(10)
            .enqueue(4)
            .enqueue(3)
            .enqueue(2)
            .enqueue(8)
            .enqueue(6)
            .enqueue(7)
            .enqueue(5)
            .enqueue(9)
            .enqueue(1);
        cout << queue << endl;
        cout << queue.maxN() << endl;
        cout << queue.minN() << endl;
        auto queue1 = PriorityQueue<uint32_t>(queue);
        cout << queue1 << endl;
        while (!queue.isEmpty()) {
            cout << queue.dequeueMaxN() << endl;
            cout << queue << endl;
        }
        while (!queue1.isEmpty()) {
            cout << queue1.dequeueMinN() << endl;
            cout << queue1 << endl;
        }
        cout << queue.isEmpty() << endl;
        queue1.clear();
        cout << queue1 << endl;
    }
}