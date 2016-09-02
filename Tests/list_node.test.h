//
//  list_node.cpp
//  Algorithm
//
//  Created by dtysky on 16/8/22.
//  Copyright © 2016年 dtysky@outlook.com. All rights reserved.
//

#include "list_node.h"


namespace data_structures {
    void testListNode(){
        ListNode<int> node;
        ListNode<int> next_node = *new ListNode<int>(1000, &node);
        ListNode<int> copy_node = *new ListNode<int>(next_node);
        cout << "node:\n" << node << "\n\n";
        cout << "next_node:\n" << next_node << "\n\n";
        cout << "copy_node:\n" << copy_node << "\n\n";
        
        copy_node = node;
        cout << "copy_node:\n" << copy_node << "\n\n";
        
        node.insertAfter(&next_node);
        node.element = next_node.element;
        cout << "insertAfter, setElement, getElement, getNext:\n" << node << " should equal " << node.next()  << "\n" << "Equal: " << (*node.next() == next_node) << "\n\n";
        
        node.deleteAfter();
        cout << "deleteAfter:\n" << node << "\n";
    }

}
