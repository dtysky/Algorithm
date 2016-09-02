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

template <typename T>
void printVector(std::vector<T>& a) {
    for (auto i: a) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

#endif /* utils_hpp */
