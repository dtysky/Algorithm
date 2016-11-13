//
//  polynomial_unit.hpp
//  Algorithm
//
//  Created by dtysky on 16/8/28.
//  Copyright © 2016年 dtysky@outlook.com. All rights reserved.
//

#ifndef polynomial_unit_hpp
#define polynomial_unit_hpp

#include <cstdio>
#include <cmath>
#include <iostream>

namespace data_structures{
    using std::cout;
    using std::ostream;

    struct PolynomailUnit {
        float exponent;
        float coefficient;
        PolynomailUnit() {
            exponent = 0;
            coefficient = 0;
        }
        bool isZero() {
            return coefficient == 0;
        }
        float eval(const float& x) {
            return coefficient * pow(x, exponent);
        }
        bool operator==(const PolynomailUnit& unit) const {
            return exponent == unit.exponent && coefficient == unit.coefficient;
        };
        bool operator!=(const PolynomailUnit& unit) const {
            return exponent != unit.exponent || coefficient != unit.coefficient;
        };
    };
    
    
    ostream& operator<<(ostream& out, const PolynomailUnit& unit){
        cout << unit.coefficient << "x^" << unit.exponent;
        return out;
    };
}

#endif /* polynomial_unit_hpp */
