//
//  linked_list.cpp
//  Algorithm
//
//  Created by DaiTianyu on 16/8/24.
//  Copyright © 2016年 dtysky@outlook.com. All rights reserved.
//

#include "linked_list.hpp"

namespace data_structures {
    
    template <class T>
    LinkedList<T>::LinkedList(){
        _header = new ListNode<T>();
    }
    
    template <class T>
    LinkedList<T>::LinkedList(LinkedList<T> *list){
        ListNode<T>* _current = list->header();
        while (!isTail(_current)) {
            _current->insertAfter(new ListNode<T>(_current->next()->element));
            _current = _current->next();
        }
    }
    
    template <class T>
    LinkedList<T>::~LinkedList(){
        ListNode<T>* _current = header();
        while (!isTail(_current)) {
            delete _current;
            _current = _current->next();
        }
    }
    
    template <class T>
    bool LinkedList<T>::isEmpty() const {
        return _header->next() == nullptr;
    }
    
    template <class T>
    bool LinkedList<T>::isTail(ListNode<T>* node) const {
        return node->next() == nullptr;
    };
    
    template <class T>
    ListNode<T>* LinkedList<T>::find(const T& element){
        ListNode<T>* _current = _header;
        while (!isTail(_current) && _current->element != element) {
            _current = _current->next;
        }
        return _current;
    };
    
    template <class T>
    void LinkedList<T>::del(const T& element){
        ListNode<T>* _previous = findPrevious(element);
        ListNode<T>* _current = _previous->next();
        _previous->insertAfter(_current->next);
        delete _current;
    };
    
    template <class T>
    ListNode<T>* LinkedList<T>::findPrevious(const T& element){
        ListNode<T>* _current = _header;
        while (!isTail(_current) && _current->next->element != element) {
            _current = _current->next;
        }
        return _current;
    };
    
    template <class T>
    void LinkedList<T>::insert(T& element, ListNode<T>* node){
        ListNode<T>* _current = find(element);
        _current->insertAfer(node);
    };
    
    template <class T>
    LinkedList<T>* LinkedList<T>::insertToTail(ListNode<T>* node){
        tail()->insertAfter(node);
        return this;
    };
    
    template <class T>
    ListNode<T>* LinkedList<T>::header() const {
        return _header;
    };
    
    template <class T>
    ListNode<T>* LinkedList<T>::tail(){
        ListNode<T>* _current = _header;
        while (!isTail(_current)) {
            _current = _current->next();
        }
        return _current;
    };
    
    
    void testLinkedList(){
        LinkedList<int>* list;
        list->insertToTail(new ListNode<int>(1))
            ->insertToTail(new ListNode<int>(2));
        cout << *list << "\n";
    }

}