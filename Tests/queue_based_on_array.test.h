//
//  queue_based_on_array
//  Algorithm
//
//  Created by dtysky on 16/9/8.
//  Copyright © 2016 dtysky@outlook.com. All rights reserved.
//

#include "queue_based_on_array.h"


namespace data_structures {
    using std::endl;

    void testQueueBasedOnArray() {
        auto queue = QueueBasedOnArray<uint32_t, 11>();
        queue.enqueue(0)
            .enqueue(1)
            .enqueue(2)
            .enqueue(3)
            .enqueue(4)
            .enqueue(5)
            .enqueue(6)
            .enqueue(7)
            .enqueue(8)
            .enqueue(9)
            .enqueue(10);
        cout << queue << endl;
        cout << queue.front() << endl;
        cout << queue.rear() << endl;
        cout << queue.isFull() << endl;
        auto queue1 = QueueBasedOnArray<uint32_t, 11>(queue);
        cout << queue1 << endl;
        while (!queue.isEmpty()) {
            cout << queue.dequeue() << endl;
            cout << queue << endl;
        }
        cout << queue.isEmpty() << endl;
        queue.enqueue(20)
            .enqueue(21)
            .enqueue(22)
            .enqueue(23)
            .enqueue(24)
            .enqueue(25)
            .enqueue(26)
            .enqueue(27)
            .enqueue(28)
            .enqueue(29)
            .enqueue(30);
        cout << queue << endl;
        queue.clear();
        cout << queue << endl;
    }
}