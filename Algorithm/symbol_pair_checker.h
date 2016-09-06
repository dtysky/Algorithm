//
//  symbol_pair_checker
//  Algorithm
//
//  Created by dtysky on 16/9/6.
//  Copyright © 2016 dtysky@outlook.com. All rights reserved.
//

#ifndef ALGORITHM_SYMBOL_PAIR_CHECKER_H
#define ALGORITHM_SYMBOL_PAIR_CHECKER_H

#include <cstdio>
#include <cstring>
#include <vector>
#include "stack.h"


namespace my_algorithm {
    class SymbolPairChecker {

    protected:
        uint32_t _cursor;
        std::string _open_symbols;
        std::string _close_symbols;
        data_structures::Stack<char> _stack;

    public:
        SymbolPairChecker();
        SymbolPairChecker(const SymbolPairChecker& checker);
        SymbolPairChecker(const std::vector<std::string>& symbol_pairs);
        virtual ~SymbolPairChecker();
        void operator=(const SymbolPairChecker& checker);
        void setSymbolPairs(const std::vector<std::string>& symbol_pairs);
        bool check(const std::string& str);
        uint32_t position();
    };

}


#endif //ALGORITHM_SYMBOL_PAIR_CHECKER_H
