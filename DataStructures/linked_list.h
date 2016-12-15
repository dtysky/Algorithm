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
        size_t _size;
        ListNode<T>* _findPrevious(const T& element);
        
    public:
        LinkedList();
        LinkedList(const LinkedList<T>& list);
        virtual ~LinkedList();
        size_t size() const ;
        bool isEmpty() const;
        bool isTail(ListNode<T>* node) const;
        bool isTail(const T& element) const;
        ListNode<T>* getKthNode(const size_t k);
        ListNode<T>* find(const T& element);
        ListNode<T>* findPrevious(const T& element);
        LinkedList<T>* insert(const T& pre_element, const T& new_element);
        LinkedList<T>* insertAfterNode(ListNode<T>* _current, const T& new_element);
        LinkedList<T>* insertToHeader(const T& element);
        LinkedList<T>* insertToTail(const T& element);
        LinkedList<T>* del(const T& element);
        LinkedList<T>* deleteAfterNode(ListNode<T>* _previous);
        LinkedList<T>* deleteFromHeader();
        LinkedList<T>* clear();
        ListNode<T>* header() const;
        ListNode<T>* tail() const;
        ListNode<T>* begin() const;
        ListNode<T>* end() const;
        LinkedList<T>& operator=(const LinkedList<T>& list);
        bool operator==(const LinkedList<T>& list) const;
        bool operator!=(const LinkedList<T>& list) const;
        friend ostream& operator<<(ostream& out, const LinkedList<T>& list){
            if (list.isEmpty()) {
                return out;
            }
            ListNode<T>* _current = list.begin();
            while (!list.isTail(_current)) {
                out << _current->element << " ";
                _current = _current->next();
            }
            out << _current->element;
            return out;
        };
    };
    

    template <typename T> inline
    LinkedList<T>::LinkedList(){
        _header = new ListNode<T>();
        _tail = _header;
        _size = 0;
    }
    
    template <typename T> inline
    LinkedList<T>::LinkedList(const LinkedList<T>& list){
        _header = new ListNode<T>();
        _tail = _header;
        _size = 0;
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
        _size = 0;
    }
    
    template <typename T> inline
    LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& list) {
        _header = new ListNode<T>();
        _tail = _header;
        _size = 0;
        ListNode<T>* _current = list._header;
        while (!list.isTail(_current)) {
            _current = _current->next();
            insertToTail(_current->element);
        }
        return *this;
    }

    template <typename T> inline
    bool LinkedList<T>::operator==(const LinkedList<T>& list) const {
        if (_size != list._size) {
            return false;
        }
        ListNode<T>* current1 = _header->next();
        ListNode<T>* current2 = list._header->next();
        while (current1 != nullptr) {
            if (current1->element != current2->element) {
                return false;
            }
            current1 = current1->next();
            current2 = current2->next();
        }
        return true;
    }

    template <typename T> inline
    bool LinkedList<T>::operator!=(const LinkedList<T>& list) const {
        return !(*this == list);
    }

    template <typename T> inline
    size_t LinkedList<T>::size() const {
        return _size;
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
    ListNode<T>* LinkedList<T>::getKthNode(const size_t k){
        size_t i = 0;
        ListNode<T>* _current = _header->next();
        while (i < k && _current != nullptr) {
            _current = _current->next();
            i++;
        }
        return _current;
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
        return insertAfterNode(_current, new_element);
    }

    template <typename T> inline
    LinkedList<T>* LinkedList<T>::insertAfterNode(ListNode<T>* _current, const T &new_element){
        _current->insertAfter(new ListNode<T>(new_element));
        _size++;
        if (_current == _tail) {
            _tail = _current->next();
        }
        return this;
    }
    
    template <typename T> inline
    LinkedList<T>* LinkedList<T>::insertToHeader(const T& element){
        return insertAfterNode(_header, element);
    }
    
    template <typename T> inline
    LinkedList<T>* LinkedList<T>::insertToTail(const T& element){
        return insertAfterNode(_tail, element);
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
        return deleteAfterNode(_previous);
    }

    template <typename T> inline
    LinkedList<T>* LinkedList<T>::deleteAfterNode(ListNode<T>* _previous){
        ListNode<T>* _current = _previous->next();
        _previous->deleteAfter();
        delete _current;
        if (_current == _tail) {
            _tail = _previous;
        }
        _size--;
        return this;
    }

    template <typename T> inline
    LinkedList<T>* LinkedList<T>::deleteFromHeader(){
        if (isEmpty()) {
            return this;
        }
        return deleteAfterNode(_header);
    }

    template <typename T> inline
    LinkedList<T>* LinkedList<T>::clear(){
        while (!isEmpty()) {
            deleteFromHeader();
        }
        _tail = _header;
        _size = 0;
        return this;
    }
    
    template <typename T> inline
    ListNode<T>* LinkedList<T>::header() const {
        return _header;
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
