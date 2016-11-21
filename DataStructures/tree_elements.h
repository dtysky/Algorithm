//
//  tree_elements
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
    struct BinarySearchTreeElement {
    public:
        Key key;
        Value value;
        BinarySearchTreeElement() {}
        BinarySearchTreeElement(const Key& k, const Value& v) {
            key = k;
            value = v;
        }
        BinarySearchTreeElement(const BinarySearchTreeElement<Key, Value>& element) {
            key = element.key;
            value = element.value;
        }
        BinarySearchTreeElement<Key, Value>& operator=(const BinarySearchTreeElement<Key, Value>& element) {
            key = element.key;
            value = element.value;
            return *this;
        }
        bool operator==(const BinarySearchTreeElement<Key, Value>& element) const {
            return key == element.key;
        }
        bool operator!=(const BinarySearchTreeElement<Key, Value>& element) const {
            return key != element.key;
        }
        bool operator>(const BinarySearchTreeElement<Key, Value>& element) const {
            return key > element.key;
        }
        bool operator<(const BinarySearchTreeElement<Key, Value>& element) const {
            return key < element.key;
        }
        bool operator>=(const BinarySearchTreeElement<Key, Value>& element) const {
            return key >= element.key;
        }
        bool operator<=(const BinarySearchTreeElement<Key, Value>& element) const {
            return key <= element.key;
        }
        friend std::ostream &operator<<(std::ostream &out, const BinarySearchTreeElement<Key, Value> &element) {
            out<< element.key << ":" << element.value;
            return out;
        };
    };
}

#endif //ALGORITHM_TREE_ELEMENTS_H
