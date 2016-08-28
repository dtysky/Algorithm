//
//  polynomial.cpp
//  Algorithm
//
//  Created by DaiTianyu on 16/8/28.
//  Copyright © 2016年 dtysky@outlook.com. All rights reserved.
//

#include "polynomial.hpp"

namespace algorithm {
    void testPolynomail() {
        
        Polynomail<PolynomailUnit> py1 = Polynomail<PolynomailUnit>(vector<PolynomailUnit>{
            {1000, 4},
            {100, 3},
            {10, 2},
            {1, 1}
        });
        
        cout << py1 << endl;
    }
}