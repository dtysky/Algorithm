//
//  tree_element
//  Algorithm
//
//  Created by dtysky on 16/11/19.
//  Copyright © 2016 dtysky@outlook.com. All rights reserved.
//

#ifndef ALGORITHM_TREE_ELEMENTS_H
#define ALGORITHM_TREE_ELEMENTS_H

#include <cstdio>
#include <iostream>


namespace data_structures {
    template <typename Key, typename Value>
    struct TreeElement {
    public:
        Key key;
        Value value;
        TreeElement() {}
        TreeElement(const Key& k, const Value& v) {
            key = k;
            value = v;
        }
        TreeElement(const TreeElement<Key, Value>& element) {
            key = element.key;
            value = element.value;
        }
        TreeElement<Key, Value>& operator=(const TreeElement<Key, Value>& element) {
            key = element.key;
            value = element.value;
            return *this;
        }
        bool operator==(const TreeElement<Key, Value>& element) const {
            return key == element.key;
        }
        bool operator!=(const TreeElement<Key, Value>& element) const {
            return key != element.key;
        }
        bool operator>(const TreeElement<Key, Value>& element) const {
            return key > element.key;
        }
        bool operator<(const TreeElement<Key, Value>& element) const {
            return key < element.key;
        }
        bool operator>=(const TreeElement<Key, Value>& element) const {
            return key >= element.key;
        }
        bool operator<=(const TreeElement<Key, Value>& element) const {
            return key <= element.key;
        }
        friend std::ostream &operator<<(std::ostream &out, const TreeElement<Key, Value> &element) {
            out<< element.key << ":" << element.value;
            return out;
        };
    };
}

#endif //ALGORITHM_TREE_ELEMENTS_H
