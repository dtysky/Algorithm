//
//  queue_based_on_array
//  Algorithm
//
//  Created by dtysky on 16/9/8.
//  Copyright © 2016 dtysky@outlook.com. All rights reserved.
//

#ifndef ALGORITHM_QUEUE_BASED_ON_ARRAY_H
#define ALGORITHM_QUEUE_BASED_ON_ARRAY_H

#include <cstdio>
#include <iostream>
#include <array>


namespace data_structures {
    using std::ostream;
    using std::cout;
    using std::endl;

    template <typename T, size_t Size>
    class QueueBasedOnArray {

    protected:
        std::array<T, Size> _array;
        int _cursor_front, _cursor_rear;
        bool _empty, _full;

    public:
        QueueBasedOnArray();
        QueueBasedOnArray(const QueueBasedOnArray<T, Size>& queue);
        virtual ~QueueBasedOnArray();
        bool isEmpty() const;
        bool isFull() const;
        QueueBasedOnArray<T, Size>& clear();
        QueueBasedOnArray<T, Size>& enqueue(const T& element);
        T dequeue();
        T front();
        T rear();
        void operator=(const QueueBasedOnArray<T, Size>& queue);
        bool operator==(const QueueBasedOnArray<T, Size>& queue);
        bool operator!=(const QueueBasedOnArray<T, Size>& queue);
        friend ostream& operator<<(ostream& out, const QueueBasedOnArray<T, Size>& queue){
            cout << "Front ---- ";
            if (queue.isEmpty()) {}
            else if (queue._cursor_front < queue._cursor_rear) {
                for(auto i = queue._cursor_front + 1; i <= queue._cursor_rear; i++) {
                    cout << queue._array[i] << " ";
                }
            }
            else {
                for(auto i = queue._cursor_front + 1; i < Size; i++) {
                    cout << queue._array[i] << " ";
                }
                for(auto i = 0; i <= queue._cursor_rear; i++) {
                    cout << queue._array[i] << " ";
                }
            }
            cout << " ---- Rear";
            return out;
        };
    };


    template <typename T, size_t Size> inline
    QueueBasedOnArray<T, Size>::QueueBasedOnArray() {
        _cursor_front = _cursor_rear = (int) (Size - 1);
        _full = false;
        _empty = true;
        _array = std::array<T, Size>();
    }

    template <typename T, size_t Size> inline
    QueueBasedOnArray<T, Size>::QueueBasedOnArray(const QueueBasedOnArray<T, Size>& queue) {
        _cursor_front = queue._cursor_front;
        _cursor_rear = queue._cursor_rear;
        _full = queue._full;
        _empty = queue._empty;
        _array = queue._array;
    }

    template <typename T, size_t Size> inline
    QueueBasedOnArray<T, Size>::~QueueBasedOnArray() {}

    template <typename T, size_t Size> inline
    void QueueBasedOnArray<T, Size>::operator=(const QueueBasedOnArray<T, Size>& queue){
        _cursor_front = queue._cursor_front;
        _cursor_rear = queue._cursor_rear;
        _full = queue._full;
        _empty = queue._empty;
        _array = queue._array;
    }

    template <typename T, size_t Size> inline
    bool QueueBasedOnArray<T, Size>::operator==(const QueueBasedOnArray<T, Size>& queue){
        return _array == queue._array && _cursor_front == queue._cursor_front && _cursor_rear == queue._cursor_rear;
    }

    template <typename T, size_t Size> inline
    bool QueueBasedOnArray<T, Size>::operator!=(const QueueBasedOnArray<T, Size>& queue){
        return _cursor_front != queue._cursor_front || _cursor_rear != queue._cursor_rear || _array != queue._array;
    }

    template <typename T, size_t Size> inline
    bool QueueBasedOnArray<T, Size>::isEmpty() const {
        return _empty;
    }

    template <typename T, size_t Size> inline
    bool QueueBasedOnArray<T, Size>::isFull() const {
        return _full;
    }

    template <typename T, size_t Size> inline
    QueueBasedOnArray<T, Size>& QueueBasedOnArray<T, Size>::clear() {
        _array = std::array<T, Size>();
        _cursor_front = _cursor_rear = (int) (Size - 1);
        _full = false;
        _empty = true;
        return *this;
    }

    template <typename T, size_t Size> inline
    QueueBasedOnArray<T, Size>& QueueBasedOnArray<T, Size>::enqueue(const T& element) {
        if (isFull()) {
            throw std::out_of_range("Queue overflow !");
        }
        if (_cursor_rear == Size - 1) {
            _cursor_rear = -1;
        }
        _array[++_cursor_rear] = element;
        if (_cursor_rear == _cursor_front) {
            _full = true;
        }
        _empty = false;
        return *this;
    }

    template <typename T, size_t Size> inline
    T QueueBasedOnArray<T, Size>::dequeue() {
        if (isEmpty()) {
            throw std::out_of_range("Noting in this queue !");
        }
        if (_cursor_front == Size - 1) {
            _cursor_front = -1;
        }
        if (++_cursor_front == _cursor_rear) {
            _empty = true;
        }
        _full = false;
        return _array[_cursor_front];
    }

    template <typename T, size_t Size> inline
    T QueueBasedOnArray<T, Size>::front() {
        if (isEmpty()) {
            throw std::out_of_range("Noting in this queue !");
        }
        return _array[_cursor_front];
    }

    template <typename T, size_t Size> inline
    T QueueBasedOnArray<T, Size>::rear(){
        if (isEmpty()) {
            throw std::out_of_range("Noting in this queue !");
        }
        return _array[_cursor_rear];
    }

}

#endif //ALGORITHM_QUEUE_BASED_ON_ARRAY_H
