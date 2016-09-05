//
//  stack_based_on_array
//  Algorithm
//
//  Created by dtysky on 16/9/4.
//  Copyright © 2016 dtysky@outlook.com. All rights reserved.
//

#ifndef ALGORITHM_STACK_BASED_ON_ARRAY_H
#define ALGORITHM_STACK_BASED_ON_ARRAY_H

#include <cstdio>
#include <iostream>
#include <array>


namespace data_structures {
    using std::ostream;
    using std::cout;
    using std::endl;

    template <typename T, size_t Size>
    class StackBasedOnArray {

    protected:
        std::array<T, Size> _array;
        int _cursor;

    public:
        StackBasedOnArray();
        StackBasedOnArray(const StackBasedOnArray<T, Size>& stack);
        virtual ~StackBasedOnArray();
        bool isEmpty() const;
        StackBasedOnArray<T, Size>& clear();
        StackBasedOnArray<T, Size>& push(const T& element);
        T pop();
        T top();
        void operator=(const StackBasedOnArray<T, Size>& stack);
        bool operator==(const StackBasedOnArray<T, Size>& stack);
        bool operator!=(const StackBasedOnArray<T, Size>& stack);
        friend ostream& operator<<(ostream& out, const StackBasedOnArray<T, Size>& stack){
            cout << "Top ---- ";
            for(auto i = 0; i <= stack._cursor; i++) {
                cout << stack._array[i] << " ";
            }
            cout << " ---- Bottom";
            return out;
        };
    };


    template <typename T, size_t Size> inline
    StackBasedOnArray<T, Size>::StackBasedOnArray() {
        _cursor = -1;
        _array = std::array<T, Size>();
    }

    template <typename T, size_t Size> inline
    StackBasedOnArray<T, Size>::StackBasedOnArray(const StackBasedOnArray<T, Size>& stack) {
        _cursor = stack._cursor;
        _array = stack._array;
    }

    template <typename T, size_t Size> inline
    StackBasedOnArray<T, Size>::~StackBasedOnArray() {}

    template <typename T, size_t Size> inline
    void StackBasedOnArray<T, Size>::operator=(const StackBasedOnArray<T, Size>& stack){
        _cursor = stack._cursor;
        _array = stack._array;
    }

    template <typename T, size_t Size> inline
    bool StackBasedOnArray<T, Size>::operator==(const StackBasedOnArray<T, Size>& stack){
        return _array == stack._array && _cursor == stack._cursor;
    }

    template <typename T, size_t Size> inline
    bool StackBasedOnArray<T, Size>::operator!=(const StackBasedOnArray<T, Size>& stack){
        return _cursor != stack._cursor || _array != stack._array;
    }

    template <typename T, size_t Size> inline
    bool StackBasedOnArray<T, Size>::isEmpty() const {
        return _cursor == -1;
    }

    template <typename T, size_t Size> inline
    StackBasedOnArray<T, Size>& StackBasedOnArray<T, Size>::clear() {
        _array = std::array<T, Size>();
        _cursor = -1;
        return *this;
    }

    template <typename T, size_t Size> inline
    StackBasedOnArray<T, Size>& StackBasedOnArray<T, Size>::push(const T& element) {
        if (_cursor == Size - 1) {
            throw std::out_of_range("Stack overflow !");
        }
        _cursor ++;
        _array[_cursor] = element;
        return *this;
    }

    template <typename T, size_t Size> inline
    T StackBasedOnArray<T, Size>::pop() {
        if (isEmpty()) {
            throw std::out_of_range("Noting in this stack !");
        }
        T result = _array[_cursor];
        _cursor--;
        return result;
    }

    template <typename T, size_t Size> inline
    T StackBasedOnArray<T, Size>::top() {
        if (isEmpty()) {
            throw std::out_of_range("Noting in this stack !");
        }
        return _array[_cursor];
    }

}


#endif //ALGORITHM_STACK_BASED_ON_ARRAY_H
