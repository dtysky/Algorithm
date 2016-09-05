//
//  linked_list
//  Algorithm
//
//  Created by dtysky on 16/8/24.
//  Copyright © 2016年 dtysky@outlook.com. All rights reserved.
//

#include "linked_list.h"


namespace data_structures {
    void testLinkedList(){
        LinkedList<uint32_t>* list = new LinkedList<uint32_t>();
        cout << list->isEmpty() << "\n";
        cout << list->header() << "\n";
        cout << list->tail() << "\n";
        list->insertToTail(1)
            ->insertToTail(2)
            ->insertToTail(3)
            ->insertToTail(4)
            ->insertToTail(5)
            ->insertToTail(6)
            ->insertToTail(7)
            ->insertToTail(8)
            ->insertToTail(9)
            ->insertToTail(10);
        cout << *list << "\n";
        cout << list->isEmpty() << "\n";
        cout << list->header() << "\n";
        cout << list->tail() << "\n";
        cout << list->find(4) << "\n";
        cout << list->findPrevious(9) << "\n";
        cout << list->find(0) << "\n";
        cout << list->findPrevious(1) << "\n";
        cout << list->isTail(10) << "\n";
        LinkedList<uint32_t>* copy_list = new LinkedList<uint32_t>(*list);
        cout << *copy_list << "\n";
        LinkedList<uint32_t> copy_list2 = *list;
        cout << copy_list2 << "\n";
        cout << (*copy_list == copy_list2) << "\n";
        list->del(1)
            ->del(5)
            ->del(10);
        cout << *list << "\n";
        list->insertToHeader(1);
        list->insert(4, 5)
            ->insert(9, 10);
        cout << *list << "\n";
        list->clear();
        cout << *list << "\n";
        list->del(1);
        delete list;
        delete copy_list;
    }

}