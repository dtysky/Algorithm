//
//  symbol_table
//  Algorithm
//
//  Created by dtysky on 16/11/9.
//  Copyright © 2016 dtysky@outlook.com. All rights reserved.
//

#ifndef ALGORITHM_SYMBOLTABLE_H
#define ALGORITHM_SYMBOLTABLE_H

#include <cstdio>
#include <vector>
#include <iostream>
#include "linked_list.h"


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
    class SymbolTable {
    private:
        LinkedList<SymbolTableElement<Key, Value>> _list;
    public:
        SymbolTable();
        virtual ~SymbolTable();
        SymbolTable(const SymbolTable<Key, Value>& table);
        SymbolTable<Key, Value>& operator=(const SymbolTable<Key, Value>& table);
        bool operator==(const SymbolTable<Key, Value>& table);
        bool operator!=(const SymbolTable<Key, Value>& table);
        bool isEmpty();
        size_t size();
        bool has(const Key& key);
        SymbolTable<Key, Value>& set(const Key& key, const Value& value);
        Value get(const Key& key);
        Value del(const Key& key);
        SymbolTable<Key, Value>& clear();
        std::vector<Key> keys();
        std::vector<SymbolTableElement<Key, Value>> elements();
        friend std::ostream &operator<<(std::ostream &out, const SymbolTable<Key, Value> &table) {
            std::cout << "{" << std::endl;
            std::cout << " " << table._list;
            std::cout << "}" << std::endl;
            return out;
        };
    };

    template <typename Key, typename Value> inline
    SymbolTable<Key, Value>::SymbolTable() {
        _list = LinkedList<SymbolTableElement<Key, Value>>();
    }

    template <typename Key, typename Value> inline
    SymbolTable<Key, Value>::~SymbolTable() {
        _list.clear();
    }

    template <typename Key, typename Value> inline
    SymbolTable<Key, Value>::SymbolTable(const SymbolTable<Key, Value>& table) {
        _list = table._list;
    }

    template <typename Key, typename Value> inline
    SymbolTable<Key, Value>& SymbolTable<Key, Value>::operator=(const SymbolTable<Key, Value> &table){
        _list = table._list;
        return *this;
    }

    template <typename Key, typename Value> inline
    bool SymbolTable<Key, Value>::operator==(const SymbolTable<Key, Value> &table){
        return  _list == table._list;
    }

    template <typename Key, typename Value> inline
    bool SymbolTable<Key, Value>::operator!=(const SymbolTable<Key, Value> &table){
        return  _list != table._list;
    }

    template <typename Key, typename Value> inline
    bool SymbolTable<Key, Value>::isEmpty(){
        return _list.isEmpty();
    }

    template <typename Key, typename Value> inline
    size_t SymbolTable<Key, Value>::size(){
        return _list.size();
    }

    template <typename Key, typename Value> inline
    bool SymbolTable<Key, Value>::has(const Key &key){
        for (auto node = _list.begin(); node != _list.end(); node = node->next()) {
            if (node->element.key == key) {
                return true;
            }
        }
        return false;
    }

    template <typename Key, typename Value> inline
    SymbolTable<Key, Value>& SymbolTable<Key, Value>::set(const Key &key, const Value &value){
        for (auto node = _list.begin(); node != _list.end(); node = node->next()) {
            if (node->element.key == key) {
                node->element.value = value;
                return *this;
            }
        }
        _list.insertToTail(SymbolTableElement<Key, Value>(key, value));
        return *this;
    }

    template <typename Key, typename Value> inline
    Value SymbolTable<Key, Value>::get(const Key &key){
        for (auto node = _list.begin(); node != _list.end(); node = node->next()) {
            if (node->element.key == key) {
                return node->element.value;
            }
        }
        throw std::out_of_range("Key error !");
    }

    template <typename Key, typename Value> inline
    Value SymbolTable<Key, Value>::del(const Key &key){
        auto pre_node = _list.header();
        for (auto node = _list.begin(); node != _list.end(); node = node->next()) {
            if (node->element.key == key) {
                auto result = node->element.value;
                _list.deleteAfterNode(pre_node);
                return result;
            }
            pre_node = node;
        }
        throw std::out_of_range("Key error !");
    }

    template <typename Key, typename Value> inline
    SymbolTable<Key, Value>& SymbolTable<Key, Value>::clear(){
        _list.clear();
        return *this;
    }

    template <typename Key, typename Value> inline
    std::vector<Key> SymbolTable<Key, Value>::keys(){
        auto keys = std::vector<Key>();
        for (auto node = _list.begin(); node != _list.end(); node = node->next()) {
            keys.push_back(node->element.key);
        }
        return keys;
    }

    template <typename Key, typename Value> inline
    std::vector<SymbolTableElement<Key, Value>> SymbolTable<Key, Value>::elements(){
        auto elements = std::vector<SymbolTableElement<Key, Value>>();
        for (auto node = _list.begin(); node != _list.end(); node = node->next()) {
            elements.push_back(node->element);
        }
        return elements;
    }
}


#endif //ALGORITHM_SYMBOLTABLE_H
