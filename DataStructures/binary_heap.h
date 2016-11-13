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
#include <cmath>


namespace data_structures {
    template<typename T, size_t Size>
    class BinaryHeap {
    protected:
        std::array<T, Size> _array;
        size_t _size;
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
        bool operator==(const BinaryHeap<T, Size> &heap) const;
        bool operator!=(const BinaryHeap<T, Size> &heap) const;
        void printRow(const int32_t line, const int32_t indent) const;
        friend std::ostream &operator<<(std::ostream &out, const BinaryHeap<T, Size> &heap) {
            auto size = heap.size();
            auto lines = float(int32_t(log2f(size)));
            int32_t line = 0;
            int32_t indent;
            while (line <= lines) {
                indent = int32_t(6 * powf(2.0, lines - line));
                heap.printRow(line, indent);
                line++;
            }
            return out;
        };
    };


    template<typename T, size_t Size> inline
    BinaryHeap<T, Size>::BinaryHeap() {
        _array = std::array<T, Size>();
        _size = 0;
    }

    template<typename T, size_t Size> inline
    BinaryHeap<T, Size>::BinaryHeap(BinaryHeap<T, Size> &heap) {
        _array = heap._array;
        _size = heap._size;
    }

    template<typename T, size_t Size> inline
    BinaryHeap<T, Size>::~BinaryHeap() {
        _size = 0;
    }

    template<typename T, size_t Size> inline
    BinaryHeap<T, Size>& BinaryHeap<T, Size>::operator=(const BinaryHeap<T, Size>& heap) {
        _array = heap._array;
        _size = heap._size;
        return *this;
    }

    template<typename T, size_t Size> inline
    bool BinaryHeap<T, Size>::operator==(const BinaryHeap<T, Size>& heap) const {
        return _array == heap._array;
    }

    template<typename T, size_t Size> inline
    bool BinaryHeap<T, Size>::operator!=(const BinaryHeap<T, Size>& heap) const {
        return _array != heap._array;
    }

    template<typename T, size_t Size> inline
    void BinaryHeap<T, Size>::printRow(const int32_t line, const int32_t indent) const {
        auto lead = (pow(2, line) - 1) / 2.0;
        auto start = size_t(pow(2, line)) - 1;
        auto end = size_t(pow(2, line + 1)) - 1;
        end = end > size() ? size() : end;
        for (size_t i = start; i < end; i++) {
            if (i == start) {
                std::cout << std::setw(int32_t(indent * (lead + 1)));
            } else {
                std::cout << std::setw(indent);
            }
            std::cout << _array[i];
        }
        std::cout << std::endl << std::endl;
    }

    template<typename T, size_t Size> inline
    bool BinaryHeap<T, Size>::isEmpty() {
        return _size == 0;
    }

    template<typename T, size_t Size> inline
    bool BinaryHeap<T, Size>::isEmpty() const {
        return _size == 0;
    }

    template<typename T, size_t Size> inline
    BinaryHeap<T, Size>& BinaryHeap<T, Size>::clear() {
        _array = std::array<T, Size>();
        _size = 0;
        return *this;
    }

    template<typename T, size_t Size> inline
    size_t BinaryHeap<T, Size>::size() {
        return _size;
    }

    template<typename T, size_t Size> inline
    size_t BinaryHeap<T, Size>::size() const {
        return _size;
    }

    template<typename T, size_t Size> inline
    bool BinaryHeap<T, Size>::_compare(const T &element1, const T &element2) {
        return element1 <= element2;
    }

    template<typename T, size_t Size> inline
    void BinaryHeap<T, Size>::_exec(const size_t k1, const size_t k2){
        auto tmp = _array[k1];
        _array[k1] = _array[k2];
        _array[k2] = tmp;
    }

    template<typename T, size_t Size> inline
    void BinaryHeap<T, Size>::_swim(const size_t k) {
        if (k == 0) {
            return;
        }
        auto current = k;
        auto parent = (current - 1) / 2;
        while (current != 0 && _compare(_array[current], _array[parent])) {
            _exec(current, parent);
            current = parent;
            parent = (current - 1) / 2;
        }
    }

    template<typename T, size_t Size> inline
    void BinaryHeap<T, Size>::_sink(const size_t k) {
        auto current = k;
        size_t left, right;
        auto size = this->size();
        while (true) {
            left = (current + 1) * 2 - 1;
            right = (current + 1) * 2;
            if (left >= size) {
                return;
            }
            bool l_c_c, r_c_c, l_c_r;
            l_c_c = _compare(_array[left], _array[current]);
            if (left == size - 1) {
                if (l_c_c) {
                    _exec(current, left);
                }
                return;
            }
            r_c_c = _compare(_array[right], _array[current]);
            l_c_r = _compare(_array[left], _array[right]);
            if (l_c_r && l_c_c) {
                _exec(current, left);
                current = left;
                continue;
            }
            if (!l_c_r && r_c_c) {
                _exec(current, right);
                current = right;
                continue;
            }
            return;
        }
    }

    template<typename T, size_t Size> inline
    BinaryHeap<T, Size>& BinaryHeap<T, Size>::insert(const T &element) {
        if (size() > _array.max_size()) {
            std::out_of_range("Heap is out of its range!");
        }
        _array[_size] = element;
        _swim(_size);
        _size++;
        return *this;
    }

    template<typename T, size_t Size> inline
    T BinaryHeap<T, Size>::top() {
        return _array[0];
    }

    template<typename T, size_t Size> inline
    T BinaryHeap<T, Size>::deleteTop() {
        auto tmp = _array[0];
        if (isEmpty()) {
            clear();
            return tmp;
        }
        _exec(0, _size - 1);
        _size--;
        _sink(0);
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
