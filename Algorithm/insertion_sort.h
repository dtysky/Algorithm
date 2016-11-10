//
//  insertion_sort
//  Algorithm
//
//  Created by dtysky on 16/9/11.
//  Copyright © 2016 dtysky@outlook.com. All rights reserved.
//

#ifndef ALGORITHM_INSERTION_SORT_H
#define ALGORITHM_INSERTION_SORT_H

#include <cstdio>
#include <vector>


namespace my_algorithm {
    using std::vector;

    // time: O(n) ~ O(n^2)
    // space: O(1)
    template <typename T>
    void insertionSort(vector<T>& t_vector, const bool reverse = false, const size_t low = 0, const size_t high = 0) {

        auto t_size = high == 0 ? t_vector.size() : high + 1;
        size_t end, current;
        T tmp;

        for (size_t i = low + 1; i < t_size; i++) {
            end = i;
            current = end;
            tmp = t_vector[end];

            if (reverse) {
                while (current > 0 && t_vector[current - 1] < tmp) {
                    t_vector[current] = t_vector[current - 1];
                    current--;
                }
            }
            else {
                while (current > 0 && t_vector[current - 1] > tmp) {
                    t_vector[current] = t_vector[current - 1];
                    current--;
                }
            }

            t_vector[current] = tmp;
        }
    }
}

#endif //ALGORITHM_INSERTION_SORT_H
