//
//  polynomial.cpp
//  Algorithm
//
//  Created by DaiTianyu on 16/8/28.
//  Copyright © 2016年 dtysky@outlook.com. All rights reserved.
//

#include "polynomial.hpp"

namespace data_structures {
    void testPolynomail() {
        
        auto py1 = Polynomail<PolynomailUnit>(vector<PolynomailUnit>{
            {1000, 4},
            {100, 3},
            {10, 2},
            {1, 1}
        });
        auto py2 = Polynomail<PolynomailUnit>(vector<PolynomailUnit>{
            {10000, 5},
            {200, 3},
            {10, 2},
            {1, 2}
        });
        auto py3 = py2 + py1;
        cout << (py3) << endl;
    }
}