//
//  list_node.cpp
//  Algorithm
//
//  Created by DaiTianyu on 16/8/22.
//  Copyright © 2016年 dtysky@outlook.com. All rights reserved.
//

#include "list_node.hpp"

namespace data_structures {
    template <class T>
    ListNode<T>::ListNode(){
        element = NULL;
        _next = nullptr;
    }
    
    template <class T>
    ListNode<T>::ListNode(const T& element, ListNode<T>* next_node){
        this->element = element;
        _next = next_node;
    }
    
    template <class T>
    ListNode<T>::ListNode(ListNode<T>* node){
        this->element = node->element;
        _next = node->_next;
    }
    
    template <class T>
    void ListNode<T>::insertAfter(ListNode<T>* node){
        node->_next = _next;
        _next = node;
    }
    
    template <class T>
    ListNode<T>* ListNode<T>::deleteAfter(){
        ListNode<T>* temp_node = _next;
        if (_next != nullptr) {
            _next = _next->_next;
        }
        return temp_node;
    }
    
    template <class T>
    ListNode<T>* ListNode<T>::next() const {
        return _next;
    }
    
    void testListNode(){
        ListNode<int> node;
        ListNode<int> next_node = *new ListNode<int>(1000, &node);
        ListNode<int> copy_node = *new ListNode<int>(&next_node);
        cout << "node:\n" << node << "\n\n";
        cout << "next_node:\n" << next_node << "\n\n";
        cout << "copy_node:\n" << copy_node << "\n\n";
        
        node.insertAfter(&next_node);
        node.element = next_node.element;
        cout << "insertAfter, setElement, getElement, getNext:\n" << node << " should equal " << node.next()  << "\n\n";
        
        node.deleteAfter();
        cout << "deleteAfter:\n" << node << "\n";
    }

}
