//
//  symbol_pair_checker
//  Algorithm
//
//  Created by dtysky on 16/9/6.
//  Copyright © 2016 dtysky@outlook.com. All rights reserved.
//

#ifndef ALGORITHM_SYMBOL_PAIR_CHECKER_TEST_H
#define ALGORITHM_SYMBOL_PAIR_CHECKER_TEST_H

#include <cstdio>
#include <iostream>
#include "symbol_pair_checker.h"


namespace my_algorithm {

    void checkWithPrint(SymbolPairChecker& checker, const std::string& str) {
        auto result = checker.check(str);
        auto position = checker.position();
        std::cout << result << " " << position << " " << str[position] << std::endl;
    }

    void testSymbolPairChecker() {

        auto checker = SymbolPairChecker(
            std::vector<std::string>{
                "{}",
                "[]",
                "()",
                "<>",
                "''",
                "\"\""
            }
        );

        checkWithPrint(checker, "hello world");
        checkWithPrint(checker, "{}[]()<>''\"\"");
        checkWithPrint(checker, "template<typename T> void fun(int i[]) {print \"'hello world'\";}");
        checkWithPrint(checker, "{[hello}world");
        checkWithPrint(checker, "hello]world{}");
    }
}

#endif //ALGORITHM_SYMBOL_PAIR_CHECKER_TEST_H
