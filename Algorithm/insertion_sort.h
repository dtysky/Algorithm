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
    void insertionSort(vector<uint32_t>& t_vector, const bool reverse = false) {

        auto t_size = t_vector.size();
        size_t end = 0;
        auto tmp = t_vector[0];

        for (size_t i = 1; i < t_size; i++) {
            end = i;

            for (size_t j = end; j > 0; j--) {
                if (reverse) {
                    if (t_vector[j] > t_vector[j - 1]) {
                        tmp = t_vector[j];
                        t_vector[j] = t_vector[j - 1];
                        t_vector[j - 1] = tmp;
                        continue;
                    }
                    break;
                }

                if (t_vector[j] < t_vector[j - 1]) {
                    tmp = t_vector[j];
                    t_vector[j] = t_vector[j - 1];
                    t_vector[j - 1] = tmp;
                    continue;
                }
                break;
            }
        }
    }
}

#endif //ALGORITHM_INSERTION_SORT_H
