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
//        data = NULL;
//        next = nullptr;
    }
    
    template <class T>
    ListNode<T>::ListNode(const T& data, ListNode<T>* next_node){
        this->data = data;
        next = next_node;
    }
    
    template <class T>
    void ListNode<T>::insertAfter(ListNode<T>* node){
        node->next = next;
        next = node;
    }
    
    template <class T>
    ListNode<T>* ListNode<T>::deleteAfter(){
        ListNode<T>* temp_node = next;
        if (next != nullptr) {
            next = next->next;
        }
        return temp_node;
    }
    
    template <class T>
    void ListNode<T>::setData(T data){
        this->data = data;
    }
    
    template <class T>
    T ListNode<T>::getData(){
        return data;
    }
    
    template <class T>
    ListNode<T>* ListNode<T>::nextNode(){
        return next;
    }
    
    
    
    void test(){
        ListNode<int> node;
        ListNode<int> next_node = *new ListNode<int>(1000);
        cout << "node:\n" << node << "\n\n";
        cout << "next_node:\n" << next_node << "\n\n";
        
        node.insertAfter(&next_node);
        node.setData(next_node.getData());
        cout << "insertAfter, setData, getData:\n" << node << "\n\n";
        
        node.deleteAfter();
        cout << "deleteAfter:\n" << node << "\n";
    }
}
