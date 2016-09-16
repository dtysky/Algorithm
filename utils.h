//
//  utils.hpp
//  Algorithm
//
//  Created by dtysky on 16/8/31.
//  Copyright © 2016年 dtysky@outlook.com. All rights reserved.
//

#ifndef utils_hpp
#define utils_hpp

#include <cstdio>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <algorithm>

template <typename T>
void printVector(std::vector<T>& a) {
    for (auto i: a) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}


//template <typename T>
//void findInVector(const std::vector<T>& v, const T& e) {
//    return std::find(v.begin(), v.end(), e);
//}


template <typename T>
bool isInVector(const std::vector<T>& v, const T& e) {
    return std::find(v.begin(), v.end(), e) != v.end();
}


void fillVectorWithRandomNumbers(std::vector<uint32_t >& v, const uint32_t max, const uint32_t seed = 0) {
    auto size = v.size();
    srand(seed);

    for (size_t i = 0; i < size; i++) {
        v[i] = float(max) * rand() / RAND_MAX;
    }
}

template <typename T>
std::vector<T> refSort(const std::vector<T>& v) {
    auto tmp = v;
    std::sort(tmp.begin(), tmp.end());
    return tmp;
}


#endif /* utils_hpp */
