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
        if (isEmpty()) {
            return nullptr;
        }
        ListNode<T>* _current = _header->next();
        while (_current != nullptr) {
            if (_current->element == element) {
                break;
            }
            _current = _current->next();
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
        if (isEmpty()) {
            return nullptr;
        }
        ListNode<T>* _current = _header->next();
        while (!isTail(_current)) {
            if (_current->next()->element == element) {
                return _current;
            }
            _current = _current->next();
        }
        return nullptr;
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
        LinkedList<int>* list = new LinkedList<int>();
        list->insertToTail(new ListNode<int>(1))
            ->insertToTail(new ListNode<int>(2))
            ->insertToTail(new ListNode<int>(3))
            ->insertToTail(new ListNode<int>(4))
            ->insertToTail(new ListNode<int>(5))
            ->insertToTail(new ListNode<int>(6))
            ->insertToTail(new ListNode<int>(7))
            ->insertToTail(new ListNode<int>(8))
            ->insertToTail(new ListNode<int>(9))
            ->insertToTail(new ListNode<int>(10));
        cout << *list << "\n";
        cout << list->find(4) << "\n";
        cout << list->findPrevious(9) << "\n";
        cout << list->find(0) << "\n";
        cout << list->findPrevious(1) << "\n";
        delete list;
    }

}