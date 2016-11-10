//
//  OrderlySymbolTable
//  Algorithm
//
//  Created by dtysky on 16/11/9.
//  Copyright © 2016 dtysky@outlook.com. All rights reserved.
//

#ifndef ALGORITHM_SYMBOLTABLE_H
#define ALGORITHM_SYMBOLTABLE_H

#include <cstdio>



namespace data_structure {
    template <typename Key, typename Value>
    struct OrderlySymbolTableElement {
    public:
        Key key;
        Value value;
        OrderlySymbolTableElement() {}
        OrderlySymbolTableElement(const OrderlySymbolTableElement<Key, Value>& element) {
            key = element.key;
            value = element.value;
        }
        OrderlySymbolTableElement<Key, Value>& operator=(const OrderlySymbolTableElement<Key, Value>& element) {
            key = element.key;
            value = element.value;
            return *this;
        }
        bool operator==(const OrderlySymbolTableElement<Key, Value>& element) {
            return key == element.key;
        }
        bool operator!=(const OrderlySymbolTableElement<Key, Value>& element) {
            return key != element.key;
        }
        bool operator>(const OrderlySymbolTableElement<Key, Value>& element) {
            return key > element.key;
        }
        bool operator<(const OrderlySymbolTableElement<Key, Value>& element) {
            return key < element.key;
        }
        bool operator>=(const OrderlySymbolTableElement<Key, Value>& element) {
            return key >= element.key;
        }
        bool operator<=(const OrderlySymbolTableElement<Key, Value>& element) {
            return key <= element.key;
        }
    };

    template <typename Key, typename Value>
    class SymbolTable {
    private:

    };
}


#endif //ALGORITHM_SYMBOLTABLE_H
