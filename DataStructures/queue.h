//
//  queue
//  Algorithm
//
//  Created by dtysky on 16/9/8.
//  Copyright © 2016 dtysky@outlook.com. All rights reserved.
//

#ifndef ALGORITHM_QUEUE_H
#define ALGORITHM_QUEUE_H

#include <cstdio>
#include "linked_list.h"


namespace data_structures {
    template <typename T>
    class Queue {

    protected:
        LinkedList<T> _list;

    public:
        Queue();
        Queue(const Queue<T>& queue);
        virtual ~Queue();
        bool isEmpty() const;
        Queue<T>& clear();
        Queue<T>& enqueue(const T& element);
        T dequeue();
        T front();
        T rear();
        Queue<T>& operator=(const Queue<T>& queue);
        bool operator==(const Queue<T>& queue) const;
        bool operator!=(const Queue<T>& queue) const;
        friend ostream& operator<<(ostream& out, const Queue<T>& queue){
            cout << "Front ---- ";
            cout << queue._list;
            cout << " ---- Rear";
            return out;
        };
    };


    template <typename T> inline
    Queue<T>::Queue() {
        _list = LinkedList<T>();
    }

    template <typename T> inline
    Queue<T>::Queue(const Queue<T>& queue) {
        _list =  LinkedList<T>(queue._list);
    }

    template <typename T> inline
    Queue<T>::~Queue() {}

    template <typename T> inline
    Queue<T>& Queue<T>::operator=(const Queue<T>& queue){
        _list = queue._list;
        return *this;
    }

    template <typename T> inline
    bool Queue<T>::operator==(const Queue<T>& queue) const {
        return _list == queue._list;
    }

    template <typename T> inline
    bool Queue<T>::operator!=(const Queue<T>& queue) const {
        return _list != queue._list;
    }

    template <typename T> inline
    bool Queue<T>::isEmpty() const {
        return _list.isEmpty();
    }

    template <typename T> inline
    Queue<T>& Queue<T>::clear() {
        _list.clear();
        return *this;
    }

    template <typename T> inline
    Queue<T>& Queue<T>::enqueue(const T &element){
        _list.insertToTail(element);
        return *this;
    }

    template <typename T> inline
    T Queue<T>::dequeue(){
        if (isEmpty()) {
            throw std::out_of_range("Noting in this queue !");
        }
        T result = _list.begin()->element;
        _list.deleteFromHeader();
        return result;
    }

    template <typename T> inline
    T Queue<T>::front(){
        if (isEmpty()) {
            throw std::out_of_range("Noting in this queue !");
        }
        return _list.begin()->element;
    }

    template <typename T> inline
    T Queue<T>::rear(){
        if (isEmpty()) {
            throw std::out_of_range("Noting in this queue !");
        }
        return _list.tail()->element;
    }

}


#endif //ALGORITHM_QUEUE_H
