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
#include <cmath>
#include "utils.h"
#include "stack.h"


namespace my_algorithm {

    template <typename T>
    class PostfixExpressionManager {

    protected:
        std::vector<std::vector<std::string>> _operators;
        data_structures::Stack<T> _stack;
        data_structures::Stack<std::string> _stack_converter;
        data_structures::Stack<size_t> _stack_priority;
        std::vector<std::string> _all_operators;

    public:
        PostfixExpressionManager();
        PostfixExpressionManager(const PostfixExpressionManager<T>& manager);
        virtual ~PostfixExpressionManager();
        T eval(const std::vector<std::string>& expression);
        std::vector<std::string> fromInfixExpression(const std::vector<std::string>& expression);
    };


    template <typename T> inline
    PostfixExpressionManager<T>::PostfixExpressionManager() {
        _stack = data_structures::Stack<T>();
        _stack_converter = data_structures::Stack<std::string>();
        _stack_priority = data_structures::Stack<size_t>();
        _all_operators = {};
        _operators = T::operators;
        _operators.insert(_operators.begin(), {")"});
        _operators.push_back({"("});
        for (auto &ops: _operators) {
            for (auto &op: ops) {
                _all_operators.push_back(op);
            }
        }
    }

    template <typename T> inline
    PostfixExpressionManager<T>::PostfixExpressionManager(const PostfixExpressionManager<T> &manager) {
        _stack = manager._stack;
        _stack_converter = manager._stack_converter;
        _stack_priority = manager._stack_priority;
        _operators = manager._operators;
        _all_operators = manager._all_operators;
    }

    template <typename T> inline
    PostfixExpressionManager<T>::~PostfixExpressionManager() {}

    // time: O(N)
    // space: O(1)
    template <typename T> inline
    T PostfixExpressionManager<T>::eval(const std::vector<std::string> &expression) {
        _stack.clear();
        for (auto &e: expression) {
            if (!isInVector(_all_operators, e)) {
                _stack.push(T(e));
                continue;
            }
            _stack.push(_stack.pop().exec(e, _stack.pop()));
        }
        return _stack.pop();
    }

    // time: O(N)
    // space: O(2N)
    template <typename T> inline
    std::vector<std::string> PostfixExpressionManager<T>::fromInfixExpression(const std::vector<std::string> &expression) {
        auto result = std::vector<std::string>();
        auto result_stack = data_structures::Stack<std::string>();
        _stack_converter.clear();
        _stack_priority.clear();
        auto max_priority = _operators.size();
        for (auto &e: expression) {
            if (!isInVector(_all_operators, e)) {
                result_stack.push(e);
                continue;
            }
            for (auto priority = max_priority; priority > 0; priority--) {
                if (!isInVector(_operators[priority - 1], e)) {
                    continue;
                }
                while (!_stack_converter.isEmpty()) {
                    if (priority > _stack_priority.top()) {
                        break;
                    }
                    if (_stack_converter.top() == "(" && e == ")") {
                        _stack_priority.pop();
                        _stack_converter.pop();
                        break;
                    }
                    if (_stack_converter.top() == "(") {
                        break;
                    }
                    result_stack.push(_stack_converter.pop());
                    _stack_priority.pop();
                }
                if (e != ")") {
                    _stack_converter.push(e);
                    _stack_priority.push(priority);
                }
            }
        }
        while (!_stack_converter.isEmpty()) {
            result_stack.push(_stack_converter.pop());
        }
        while (!result_stack.isEmpty()) {
            result.insert(result.begin(), result_stack.pop());
        }
        return result;
    }

}

#endif //ALGORITHM_POSTFIX_EXPRESSION_MANAGER_H
