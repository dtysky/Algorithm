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
        auto py1 = Polynomail<PolynomailUnit, float>(vector<PolynomailUnit>{
            {6, 4},
            {5, 3},
            {2, 2},
            {1, 1}
        });
        auto py2 = Polynomail<PolynomailUnit, float>(vector<PolynomailUnit>{
            {6, 5},
            {3, 3},
            {2, 2},
            {1, 2}
        });
        cout << py1 << endl;
        cout << py1.eval(2) << endl;
        cout << py2 << endl;
        cout << -py1 << endl;
        cout << (py2 + py1) << endl;
        cout << (py2 - py1) << endl;
        cout << (py2 * py1) << endl;
    }
}