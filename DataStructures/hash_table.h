//
//  hash_table
//  Algorithm
//
//  Created by dtysky on 16/12/12.
//  Copyright © 2016 dtysky@outlook.com. All rights reserved.
//

#ifndef ALGORITHM_HASH_TABLE_H
#define ALGORITHM_HASH_TABLE_H

#include <cstdio>
#include <iostream>
#include <array>
#include <vector>
#include <functional>
#include "symbol_table.h"
#include "symbol_table_elements.h"
#include "linked_list.h"


namespace data_structures {
    template <typename Key, typename Value, size_t Radix>
    class HashTable {
    protected:
        std::array<SymbolTable<Key, Value>, Radix> _array;
        size_t _size;
        std::hash<Key> _calculator;
    public:
        HashTable();
        virtual ~HashTable();
        HashTable(const HashTable<Key, Value, Radix> &table);
        HashTable<Key, Value, Radix>& operator=(const HashTable<Key, Value, Radix> &table);
        bool operator==(const HashTable<Key, Value, Radix>& table);
        bool operator!=(const HashTable<Key, Value, Radix>& table);
        bool isEmpty();
        size_t size();
        HashTable<Key, Value, Radix>& clear();
        HashTable<Key, Value, Radix>& set(const Key& key, const Value& value);
        Value get(const Key& key);
        Value del(const Key& key);
        std::vector<Key> keys();
        std::vector<SymbolTableElement<Key, Value>> elements();
        friend std::ostream &operator<<(std::ostream& out, HashTable<Key, Value, Radix>& table) {
            out << "{" << std::endl;
            auto elements = table.elements();
            for (auto &e: elements) {
                out << "  " << e.key << ": " << e.value << std::endl;
            }
            out << "}" << std::endl;
            return out;
        };
    };

    template <typename Key, typename Value, size_t Radix> inline
    HashTable<Key, Value, Radix>::HashTable() {
        _array = std::array<SymbolTable<Key, Value>, Radix>();
        _size = 0;
    }

    template <typename Key, typename Value, size_t Radix> inline
    HashTable<Key, Value, Radix>::~HashTable() {}

    template <typename Key, typename Value, size_t Radix> inline
    HashTable<Key, Value, Radix>::HashTable(const HashTable<Key, Value, Radix> &table){
        _array = table._array;
        _size = table._size;
    }

    template <typename Key, typename Value, size_t Radix> inline
    HashTable<Key, Value, Radix>& HashTable<Key, Value, Radix>::operator=(const HashTable<Key, Value, Radix> &table){
        _array = table._array;
        _size = table._size;
    }

    template <typename Key, typename Value, size_t Radix> inline
    bool HashTable<Key, Value, Radix>::operator==(const HashTable<Key, Value, Radix> &table){
        for (size_t i = 0; i < Radix; i++) {
            if (_array[i] != table._array[i]) {
                return false;
            }
        }
        return true;
    }

    template <typename Key, typename Value, size_t Radix> inline
    bool HashTable<Key, Value, Radix>::operator!=(const HashTable<Key, Value, Radix> &table){
        for (size_t i = 0; i < Radix; i++) {
            if (_array[i] != table._array[i]) {
                return true;
            }
        }
        return false;
    }

    template <typename Key, typename Value, size_t Radix> inline
    bool HashTable<Key, Value, Radix>::isEmpty(){
        return _size == 0;
    }

    template <typename Key, typename Value, size_t Radix> inline
    size_t HashTable<Key, Value, Radix>::size(){
        return _size;
    }

    template <typename Key, typename Value, size_t Radix> inline
    HashTable<Key, Value, Radix>& HashTable<Key, Value, Radix>::clear(){
        if (isEmpty()) {
            return *this;
        }
        for (auto &table : _array) {
            table.clear();
        }
    }

    template <typename Key, typename Value, size_t Radix> inline
    HashTable<Key, Value, Radix>& HashTable<Key, Value, Radix>::set(const Key &key, const Value &value){
        auto hash = _calculator(key) % Radix;
        auto size = _array[hash].size();
        if (_array[hash].set(key, value).size() != size) {
            _size++;
        }
        return *this;
    }

    template <typename Key, typename Value, size_t Radix> inline
    Value HashTable<Key, Value, Radix>::get(const Key &key){
        auto hash = _calculator(key) % Radix;
        return _array[hash].get(key);
    }

    template <typename Key, typename Value, size_t Radix> inline
    Value HashTable<Key, Value, Radix>::del(const Key &key){
        auto hash = _calculator(key) % Radix;
        auto size = _array[hash].size();
        auto result = _array[hash].del(key);
        if (_array[hash].size() != size) {
            _size--;
        }
        return result;
    }

    template <typename Key, typename Value, size_t Radix> inline
    std::vector<Key> HashTable<Key, Value, Radix>::keys(){
        auto keys = std::vector<Key>();
        for (auto &table: _array) {
            auto keys2 = table.keys();
            keys.insert(keys.end(), keys2.begin(), keys2.end());
        }
        return keys;
    }

    template <typename Key, typename Value, size_t Radix> inline
    std::vector<SymbolTableElement<Key, Value>> HashTable<Key, Value, Radix>::elements(){
        auto elements = std::vector<SymbolTableElement<Key, Value>>();
        for (auto &table: _array) {
            auto elements2 = table.elements();
            elements.insert(elements.end(), elements2.begin(), elements2.end());
        }
        return elements;
    }
}


#endif //ALGORITHM_HASH_TABLE_H
