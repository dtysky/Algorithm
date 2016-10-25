//
//  priority_queue
//  Algorithm
//
//  Created by dtysky on 16/9/19.
//  Copyright © 2016 dtysky@outlook.com. All rights reserved.
//

#ifndef ALGORITHM_PRIORITY_QUEUE_H
#define ALGORITHM_PRIORITY_QUEUE_H

#include <cstdio>
#include <iostream>
#include "linked_list.h"


namespace data_structures {
    template <typename T>
    class PriorityQueue {
    protected:
        LinkedList<T> _list;
        bool _less(const T& element1, const T& element2);
        void _checkN(const size_t n);

    public:
        PriorityQueue();
        PriorityQueue(const PriorityQueue<T>& queue);
        virtual ~PriorityQueue();
        bool isEmpty();
        PriorityQueue<T>& clear();
        PriorityQueue<T>& enqueue(const T &element);
        T dequeueMaxN(const size_t n = 1);
        T dequeueMinN(const size_t n = 1);
        T maxN(const size_t n = 1);
        T minN(const size_t n = 1);
        PriorityQueue<T>& operator=(const PriorityQueue<T>& queue);
        bool operator==(const PriorityQueue<T>& queue);
        bool operator!=(const PriorityQueue<T>& queue);
        friend std::ostream& operator<<(std::ostream& out, const PriorityQueue<T>& queue){
            std::cout << "Min ---- ";
            std::cout << queue._list;
            std::cout << " ---- Max";
            return out;
        };
    };

    template <typename T> inline
    PriorityQueue<T>::PriorityQueue() {
        _list = LinkedList<T>();
    }

    template <typename T> inline
    PriorityQueue<T>::PriorityQueue(const PriorityQueue<T>& queue) {
        _list =  LinkedList<T>(queue._list);
    }

    template <typename T> inline
    PriorityQueue<T>::~PriorityQueue() {}

    template <typename T> inline
    PriorityQueue<T>& PriorityQueue<T>::operator=(const PriorityQueue<T>& queue){
        _list = queue._list;
        return *this;
    }

    template <typename T> inline
    bool PriorityQueue<T>::operator==(const PriorityQueue<T>& queue){
        return _list == queue._list;
    }

    template <typename T> inline
    bool PriorityQueue<T>::operator!=(const PriorityQueue<T>& queue){
        return _list != queue._list;
    }

    template <typename T> inline
    bool PriorityQueue<T>::isEmpty() {
        return _list.isEmpty();
    }

    template <typename T> inline
    PriorityQueue<T>& PriorityQueue<T>::clear(){
        _list.clear();
        return *this;
    }

    template <typename T> inline
    bool PriorityQueue<T>::_less(const T &element1, const T &element2) {
        return element1 < element2;
    }

    template <typename T> inline
    PriorityQueue<T>& PriorityQueue<T>::enqueue(const T &element) {
        if (isEmpty()) {
            _list.insertToHeader(element);
            return *this;
        }
        for (auto node = _list.begin(); node->next() != _list.end() ; node = node->next()) {
            if (!_less(node->next()->element, element)) {
                _list.insertAfterNode(node, element);
                return *this;
            }
        }
        _list.insertToTail(element);
        return *this;
    }

    template <typename T> inline
    void PriorityQueue<T>::_checkN(const size_t n) {
        auto size = _list.size();
        if (n == 0 || n > size) {
            throw std::out_of_range("N must be larger than 0 and less than this queue's size !");
        }
    }

    template <typename T> inline
    T PriorityQueue<T>::maxN(const size_t n) {
        _checkN(n);
        return _list.getKthNode(_list.size() - n)->element;
    }

    template <typename T> inline
    T PriorityQueue<T>::minN(const size_t n) {
        _checkN(n);
        return _list.getKthNode(n - 1)->element;
    }

    template <typename T> inline
    T PriorityQueue<T>::dequeueMaxN(const size_t n) {
        _checkN(n);
        auto size = _list.size();
        T result;
        if (n == size) {
            result = _list.header()->element;
            _list.deleteFromHeader();
        }
        else {
            auto node = _list.getKthNode(_list.size() - n - 1);
            result = node->next()->element;
            _list.deleteAfterNode(node);
        }
        return result;
    }

    template <typename T> inline
    T PriorityQueue<T>::dequeueMinN(const size_t n) {
        _checkN(n);
        T result;
        if (n == 1) {
            result = _list.header()->element;
            _list.deleteFromHeader();
        }
        else {
            auto node = _list.getKthNode(n - 1);
            result = node->next()->element;
            _list.deleteAfterNode(node);
        }
        return result;
    }

}

#endif //ALGORITHM_PRIORITY_QUEUE_H
