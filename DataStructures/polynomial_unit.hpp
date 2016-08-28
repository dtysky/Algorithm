//
//  polynomial_unit.hpp
//  Algorithm
//
//  Created by DaiTianyu on 16/8/28.
//  Copyright © 2016年 dtysky@outlook.com. All rights reserved.
//

#ifndef polynomial_unit_hpp
#define polynomial_unit_hpp

#include <stdio.h>

namespace data_structures{
    using namespace std;
    struct PolynomailUnit {
        float exponent;
        float coefficient;
        bool operator==(const PolynomailUnit& unit) {
            return exponent == unit.exponent && coefficient == unit.coefficient;
        };
    };
    
    
    ostream& operator<<(ostream& out, const PolynomailUnit& py){
        cout << py.coefficient << "x^" << py.exponent;
        return out;
    };
}

#endif /* polynomial_unit_hpp */
