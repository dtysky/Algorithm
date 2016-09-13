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
    // space: O(n)
    template <typename T>
    void insertionSort(vector<T>& t_vector, const bool reverse = false) {

        auto t_size = t_vector.size();
        size_t end = 0;
        size_t current = 0;
        T tmp;

        for (size_t i = 1; i < t_size; i++) {
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
