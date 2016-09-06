//
//  postfix_expression_manager
//  Algorithm
//
//  Created by dtysky on 16/9/6.
//  Copyright © 2016 dtysky@outlook.com. All rights reserved.
//

#ifndef ALGORITHM_POSTFIX_EXPRESSION_MANAGER_H
#define ALGORITHM_POSTFIX_EXPRESSION_MANAGER_H

#include <cstdio>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include "stack.h"


namespace my_algorithm {

    template <typename T>
    class PostfixExpressionManager {

    protected:
        const std::vector<std::vector<std::string>> _operators = T::operators;
        data_structures::Stack<T> _stack;
        data_structures::Stack<std::vector<std::string>> _stack_converter;
        std::vector<std::string> _all_operators;

    public:
        PostfixExpressionManager();
        PostfixExpressionManager(const PostfixExpressionManager<T>& manager);
//        PostfixExpressionManager(const std::vector<std::vector<std::string>>& operators);
        virtual ~PostfixExpressionManager();
        T eval(const std::vector<std::string>& expression);
        std::vector<std::string> fromInfixExpression(const std::vector<std::string>& expression);
    };


    template <typename T> inline
    PostfixExpressionManager<T>::PostfixExpressionManager() {
        _stack = {};
        _stack_converter = {};
        _all_operators = std::vector<std::string>();
        for (auto ops: _operators) {
            for (auto op: ops) {
                _all_operators.push_back(op);
            }
        }
    }

    template <typename T> inline
    PostfixExpressionManager<T>::PostfixExpressionManager(const PostfixExpressionManager<T> &manager) {
        _stack = manager._stack;
        _stack_converter = manager._stack_converter;
        _all_operators = manager._all_operators;
    }

    template <typename T> inline
    PostfixExpressionManager<T>::~PostfixExpressionManager() {}

    template <typename T> inline
    T PostfixExpressionManager<T>::eval(const std::vector<std::string> &expression) {
        _stack.clear();
        for (auto e: expression) {
            if (std::find(_all_operators.begin(), _all_operators.end(), e) == _all_operators.end()) {
                _stack.push(T(e));
                continue;
            }
            _stack.push(_stack.pop().exec(e, _stack.pop()));
        }
        return _stack.pop();
    }

    template <typename T> inline
    std::vector<std::string> PostfixExpressionManager<T>::fromInfixExpression(const std::vector<std::string> &expression) {

    }

}

#endif //ALGORITHM_POSTFIX_EXPRESSION_MANAGER_H
