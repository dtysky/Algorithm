//
//  bucket_sort.hpp
//  Algorithm
//
//  Created by dtysky on 16/8/31.
//  Copyright © 2016年 dtysky@outlook.com. All rights reserved.
//

#ifndef bucket_sort_hpp
#define bucket_sort_hpp

#include <cstdio>
#include <vector>


namespace my_algorithm {
    using std::vector;

    // time: O(t_size + t_max)
    // space: O(t_max)
    void bucketSort(vector<uint32_t>& t_vector, const uint32_t t_max, const bool reverse = false) {
        auto bucket = vector<uint32_t>(size_t(t_max + 1));
        for (auto t: t_vector) {
            bucket[t] = 1;
        }

        uint32_t index = 0;
        
        if (reverse) {
            for (auto i = bucket.size(); i > 0; i--) {
                if (bucket[i - 1] == 1) {
                    t_vector[index] = uint32_t(i - 1);
                    index++;
                }
            }
            return;
        }
        
        
        for (auto i = 0; i < bucket.size(); i++) {
            if (bucket[i] == 1) {
                t_vector[index] = uint32_t(i);
                index++;
            }
        }
    }
}


#endif /* bucket_sort_hpp */
