//
//  shell_sort
//  Algorithm
//
//  Created by dtysky on 16/9/13.
//  Copyright © 2016 dtysky@outlook.com. All rights reserved.
//

#ifndef ALGORITHM_SHELL_SORT_H
#define ALGORITHM_SHELL_SORT_H

#include <cstdio>
#include <vector>


namespace my_algorithm {
    using std::vector;

    // time: ......
    // space: O(1)
    template <typename T>
    void shellSort(vector<T>& t_vector, const vector<uint32_t>& step_queue, const bool reverse = false) {
        auto size = t_vector.size();
        size_t current = 0;
        T tmp;

        for (auto step: step_queue) {

            for (size_t start = 0; start < step; start++) {

                for (auto end = 1 * step + start; end < size; end += step) {
                    tmp = t_vector[end];
                    current = end;

                    if (reverse) {
                        while (current > start && t_vector[current - step] < tmp) {
                            t_vector[current] = t_vector[current - step];
                            current -= step;
                        }
                    }
                    else {
                        while (current > start && t_vector[current - step] > tmp) {
                            t_vector[current] = t_vector[current - step];
                            current -= step;
                        }
                    }

                    t_vector[current] = tmp;
                }
            }
        }
    }
}

#endif //ALGORITHM_SHELL_SORT_H
