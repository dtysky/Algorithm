//
//  heap_sort
//  Algorithm
//
//  Created by dtysky on 16/10/28.
//  Copyright © 2016 dtysky@outlook.com. All rights reserved.
//

#ifndef ALGORITHM_HEAP_SORT_H
#define ALGORITHM_HEAP_SORT_H

#include <cstdio>
#include <vector>
#include "binary_heap.h"


namespace my_algorithm {
    // time: O(nlog(n))
    // space: O(n)
    template<typename T, size_t Size>
    void heapSort(std::vector<T>& t_vector, bool reverse = false) {
        auto size = size_t(t_vector.size());
        if (size > Size) {
            throw std::out_of_range("Vector's size must be less than heap's.");
        }
        if (reverse) {
            data_structures::MaxBinaryHeap<T, Size> heap;
            for (int i = 0; i < size; i++) {
                heap.insert(t_vector[i]);
            }
            for (int i = 0; i < size; i++) {
                t_vector[i] = heap.deleteTop();
            }
        } else {
            data_structures::MinBinaryHeap<T, Size> heap;
            for (int i = 0; i < size; i++) {
                heap.insert(t_vector[i]);
            }
            for (int i = 0; i < size; i++) {
                t_vector[i] = heap.deleteTop();
            }
        }
    }
}


#endif //ALGORITHM_HEAP_SORT_H
