//
//  binary_heap
//  Algorithm
//
//  Created by dtysky on 16/10/19.
//  Copyright © 2016 dtysky@outlook.com. All rights reserved.
//

#ifndef ALGORITHM_BINARY_HEAP_H
#define ALGORITHM_BINARY_HEAP_H

#include <cstdio>
#include <iostream>
#include <array>
#include <iomanip>
#include "utils.h"


namespace data_structures {
    template<typename T, size_t Size>
    class BinaryHeap {
    protected:
        std::array<T, Size> _array;
        virtual bool _compare(const T &element1, const T &element2);
        void _exec(const size_t k1, const size_t k2);
        void _swim(const size_t k);
        void _sink(const size_t k);

    public:
        BinaryHeap();
        BinaryHeap(BinaryHeap<T, Size> &heap);
        virtual ~BinaryHeap();
        bool isEmpty();
        bool isEmpty() const;
        size_t size();
        size_t size() const;
        BinaryHeap& clear();
        BinaryHeap& insert(const T &element);
        T top();
        T deleteTop();
        BinaryHeap<T, Size>& operator=(const BinaryHeap<T, Size> &heap);
        bool operator==(const BinaryHeap<T, Size> &heap);
        bool operator!=(const BinaryHeap<T, Size> &heap);
        void printSlicing(const size_t start, const size_t end) const;
        friend std::ostream &operator<<(std::ostream &out, const BinaryHeap<T, Size> &heap) {
            size_t start = 0;
            size_t end = 1;
            auto size = heap.size();
            while (end <= size) {
                heap.printSlicing(start, end);
                start = end;
                end *= 2;
            }
            return out;
        };
    };


    template<typename T, size_t Size> inline
    BinaryHeap<T, Size>::BinaryHeap() {
        _array = std::array<T, Size>();
    }

    template<typename T, size_t Size> inline
    BinaryHeap<T, Size>::BinaryHeap(BinaryHeap<T, Size> &heap) {
        _array = heap._array;
    }

    template<typename T, size_t Size> inline
    BinaryHeap<T, Size>::~BinaryHeap() {}

    template<typename T, size_t Size> inline
    BinaryHeap<T, Size>& BinaryHeap<T, Size>::operator=(const BinaryHeap<T, Size>& heap) {
        _array = heap._array;
        return *this;
    }

    template<typename T, size_t Size> inline
    bool BinaryHeap<T, Size>::operator==(const BinaryHeap<T, Size>& heap) {
        return _array == heap._array;
    }

    template<typename T, size_t Size> inline
    bool BinaryHeap<T, Size>::operator!=(const BinaryHeap<T, Size>& heap) {
        return _array != heap._array;
    }

    template<typename T, size_t Size> inline
    void BinaryHeap<T, Size>::printSlicing(const size_t start, const size_t end) const {
        auto indent = 0;
        for (auto element: sliceArray<T, Size>(_array, start, end)) {
            std::cout << std::setw(indent);
            std::cout << element;
        }
        std::cout << std::endl;
    }

    template<typename T, size_t Size> inline
    bool BinaryHeap<T, Size>::isEmpty() {
        return _array.empty();
    }

    template<typename T, size_t Size> inline
    bool BinaryHeap<T, Size>::isEmpty() const {
        return _array.empty();
    }

    template<typename T, size_t Size> inline
    BinaryHeap<T, Size>& BinaryHeap<T, Size>::clear() {
        _array = std::array<T, Size>();
        return *this;
    }

    template<typename T, size_t Size> inline
    size_t BinaryHeap<T, Size>::size() {
        return _array.size();
    }

    template<typename T, size_t Size> inline
    size_t BinaryHeap<T, Size>::size() const {
        return _array.size();
    }

    template<typename T, size_t Size> inline
    bool BinaryHeap<T, Size>::_compare(const T &element1, const T &element2) {
        return element1 < element2;
    }

    template<typename T, size_t Size> inline
    void BinaryHeap<T, Size>::_exec(const size_t k1, const size_t k2){
        auto tmp = _array[k1];
        _array[k1] = _array[k2];
        _array[k2] = tmp;
    }

    template<typename T, size_t Size> inline
    void BinaryHeap<T, Size>::_swim(HeapNode<T> *node) {
        if (node->parent() == nullptr) {
            return;
        }
        auto current = node;
        auto parent = current->parent();
        while (parent != nullptr && _compare(current->element, parent->element)) {
            parent = current->parent();
            _exec(current, parent);
            current = parent;
        }
    }

    template<typename T, size_t Size> inline
    void BinaryHeap<T, Size>::_sink(HeapNode<T> *node) {
        if (node->left() == nullptr && node->right() == nullptr) {
            return;
        }
        auto current = node;
        auto left = current->left();
        auto right = current->right();
        while (
            (left != nullptr && !_compare(current->element, left->element)) ||
            (right != nullptr && !_compare(current->element, right->element))
        ) {
            left = current->left();
            right = current->right();
            if (left == nullptr) {
                _exec(current, right);
                current = right;
                continue;
            }
            if (right == nullptr) {
                _exec(current, left);
                current = left;
                continue;
            }
            if (_compare(left->element, right->element)) {
                _exec(current, left);
                current = left;
            } else {
                _exec(current, right);
                current = right;
            }
        }
    }

    template<typename T, size_t Size> inline
    BinaryHeap<T, Size>& BinaryHeap<T, Size>::insert(const T &element) {
        if (_tail->left() == nullptr) {
            _tail->insertLeft(new HeapNode<T>(element));
            _tail = _tail->left();
        } else {
            _tail->insertRight(new HeapNode<T>(element));
            _tail = _tail->right();
        }
        _size++;
        _swim(_tail);
        return *this;
    }

    template<typename T, size_t Size> inline
    T BinaryHeap<T, Size>::top() {
        return _array[0];
    }

    template<typename T, size_t Size> inline
    T BinaryHeap<T, Size>::deleteTop() {
        auto tmp = _root->element;
        if (isEmpty()) {
            clear();
            return tmp;
        }
        _exec(_root, _tail);
        auto parent = _tail->parent();
        if (parent->right() != nullptr) {
            delete parent->deleteRight();
        } else {
            delete parent->deleteLeft();
        }
        _sink(_root);
        _size--;
        return tmp;
    }


    template<typename T, size_t Size>
    class MaxBinaryHeap: public BinaryHeap<T, Size> {
    protected:
        bool _compare(const T &element1, const T &element2) {
            return element1 > element2;
        }
    };

    template<typename T, size_t Size>
    class MinBinaryHeap: public BinaryHeap<T, Size> {
    protected:
        bool _compare(const T &element1, const T &element2) {
            return element1 < element2;
        }
    };
};


#endif //ALGORITHM_BINARY_HEAP_H
