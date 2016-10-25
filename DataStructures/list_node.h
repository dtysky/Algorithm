//
//  list_node.hpp
//  Algorithm
//
//  Created by dtysky on 16/8/22.
//  Copyright © 2016年 dtysky@outlook.com. All rights reserved.
//

#ifndef list_node_hpp
#define list_node_hpp

#include <cstdio>
#include <iostream>


namespace data_structures {
    using std::cout;
    using std::ostream;
    
    template <typename T>
    class ListNode{
        
    private:
        ListNode<T>* _next;
        
    public:
        T element;
        ListNode();
        ListNode(const T& element, ListNode<T>* next_node = nullptr);
        ListNode(const ListNode<T>& node);
        virtual ~ListNode();
        void insertAfter(ListNode<T>* node);
        ListNode<T>* deleteAfter();
        ListNode<T>* next();
        ListNode<T>& operator=(const ListNode<T>& node);
        bool operator==(const ListNode<T>& node);
        bool operator!=(const ListNode<T>& node);
        friend ostream& operator<<(ostream& out, const ListNode<T>& node){
            cout << "Current: " << &node << ", Element: " << node.element << ", Next: " << node._next;
            return out;
        }
    };
    
    
    template <typename T> inline
    ListNode<T>::ListNode(){
        _next = nullptr;
        element = T();
    }
    
    template <typename T> inline
    ListNode<T>::ListNode(const T& element, ListNode<T>* next_node){
        this->element = element;
        _next = next_node;
    }
    
    template <typename T> inline
    ListNode<T>::ListNode(const ListNode<T>& node){
        this->element = node.element;
        _next = node._next;
    }
    
    template <typename T> inline
    ListNode<T>::~ListNode(){
        _next = nullptr;
    }
    
    template <typename T> inline
    ListNode<T>& ListNode<T>::operator=(const ListNode<T>& node){
        this->element = node.element;
        _next = node._next;
        return *this;
    }
    
    template <typename T> inline
    bool ListNode<T>::operator==(const ListNode<T>& node){
        return (this->element == node.element) && (_next == node._next);
    }
    
    template <typename T> inline
    bool ListNode<T>::operator!=(const ListNode<T>& node){
        return (this->element != node.element) || (_next != node._next);
    }
    
    template <typename T> inline
    void ListNode<T>::insertAfter(ListNode<T>* node){
        node->_next = _next;
        _next = node;
    }
    
    template <typename T> inline
    ListNode<T>* ListNode<T>::deleteAfter(){
        ListNode<T>* temp_node = _next;
        if (_next != nullptr) {
            _next = _next->_next;
        }
        return temp_node;
    }
    
    template <typename T> inline
    ListNode<T>* ListNode<T>::next() {
        return _next;
    }
    
}

#endif /* list_node_hpp */
