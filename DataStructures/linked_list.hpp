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
#include <iterator>
#include "list_node.hpp"


namespace data_structures{
    using namespace std;
    template <typename T>
    class LinkedList {

    private:
        ListNode<T>* _header;
        ListNode<T>* _findPrevious(const T& element);
        
    public:
        LinkedList();
        LinkedList(const LinkedList<T>& list);
        ~LinkedList();
        bool isEmpty();
        bool isTail(ListNode<T>* node);
        bool isTail(const T& element);
        ListNode<T>* find(const T& element);
        ListNode<T>* findPrevious(const T& element);
        LinkedList<T>* insert(const T& pre_element, const T& new_element);
        LinkedList<T>* insertToHeader(const T& element);
        LinkedList<T>* insertToTail(const T& element);
        LinkedList<T>* del(const T& element);
        ListNode<T>* header();
        ListNode<T>* tail();
        void operator=(const LinkedList<T>& list);
        bool operator==(const LinkedList<T>& list);
        bool operator!=(const LinkedList<T>& list);
        friend ostream& operator<<(ostream& out, LinkedList<T>& list){
            if (list.isEmpty()) {
                return out;
            }
            ListNode<T>* _current = list.header();
            while (!list.isTail(_current)) {
                cout << _current->element << ", ";
                _current = _current->next();
            }
            cout << _current->element;
            return out;
        };
    };
    

    template <typename T> inline
    LinkedList<T>::LinkedList(){
        _header = new ListNode<T>();
    }
    
    template <typename T> inline
    LinkedList<T>::LinkedList(const LinkedList<T>& list){
        _header = new ListNode<T>();
        ListNode<T>* _current = list._header;
        ListNode<T>* _new_current = _header;
        while (!isTail(_current)) {
            _current = _current->next();
            _new_current->insertAfter(new ListNode<T>(_current->element));
            _new_current = _new_current->next();
        }
    }
    
    template <typename T> inline
    LinkedList<T>::~LinkedList(){
        ListNode<T>* _current = _header;
        ListNode<T>* _next;
        while (!isTail(_current)) {
            _next = _current->next();
            delete _current;
            _current = _next;
        }
        delete _current;
    }
    
    template <typename T> inline
    void LinkedList<T>::operator=(const LinkedList<T>& list){
        _header = new ListNode<T>();
        ListNode<T>* _current = list._header;
        ListNode<T>* _new_current = _header;
        while (!isTail(_current)) {
            _current = _current->next();
            _new_current->insertAfter(new ListNode<T>(_current->element));
            _new_current = _new_current->next();
        }
    }
    
    template <typename T> inline
    bool LinkedList<T>::operator==(const LinkedList<T>& list){
        return _header == list._header;
    }
    
    template <typename T> inline
    bool LinkedList<T>::operator!=(const LinkedList<T>& list){
        return _header != list._header;
    }
    
    template <typename T> inline
    bool LinkedList<T>::isEmpty() {
        return _header->next() == nullptr;
    }
    
    template <typename T> inline
    bool LinkedList<T>::isTail(ListNode<T>* node) {
        return node->next() == nullptr;
    }
    
    template <typename T> inline
    bool LinkedList<T>::isTail(const T& element) {
        return isTail(find(element));
    }
    
    template <typename T> inline
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
    
    template <typename T> inline
    ListNode<T>* LinkedList<T>::_findPrevious(const T& element){
        ListNode<T>* _current = _header;
        while (!isTail(_current)) {
            if (_current->next()->element == element) {
                return _current;
            }
            _current = _current->next();
        }
        return nullptr;
    }
    
    template <typename T> inline
    ListNode<T>* LinkedList<T>::findPrevious(const T& element){
        ListNode<T>* _previous = _findPrevious(element);
        if (_previous == _header) {
            return nullptr;
        }
        return _previous;
    }
    
    template <typename T> inline
    LinkedList<T>* LinkedList<T>::insert(const T& pre_element, const T& new_element){
        ListNode<T>* _current = find(pre_element);
        if (_current == nullptr) {
            throw std::out_of_range("Element is not in this list !");
        }
        _current->insertAfter(new ListNode<T>(new_element));
        return this;
    }
    
    template <typename T> inline
    LinkedList<T>* LinkedList<T>::insertToHeader(const T& element){
        _header->insertAfter(new ListNode<T>(element));
        return this;
    }
    
    template <typename T> inline
    LinkedList<T>* LinkedList<T>::insertToTail(const T& element){
        if (isEmpty()) {
            insertToHeader(element);
        }
        else {
            tail()->insertAfter(new ListNode<T>(element));
        }
        return this;
    }
    
    template <typename T> inline
    LinkedList<T>* LinkedList<T>::del(const T& element){
        if (isEmpty()) {
            return this;
        }
        ListNode<T>* _previous = _findPrevious(element);
        if (_previous == nullptr) {
            throw std::out_of_range("Element is not in this list !");
        }
        ListNode<T>* _current = _previous->next();
        _previous->deleteAfter();
        delete _current;
        return this;
    }
    
    template <typename T> inline
    ListNode<T>* LinkedList<T>::header() {
        return _header->next();
    }
    
    template <typename T> inline
    ListNode<T>* LinkedList<T>::tail() {
        if (isEmpty()) {
            return nullptr;
        }
        ListNode<T>* _current = _header;
        while (!isTail(_current)) {
            _current = _current->next();
        }
        return _current;
    }
}


#endif /* linked_list_hpp */
