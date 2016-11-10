//
//  stack
//  Algorithm
//
//  Created by dtysky on 16/9/4.
//  Copyright © 2016 dtysky@outlook.com. All rights reserved.
//

#ifndef ALGORITHM_STACK_H
#define ALGORITHM_STACK_H

#include <cstdio>
#include "linked_list.h"


namespace data_structures {
    template <typename T>
    class Stack {

    protected:
        LinkedList<T> _list;

    public:
        Stack();
        Stack(const Stack<T>& stack);
        virtual ~Stack();
        bool isEmpty() const;
        Stack<T>& clear();
        Stack<T>& push(const T& element);
        T pop();
        T top();
        Stack<T>& operator=(const Stack<T>& stack);
        bool operator==(const Stack<T>& stack);
        bool operator!=(const Stack<T>& stack);
        friend ostream& operator<<(ostream& out, const Stack<T>& stack){
            cout << "Top ---- ";
            cout << stack._list;
            cout << " ---- Bottom";
            return out;
        };
    };


    template <typename T> inline
    Stack<T>::Stack() {
        _list = LinkedList<T>();
    }

    template <typename T> inline
    Stack<T>::Stack(const Stack<T>& stack) {
        _list =  LinkedList<T>(stack._list);
    }

    template <typename T> inline
    Stack<T>::~Stack() {}

    template <typename T> inline
    Stack<T>& Stack<T>::operator=(const Stack<T>& stack){
        _list = stack._list;
        return *this;
    }

    template <typename T> inline
    bool Stack<T>::operator==(const Stack<T>& stack){
        return _list == stack._list;
    }

    template <typename T> inline
    bool Stack<T>::operator!=(const Stack<T>& stack){
        return _list != stack._list;
    }

    template <typename T> inline
    bool Stack<T>::isEmpty() const {
        return _list.isEmpty();
    }

    template <typename T> inline
    Stack<T>& Stack<T>::clear() {
        _list.clear();
        return *this;
    }

    template <typename T> inline
    Stack<T>& Stack<T>::push(const T& element) {
        _list.insertToHeader(element);
        return *this;
    }

    template <typename T> inline
    T Stack<T>::pop() {
        if (isEmpty()) {
            throw std::out_of_range("Noting in this stack !");
        }
        T result = _list.begin()->element;
        _list.deleteFromHeader();
        return result;
    }

    template <typename T> inline
    T Stack<T>::top() {
        if (isEmpty()) {
            throw std::out_of_range("Noting in this stack !");
        }
        return _list.begin()->element;
    }

}


#endif //ALGORITHM_STACK_H
