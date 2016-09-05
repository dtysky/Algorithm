//
//  stack_based_on_array
//  Algorithm
//
//  Created by dtysky on 16/9/4.
//  Copyright © 2016 dtysky@outlook.com. All rights reserved.
//


#include "stack.h"


namespace data_structures {
    using std::endl;

    void testStack() {
        auto stack = Stack<uint32_t >();
        stack.push(0)
            .push(1)
            .push(2)
            .push(3)
            .push(4)
            .push(5)
            .push(6)
            .push(7)
            .push(8)
            .push(9)
            .push(10);
        cout << stack << endl;
        cout << stack.top() << endl;
        auto stack1 = Stack<uint32_t>(stack);
        cout << stack1 << endl;
        while (!stack.isEmpty()) {
            cout << stack.pop() << endl;
        }
        cout << stack.isEmpty() << endl;
        stack.clear();
        cout << stack << endl;
    }
}
