//
//  orderly_symbol_table
//  Algorithm
//
//  Created by dtysky on 16/8/24.
//  Copyright © 2016年 dtysky@outlook.com. All rights reserved.
//

#include <string>
#include <iostream>
#include "orderly_symbol_table.h"


namespace data_structures {
    using std::cout;
    using std::endl;
    void testOrderlySymbolTable(){
        auto table = OrderlySymbolTable<std::string, uint32_t>();
        cout << table.isEmpty() << endl;
        table.set("a", 0)
            .set("b", 1)
            .set("c", 2)
            .set("d", 3)
            .set("e", 4)
            .set("f", 5)
            .set("aa", 12)
            .set("bb", 32)
            .set("cc", 2231)
            .set("dd", 4233)
            .set("ee", 444);
        cout << table << endl;
        cout << table.size() << endl;
        cout << table.get("a") << endl;
        table.set("a", 334);
        cout << table.get("a") << endl;
        auto table1 = table;
        cout << table << endl;
        cout << (table == table1) << endl;
        for (auto element: table.elements()) {
            cout << element << " ";
        }
        cout << endl;
        for (auto key: table.keys()) {
            cout << key << ": " << table.del(key) << endl;
            cout << table << endl;
        }
        cout << table.isEmpty() << endl;
        cout << table1.rankKey("aa") << endl;
        cout << table1.sizeBetweenKeys("aa", "ee") << endl;
        cout << table1.maxNKey(1) << endl;
        cout << table1.minNKey(1) << endl;
        cout << table1.deleteMaxNKey(1) << endl;
        cout << table1.deleteMinNKey(1) << endl;
        table1.clear();
        cout << table1 << endl;
        cout << table.get("aaa") << endl;
    }

}