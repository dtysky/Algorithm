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


namespace algorithm {
    using std::vector;
    
    void bucketSort(vector<int>& t_vector, const int t_max, const bool reverse = false) {
        vector<int> bucket = vector<int>(t_max + 1);
        for (auto t: t_vector) {
            bucket[t] = 1;
        }
        
        int index = 0;
        
        if (reverse) {
            for (auto i = bucket.size(); i > 0; i--) {
                if (bucket[i - 1] == 1) {
                    t_vector[index] = int(i - 1);
                    index++;
                }
            }
            return;
        }
        
        
        for (auto i = 0; i < bucket.size(); i++) {
            if (bucket[i] == 1) {
                t_vector[index] = i;
                index++;
            }
        }
    }
}


#endif /* bucket_sort_hpp */
