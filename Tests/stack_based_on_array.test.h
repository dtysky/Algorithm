//
//  stack_based_on_array
//  Algorithm
//
//  Created by dtysky on 16/9/4.
//  Copyright © 2016 dtysky@outlook.com. All rights reserved.
//


#include "stack_based_on_array.h"


namespace data_structures {
    using std::endl;

    void testStackBasedOnArray() {
        auto stack = StackBasedOnArray<uint32_t, 100 >();
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
        auto stack1 = StackBasedOnArray<uint32_t, 100>(stack);
        cout << stack1 << endl;
        while (!stack.isEmpty()) {
            cout << stack.pop() << endl;
            cout << stack << endl;
        }
        cout << stack.isEmpty() << endl;
        stack.clear();
        cout << stack << endl;
    }
}
