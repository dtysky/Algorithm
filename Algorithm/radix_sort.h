//
//  bucket_sort.hpp
//  Algorithm
//
//  Created by dtysky on 16/8/31.
//  Copyright © 2016年 dtysky@outlook.com. All rights reserved.
//

#ifndef radix_sort_hpp
#define radix_sort_hpp

#include <cstdio>
#include <vector>
#include <cmath>
#include "linked_list.h"


namespace my_algorithm {
    using std::vector;
    using data_structures::LinkedList;

    // time: O(t_msd(t_size + t_size))
    // space: O(t_size * t_radix)
    void radixSort(vector<uint32_t>& t_vector, const uint32_t t_msd, const uint32_t t_radix, const bool reverse = false) {

        for (auto dig = 0; dig < t_msd; dig++) {
            auto counts = vector<LinkedList<uint32_t>>(size_t(t_radix));
            for (auto t: t_vector) {
                counts[uint32_t(t / pow(t_radix, dig)) % t_radix].insertToTail(t);
            }
            auto position = 0;
            for (auto count: counts) {
                for (auto node = count.begin(); node != count.end(); node = node->next()) {
                    t_vector[position] = node->element;
                    position++;
                }
            }
        }

        if (reverse) {
            auto tmp = t_vector;
            auto size = t_vector.size();
            for (auto i = 0; i < size; i++) {
                t_vector[i] = tmp[size - 1 - i];
            }
        }

    }
}


#endif /* radix_sort_hpp */
