//
//  symbol_pair_checker
//  Algorithm
//
//  Created by dtysky on 16/9/6.
//  Copyright © 2016 dtysky@outlook.com. All rights reserved.
//

#include "symbol_pair_checker.h"


namespace my_algorithm {
    SymbolPairChecker::SymbolPairChecker() {
        _cursor = 0;
        _open_symbols = std::string();
        _close_symbols = std::string();
        _stack = data_structures::Stack<char>();
    }

    SymbolPairChecker::SymbolPairChecker(const SymbolPairChecker& checker) {
        _cursor = checker._cursor;
        _open_symbols = checker._open_symbols;
        _close_symbols = checker._close_symbols;
        _stack = checker._stack;
    }

    SymbolPairChecker::SymbolPairChecker(const std::vector<std::string>& symbol_pairs) {
        _cursor = 0;
        _open_symbols = std::string();
        _close_symbols = std::string();
        setSymbolPairs(symbol_pairs);
        _stack = data_structures::Stack<char>();
    }

    SymbolPairChecker::~SymbolPairChecker() {}

    void SymbolPairChecker::operator=(const SymbolPairChecker &checker) {
        _cursor = checker._cursor;
        _open_symbols = checker._open_symbols;
        _close_symbols = checker._close_symbols;
        _stack = data_structures::Stack<char>();
    }

    void SymbolPairChecker::setSymbolPairs(const std::vector<std::string> &symbol_pairs) {
        for (auto pair: symbol_pairs) {
            _open_symbols += pair[0];
            _close_symbols += pair[1];
        }
    }

    // online, O(n)
    bool SymbolPairChecker::check(const std::string &str) {
        _cursor = 0;
        _stack.clear();
        auto size = str.size();
        for (uint32_t i = 0; i < size; i++) {
            _cursor = i;
            auto s = str[i];
            auto _close_position = _close_symbols.find(s);
            auto _open_position = _open_symbols.find(s);
            // normal characters
            if (_close_position == std::string::npos && _open_position == std::string::npos) {
                continue;
            }
            // open symbol is equal close symbol, like '', "" ......
            if (_open_position != std::string::npos && _close_position != std::string::npos) {
                if(_stack.isEmpty()) {
                    _stack.push(s);
                    continue;
                }
                if (s != _close_symbols[_open_symbols.find(_stack.top())]) {
                    _stack.push(s);
                    continue;
                }
            }
            if (_close_position != std::string::npos) {
                if(_stack.isEmpty()) {
                    return false;
                }
                if (s != _close_symbols[_open_symbols.find(_stack.pop())]) {
                    return false;
                }
                continue;
            }
            _stack.push(s);
        }
        return _stack.isEmpty();
    }

    uint32_t SymbolPairChecker::position() {
        return _cursor;
    }
}