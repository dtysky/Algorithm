//
//  linked_list.hpp
//  Algorithm
//
//  Created by DaiTianyu on 16/8/24.
//  Copyright © 2016年 dtysky@outlook.com. All rights reserved.
//

#ifndef linked_list_hpp
#define linked_list_hpp

#include <stdio.h>
#include "list_node.hpp"
using namespace std;


namespace data_structures{
    template <class T>
    class LinkedList {

    private:
        ListNode<T>* _header;
        bool _isTail(ListNode<T>* node);
        ListNode<T>* _findPrevious(const T& element);
        
    public:
        LinkedList();
        LinkedList(LinkedList<T>* list);
        ~LinkedList();
        bool isEmpty();
        bool isTail(const T& element);
        ListNode<T>* find(const T& element);
        ListNode<T>* findPrevious(const T& element);
        LinkedList<T>* insert(const T& pre_element, const T& new_element);
        LinkedList<T>* insertToHeader(const T& element);
        LinkedList<T>* insertToTail(const T& element);
        LinkedList<T>* del(const T& element);
        ListNode<T>* header();
        ListNode<T>* tail();
        friend ostream& operator<<(ostream& out, LinkedList<T>& list){
            if (list.isEmpty()) {
                return out;
            }
            ListNode<T>* _current = list.header();
            while (!list._isTail(_current)) {
                cout << _current->element << ", ";
                _current = _current->next();
            }
            cout << _current->element;
            return out;
        };
    };
    
    void testLinkedList();
    
}


#endif /* linked_list_hpp */
