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
        _header = new ListNode<T>();
        ListNode<T>* _current = list->_header;
        ListNode<T>* _new_current = _header;
        while (!_isTail(_current)) {
            _current = _current->next();
            _new_current->insertAfter(new ListNode<T>(_current->element));
            _new_current = _new_current->next();
        }
    }
    
    template <class T>
    LinkedList<T>::~LinkedList(){
        ListNode<T>* _current = _header;
        while (!_isTail(_current)) {
            _current = _current->next();
            delete _current;
        }
        delete _header;
    }
    
    template <class T>
    bool LinkedList<T>::isEmpty() {
        return _header->next() == nullptr;
    }
    
    template <class T>
    bool LinkedList<T>::_isTail(ListNode<T>* node) {
        return node->next() == nullptr;
    }
    
    template <class T>
    bool LinkedList<T>::isTail(const T& element) {
        return _isTail(find(element));
    }
    
    template <class T>
    ListNode<T>* LinkedList<T>::find(const T& element){
        ListNode<T>* _current = _header->next();
        while (_current != nullptr) {
            if (_current->element == element) {
                break;
            }
            _current = _current->next();
        }
        return _current;
    }
    
    template <class T>
    ListNode<T>* LinkedList<T>::_findPrevious(const T& element){
        ListNode<T>* _current = _header;
        while (!_isTail(_current)) {
            if (_current->next()->element == element) {
                return _current;
            }
            _current = _current->next();
        }
        return nullptr;
    }
    
    template <class T>
    ListNode<T>* LinkedList<T>::findPrevious(const T& element){
        ListNode<T>* _previous = _findPrevious(element);
        if (_previous == _header) {
            return nullptr;
        }
        return _previous;
    }
    
    template <class T>
    LinkedList<T>* LinkedList<T>::insert(const T& pre_element, const T& new_element){
        ListNode<T>* _current = find(pre_element);
        _current->insertAfter(new ListNode<T>(new_element));
        return this;
    }
    
    template <class T>
    LinkedList<T>* LinkedList<T>::insertToHeader(const T& element){
        _header->insertAfter(new ListNode<T>(element));
        return this;
    }
    
    template <class T>
    LinkedList<T>* LinkedList<T>::insertToTail(const T& element){
        tail()->insertAfter(new ListNode<T>(element));
        return this;
    }
    
    template <class T>
    LinkedList<T>* LinkedList<T>::del(const T& element){
        if (isEmpty()) {
            return this;
        }
        ListNode<T>* _previous = _findPrevious(element);
        ListNode<T>* _current = _previous->next();
        _previous->deleteAfter();
        delete _current;
        return this;
    }
    
    template <class T>
    ListNode<T>* LinkedList<T>::header() {
        return _header->next();
    }
    
    template <class T>
    ListNode<T>* LinkedList<T>::tail() {
        ListNode<T>* _current = _header;
        while (!_isTail(_current)) {
            _current = _current->next();
        }
        return _current;
    }
    
    
    void testLinkedList(){
        LinkedList<int>* list = new LinkedList<int>();
        cout << list->isEmpty() << "\n";
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
        cout << list->find(4) << "\n";
        cout << list->findPrevious(9) << "\n";
        cout << list->find(0) << "\n";
        cout << list->findPrevious(1) << "\n";
        cout << list->isTail(10) << "\n";
        LinkedList<int>* copy_list = new LinkedList<int>(list);
        cout << *copy_list << "\n";
        list->del(1)
            ->del(5)
            ->del(10);
        cout << *list << "\n";
        list->insertToHeader(1);
        list->insert(1, 5)
            ->insert(9, 10);
        cout << *list << "\n";
        delete list;
        delete copy_list;
    }

}