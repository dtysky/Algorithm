//
//  linked_list.hpp
//  Algorithm
//
//  Created by dtysky on 16/8/24.
//  Copyright © 2016年 dtysky@outlook.com. All rights reserved.
//

#ifndef linked_list_hpp
#define linked_list_hpp

#include <cstdio>
#include "list_node.h"


namespace data_structures{
    using std::cout;
    using std::ostream;
    
    template <typename T>
    class LinkedList {

    protected:
        ListNode<T>* _header;
        ListNode<T>* _tail;
        ListNode<T>* _findPrevious(const T& element);
        
    public:
        LinkedList();
        LinkedList(const LinkedList<T>& list);
        virtual ~LinkedList();
        bool isEmpty() const;
        bool isTail(ListNode<T>* node) const;
        bool isTail(const T& element) const;
        ListNode<T>* find(const T& element);
        ListNode<T>* findPrevious(const T& element);
        LinkedList<T>* insert(const T& pre_element, const T& new_element);
        LinkedList<T>* insertToHeader(const T& element);
        LinkedList<T>* insertToTail(const T& element);
        LinkedList<T>* del(const T& element);
        LinkedList<T>* deleteFromHeader();
        LinkedList<T>* clear();
        ListNode<T>* header() const;
        ListNode<T>* tail() const;
        ListNode<T>* begin() const;
        ListNode<T>* end() const;
        void operator=(const LinkedList<T>& list);
        bool operator==(const LinkedList<T>& list);
        bool operator!=(const LinkedList<T>& list);
        friend ostream& operator<<(ostream& out, const LinkedList<T>& list){
            if (list.isEmpty()) {
                return out;
            }
            ListNode<T>* _current = list.header();
            while (!list.isTail(_current)) {
                cout << _current->element << " ";
                _current = _current->next();
            }
            cout << _current->element;
            return out;
        };
    };
    

    template <typename T> inline
    LinkedList<T>::LinkedList(){
        _header = new ListNode<T>();
        _tail = _header;
    }
    
    template <typename T> inline
    LinkedList<T>::LinkedList(const LinkedList<T>& list){
        _header = new ListNode<T>();
        _tail = _header;
        ListNode<T>* _current = list._header;
        while (!list.isTail(_current)) {
            _current = _current->next();
            insertToTail(_current->element);
        }
    }
    
    template <typename T> inline
    LinkedList<T>::~LinkedList(){
        while (!isEmpty()) {
            deleteFromHeader();
        }
        delete _header;
        _header = 0;
        _tail = 0;
    }
    
    template <typename T> inline
    void LinkedList<T>::operator=(const LinkedList<T>& list) {
        _header = new ListNode<T>();
        _tail = _header;
        ListNode<T>* _current = list._header;
        while (!list.isTail(_current)) {
            _current = _current->next();
            insertToTail(_current->element);
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
    bool LinkedList<T>::isEmpty() const {
        return _header == _tail;
    }
    
    template <typename T> inline
    bool LinkedList<T>::isTail(ListNode<T>* node) const {
        return node == _tail;
    }
    
    template <typename T> inline
    bool LinkedList<T>::isTail(const T& element) const {
        return element == _tail->element;
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
        if (_current == _tail) {
            _tail = _current->next();
        }
        return this;
    }
    
    template <typename T> inline
    LinkedList<T>* LinkedList<T>::insertToHeader(const T& element){
        _header->insertAfter(new ListNode<T>(element));
        if (isEmpty()) {
            _tail = _header->next();
        }
        return this;
    }
    
    template <typename T> inline
    LinkedList<T>* LinkedList<T>::insertToTail(const T& element){
        if (isEmpty()) {
            insertToHeader(element);
        }
        else {
            _tail->insertAfter(new ListNode<T>(element));
            _tail = _tail->next();
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
        if (_current == _tail) {
            _tail = _previous;
        }
        return this;
    }

    template <typename T> inline
    LinkedList<T>* LinkedList<T>::deleteFromHeader(){
        if (isEmpty()) {
            return this;
        }
        ListNode<T>* _current = _header->next();
        _header->deleteAfter();
        delete _current;
        if (_current == _tail) {
            _tail = _header;
        }
        return this;
    }

    template <typename T> inline
    LinkedList<T>* LinkedList<T>::clear(){
        while (!isEmpty()) {
            deleteFromHeader();
        }
        _tail = _header;
        return this;
    }
    
    template <typename T> inline
    ListNode<T>* LinkedList<T>::header() const {
        return _header->next();
    }
    
    template <typename T> inline
    ListNode<T>* LinkedList<T>::tail() const {
        if (isEmpty()) {
            return nullptr;
        }
        return _tail;
    }

    template <typename T> inline
    ListNode<T>* LinkedList<T>::begin() const {
        return _header->next();
    }
    
    template <typename T> inline
    ListNode<T>* LinkedList<T>::end() const {
        return nullptr;
    }
}


#endif /* linked_list_hpp */
