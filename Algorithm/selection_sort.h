//
//  selection_sort
//  Algorithm
//
//  Created by dtysky on 16/9/9.
//  Copyright © 2016 dtysky@outlook.com. All rights reserved.
//

#ifndef ALGORITHM_SELECTION_SORT_H
#define ALGORITHM_SELECTION_SORT_H

#include <cstdio>
#include <vector>


namespace my_algorithm {
    using std::vector;

    // time: O(t_size + t_max)
    // space: O(t_max)
    void selectionSort(vector<uint32_t>& t_vector, const bool reverse = false) {
        size_t cursor_current = 0;
        auto size = t_vector.size();

        for (size_t begin = 0; begin < size; begin++) {
            cursor_current = begin;
            for (size_t i = begin; i < size; i++) {

                if (reverse) {
                    if (t_vector[i] > t_vector[cursor_current]) {
                        cursor_current = i;
                    }
                    continue;
                }

                if (t_vector[i] < t_vector[cursor_current]) {
                    cursor_current = i;
                }

            }

            auto tmp = t_vector[begin];
            t_vector[begin] = t_vector[cursor_current];
            t_vector[cursor_current] = tmp;
        }
    }
}

#endif //ALGORITHM_SELECTION_SORT_H
