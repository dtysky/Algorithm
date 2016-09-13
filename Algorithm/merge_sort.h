//
//  merge_sort
//  Algorithm
//
//  Created by dtysky on 16/9/13.
//  Copyright © 2016 dtysky@outlook.com. All rights reserved.
//

#ifndef ALGORITHM_MERGE_SORT_H
#define ALGORITHM_MERGE_SORT_H

#include <cstdio>
#include <vector>


namespace my_algorithm {
    using std::vector;

    // time: O(n * log(n))
    // space: O(n)
    template <typename T>
    void mergeSort(vector<T>& t_vector, const bool reverse = false) {
        auto size = t_vector.size();
        size_t step = 1;

        while (step < size) {
            auto tmp = vector<T>();

            for (size_t begin = 0; begin < size; begin += 2 * step) {
                auto middle = (begin + step) > size ? size : (begin + step);
                auto end = (middle + step) > size ? size : (middle + step);

                if (middle == end) {
                    for (auto i = begin; i < end; i++) {
                        tmp.push_back(t_vector[i]);
                    }
                    continue;
                }

                if (reverse && t_vector[middle - 1] > t_vector[middle]) {
                    for (auto i = begin; i < end; i++) {
                        tmp.push_back(t_vector[i]);
                    }
                    continue;
                }

                if (!reverse && t_vector[middle - 1] < t_vector[middle]) {
                    for (auto i = begin; i < end; i++) {
                        tmp.push_back(t_vector[i]);
                    }
                    continue;
                }

                auto i1 = begin;
                auto i2 = middle;

                while (i1 < middle || i2 < end) {
                    if (i1 == middle) {
                        tmp.push_back(t_vector[i2]);
                        i2++;
                    }
                    else if (i2 == end) {
                        tmp.push_back(t_vector[i1]);
                        i1++;
                    }
                    else if (reverse && t_vector[i1] > t_vector[i2]) {
                        tmp.push_back(t_vector[i1]);
                        i1++;
                    }
                    else if (!reverse && t_vector[i1] < t_vector[i2]) {
                        tmp.push_back(t_vector[i1]);
                        i1++;
                    }
                    else {
                        tmp.push_back(t_vector[i2]);
                        i2++;
                    }
                }

            }

            t_vector = tmp;
            step *= 2;
        }
    }
}

#endif //ALGORITHM_MERGE_SORT_H
