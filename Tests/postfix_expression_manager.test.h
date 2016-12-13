//
//  postfix_expression_manager
//  Algorithm
//
//  Created by dtysky on 16/9/6.
//  Copyright © 2016 dtysky@outlook.com. All rights reserved.
//

#ifndef ALGORITHM_POSTFIX_EXPRESSION_MANAGER_TEST_H
#define ALGORITHM_POSTFIX_EXPRESSION_MANAGER_TEST_H

#include <cstdio>
#include <iostream>
#include <cmath>
#include "utils.h"
#include "postfix_expression_manager.h"


namespace my_algorithm {

    class MyInt {
    protected:
        int _value;
    public:
        static const std::vector<std::vector<std::string>> operators;
        MyInt() { _value = 0; }
        MyInt(const MyInt& i) { _value = i._value; }
        MyInt(const int i) { _value = i; }
        MyInt(const float f) { _value = int(f); }
        MyInt(const double d) { _value = int(d); }
        MyInt(const std::string& str) { _value = std::stoi(str); }
        void operator=(const MyInt& i) { _value = i._value; }
        void operator=(const int i) { _value = i; }
        void operator=(const double f) { _value = int(f); }
        void operator=(const float d) { _value = int(d); }
        void operator=(const std::string& str) { _value = std::stoi(str); }
        friend std::ostream& operator<<(std::ostream& out, const MyInt& i){
            std::cout << i._value;
            return out;
        };
        MyInt exec(const std::string& opt, const MyInt& i = 0) {
            if(opt == "+") { return _value + i._value; }
            if(opt == "-") { return _value - i._value; }
            if(opt == "*") { return _value * i._value; }
            if(opt == "/") { return _value / i._value; }
            if(opt == "%") { return _value % i._value; }
            if(opt == "&") { return _value & i._value; }
            if(opt == "|") { return _value | i._value; }
            if(opt == "^") { return _value ^ i._value; }
            if(opt == "**") { return pow(i._value, _value); }
            return _value;
        }
    };

    const std::vector<std::vector<std::string>> MyInt::operators = {
        {"+", "-"},
        {"*", "/", "%"},
        {"&", "|", "^", "!", "**"}
    };

    void testPostfixExpressionManager() {

        my_algorithm::PostfixExpressionManager<MyInt> manager;
        auto expression = std::vector<std::string>{
            "5", "1", "*", "6", "+", "7", "1", "*", "+"
        };
        printVector<std::string>(expression);
        std::cout << manager.eval(expression) << std::endl;

        expression = {
            "1", "2", "+", "3", "*", "4", "-", "5", "/", "6", "%", "7", "&", "8", "|", "9", "^", "10", "**"
        };
        printVector<std::string>(expression);
        std::cout << manager.eval(expression) << std::endl;

        expression = {
            "(", "1", "+", "2", ")", "*", "3", "-", "4", "/", "5", "%", "6", "&", "7", "|", "8", "^", "9", "**", "10"
        };
        printVector<std::string>(expression);
        expression = manager.fromInfixExpression(expression);
        printVector<std::string>(expression);
        std::cout << manager.eval(expression) << std::endl;
    }
}

#endif //ALGORITHM_POSTFIX_EXPRESSION_MANAGER_TEST_H
