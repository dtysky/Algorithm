//
//  symbol_table_elements
//  Algorithm
//
//  Created by dtysky on 16/11/14.
//  Copyright © 2016 dtysky@outlook.com. All rights reserved.
//

#ifndef ALGORITHM_SYMBOL_TABLE_ELEMENTS_H
#define ALGORITHM_SYMBOL_TABLE_ELEMENTS_H

#include <cstdio>
#include <iostream>


namespace data_structures {
    template <typename Key, typename Value>
    struct SymbolTableElement {
    public:
        Key key;
        Value value;
        SymbolTableElement() {}
        virtual ~SymbolTableElement() {}
        SymbolTableElement(const Key& k, const Value& v) {
            key = k;
            value = v;
        }
        SymbolTableElement(const SymbolTableElement<Key, Value>& element) {
            key = element.key;
            value = element.value;
        }
        SymbolTableElement<Key, Value>& operator=(const SymbolTableElement<Key, Value>& element) {
            key = element.key;
            value = element.value;
            return *this;
        }
        friend std::ostream &operator<<(std::ostream &out, const SymbolTableElement<Key, Value> &element) {
            std::cout << element.key << ": " << element.value << std::endl;
            return out;
        };
    };


    template <typename Key, typename Value>
    struct OrderlySymbolTableElement {
    public:
        Key key;
        Value value;
        OrderlySymbolTableElement() {}
        OrderlySymbolTableElement(const Key& k, const Value& v) {
            key = k;
            value = v;
        }
        OrderlySymbolTableElement(const OrderlySymbolTableElement<Key, Value>& element) {
            key = element.key;
            value = element.value;
        }
        OrderlySymbolTableElement<Key, Value>& operator=(const OrderlySymbolTableElement<Key, Value>& element) {
            key = element.key;
            value = element.value;
            return *this;
        }
        bool operator==(const OrderlySymbolTableElement<Key, Value>& element) const {
            return key == element.key;
        }
        bool operator!=(const OrderlySymbolTableElement<Key, Value>& element) const {
            return key != element.key;
        }
        bool operator>(const OrderlySymbolTableElement<Key, Value>& element) const {
            return key > element.key;
        }
        bool operator<(const OrderlySymbolTableElement<Key, Value>& element) const {
            return key < element.key;
        }
        bool operator>=(const OrderlySymbolTableElement<Key, Value>& element) const {
            return key >= element.key;
        }
        bool operator<=(const OrderlySymbolTableElement<Key, Value>& element) const {
            return key <= element.key;
        }
        friend std::ostream &operator<<(std::ostream &out, const OrderlySymbolTableElement<Key, Value> &element) {
            std::cout << element.key << ": " << element.value << std::endl;
            return out;
        };
    };
}


#endif //ALGORITHM_SYMBOL_TABLE_ELEMENTS_H
