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
        bool _isTail(ListNode<T>* node) const;
        ListNode<T>* _findPrevious(const T& element);
        
    public:
        LinkedList();
        LinkedList(LinkedList<T>* list);
        ~LinkedList();
        bool isEmpty() const;
        bool isTail(const T& element) const;
        ListNode<T>* find(const T& element);
        ListNode<T>* findPrevious(const T& element);
        LinkedList<T>* insert(const T& pre_element, const T& new_element);
        LinkedList<T>* insertToHeader(const T& element);
        LinkedList<T>* insertToTail(const T& element);
        LinkedList<T>* del(const T& element);
        ListNode<T>* header() const;
        ListNode<T>* tail() const;
        friend ostream& operator<<(ostream& out, const LinkedList<T>& list){
            ListNode<T>* _current = list._header;
            while (!list._isTail(_current)) {
                _current = _current->next();
                cout << _current->element << ", ";
            }
            return out;
        };
    };
    
    void testLinkedList();
    
}


#endif /* linked_list_hpp */
