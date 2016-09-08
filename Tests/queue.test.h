//
//  queue
//  Algorithm
//
//  Created by dtysky on 16/9/8.
//  Copyright © 2016 dtysky@outlook.com. All rights reserved.
//

#include "queue.h"


namespace data_structures {
    using std::endl;

    void testQueue() {
        auto queue = Queue<uint32_t>();
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
        auto queue1 = Queue<uint32_t>(queue);
        cout << queue1 << endl;
        while (!queue.isEmpty()) {
            cout << queue.dequeue() << endl;
            cout << queue << endl;
        }
        cout << queue.isEmpty() << endl;
        queue.clear();
        cout << queue << endl;
    }
}
