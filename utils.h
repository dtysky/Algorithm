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

#endif /* utils_hpp */
