//
//  binary_search
//  Algorithm
//
//  Created by dtysky on 16/9/9.
//  Copyright © 2016 dtysky@outlook.com. All rights reserved.
//

#ifndef ALGORITHM_BINARY_SEARCH_H
#define ALGORITHM_BINARY_SEARCH_H

#include <cstdio>
#include <vector>


namespace my_algorithm {

    // time: O(log(n))
    // space: O(1)
    template <typename T>
    int binarySearch(const std::vector<T>& t_vector, const T& element) {
        size_t left = 0;
        size_t right = t_vector.size() - 1;
        size_t middle;
        while (true) {
            middle = (left + right) / 2;
            if (left > right) {
                return -1;
            }
            if (t_vector[middle] == element) {
                return (int)middle;
            }
            if (t_vector[middle] > element) {
                right = middle - 1;
            } else {
                left = middle + 1;
            }
        }
    }
}

#endif //ALGORITHM_BINARY_SEARCH_H
