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
        bool operator==(const BinaryHeap<T, Size> &heap);
        bool operator!=(const BinaryHeap<T, Size> &heap);
        void print32_tSlicing(const size_t start, const size_t end, const int32_t indent, const int32_t line) const;
        friend std::ostream &operator<<(std::ostream &out, const BinaryHeap<T, Size> &heap) {
            auto lines = float(int32_t(log2f(heap.size())));
            int32_t line = 0;
            int32_t indent;
            size_t start = 0;
            size_t end = 0;
            auto size = heap.size();
            while (end <= size) {
                indent = int32_t(6 * powf(2.0, lines - line));
                heap.print32_tSlicing(start, end, indent, line);
                if (start == 0) {
                    end = 1;
                }
                start = end;
                end *= 2;
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
        _size = 0;
    }

    template<typename T, size_t Size> inline
    BinaryHeap<T, Size>::~BinaryHeap() {
        _size = 0;
    }

    template<typename T, size_t Size> inline
    BinaryHeap<T, Size>& BinaryHeap<T, Size>::operator=(const BinaryHeap<T, Size>& heap) {
        _array = heap._array;
        _size = 0;
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
    void BinaryHeap<T, Size>::print32_tSlicing(const size_t start, const size_t end, const int32_t indent, const int32_t line) const {
        double_t lead;
        if (line == 0) {
            lead = 0;
        } else {
            lead = (2 * line - 1) / 2.0;
        }
        for (size_t i = start; i <= end; i++) {
            if (i == start && start !=0) {
                std::cout << std::setw(int32_t(indent * (lead + 1)));
            } else {
                std::cout << std::setw(indent);
            }
            std::cout << _array[i];
        }
        std::cout << std::endl;
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
        auto current = k;
        auto parent = (current - 1) / 2;
        while (parent != 0 && _compare(_array[current], _array[parent])) {
            parent = (current - 1) / 2;
            _exec(current, parent);
            current = parent;
        }
    }

    template<typename T, size_t Size> inline
    void BinaryHeap<T, Size>::_sink(const size_t k) {
        auto current = k;
        auto left = (current + 1) * 2 - 1;
        auto right = (current + 1) * 2;
        auto size = this->size();
        while (true) {
            if (left > size) {
                return;
            }
            bool l_c_c, r_c_c, l_c_r;
            l_c_c = _compare(_array[current], _array[left]);
            if (left <= size && right > size) {
                if (!l_c_c) {
                    _exec(current, left);
                }
                return;
            }
            r_c_c = _compare(_array[current], _array[right]);
            l_c_r = _compare(_array[left], _array[right]);
            if (l_c_r && !l_c_c) {
                _exec(current, left);
                continue;
            }
            if (!l_c_r && !r_c_c) {
                _exec(current, right);
            }
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
        _exec(0, _size);
        _sink(0);
        _size--;
        return tmp;
    }


    template<typename T, size_t Size>
    class MaxBinaryHeap: public BinaryHeap<T, Size> {
    protected:
        bool _compare(const T &element1, const T &element2) {
            return element1 >= element2;
        }
    };

    template<typename T, size_t Size>
    class MinBinaryHeap: public BinaryHeap<T, Size> {
    protected:
        bool _compare(const T &element1, const T &element2) {
            return element1 <= element2;
        }
    };
};


#endif //ALGORITHM_BINARY_HEAP_H
