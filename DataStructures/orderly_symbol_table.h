//
//  orderly_symbol_table
//  Algorithm
//
//  Created by dtysky on 16/11/9.
//  Copyright © 2016 dtysky@outlook.com. All rights reserved.
//

#ifndef ALGORITHM_ORDERLY_SYMBOL_TABLE_H
#define ALGORITHM_ORDERLY_SYMBOL_TABLE_H

#include <cstdio>
#include <vector>
#include <iostream>
#include "priority_queue.h"
#include "symbol_table_elements.h"


namespace data_structures {
    template <typename Key, typename Value>
    class OrderlySymbolTable {
    protected:
        PriorityQueue<OrderlySymbolTableElement<Key, Value>> _queue;
    public:
        OrderlySymbolTable();
        virtual ~OrderlySymbolTable();
        OrderlySymbolTable(const OrderlySymbolTable<Key, Value>& table);
        OrderlySymbolTable<Key, Value>& operator=(const OrderlySymbolTable<Key, Value>& table);
        bool operator==(const OrderlySymbolTable<Key, Value>& table);
        bool operator!=(const OrderlySymbolTable<Key, Value>& table);
        bool isEmpty();
        size_t size();
        bool has(const Key& key);
        OrderlySymbolTable<Key, Value>& set(const Key& key, const Value& value);
        Value get(const Key& key);
        Value del(const Key& key);
        OrderlySymbolTable<Key, Value>& clear();
        std::vector<Key> keys();
        std::vector<OrderlySymbolTableElement<Key, Value>> elements();
        Key maxNKey(const size_t n);
        Key minNKey(const size_t n);
        Value deleteMaxNKey(const size_t n);
        Value deleteMinNKey(const size_t n);
        size_t rankKey(const Key& key);
        size_t sizeBetweenKeys(const Key& key1, const Key& key2);
        friend std::ostream &operator<<(std::ostream &out, const OrderlySymbolTable<Key, Value> &table) {
            std::cout << "{" << std::endl;
            for (auto node = table._queue.begin(); node != table._queue.end(); node = node->next()) {
                std::cout << "  " << node->element;
            }
            std::cout << "}" << std::endl;
            return out;
        };
    };


    template <typename Key, typename Value> inline
    OrderlySymbolTable<Key, Value>::OrderlySymbolTable() {
        _queue = PriorityQueue<OrderlySymbolTableElement<Key, Value>>();
    }

    template <typename Key, typename Value> inline
    OrderlySymbolTable<Key, Value>::~OrderlySymbolTable() {
        _queue.clear();
    }

    template <typename Key, typename Value> inline
    OrderlySymbolTable<Key, Value>::OrderlySymbolTable(const OrderlySymbolTable<Key, Value>& table) {
        _queue = table._queue;
    }

    template <typename Key, typename Value> inline
    OrderlySymbolTable<Key, Value>& OrderlySymbolTable<Key, Value>::operator=(const OrderlySymbolTable<Key, Value> &table){
        _queue = table._queue;
        return *this;
    }

    template <typename Key, typename Value> inline
    bool OrderlySymbolTable<Key, Value>::operator==(const OrderlySymbolTable<Key, Value> &table){
        return  _queue == table._queue;
    }

    template <typename Key, typename Value> inline
    bool OrderlySymbolTable<Key, Value>::operator!=(const OrderlySymbolTable<Key, Value> &table){
        return  _queue != table._queue;
    }

    template <typename Key, typename Value> inline
    bool OrderlySymbolTable<Key, Value>::isEmpty(){
        return _queue.isEmpty();
    }

    template <typename Key, typename Value> inline
    size_t OrderlySymbolTable<Key, Value>::size(){
        return _queue.size();
    }

    template <typename Key, typename Value> inline
    bool OrderlySymbolTable<Key, Value>::has(const Key &key){
        for (auto node = _queue.begin(); node != _queue.end(); node = node->next()) {
            if (node->element.key == key) {
                return true;
            }
        }
        return false;
    }

    template <typename Key, typename Value> inline
    OrderlySymbolTable<Key, Value>& OrderlySymbolTable<Key, Value>::set(const Key &key, const Value &value){
        for (auto node = _queue.begin(); node != _queue.end(); node = node->next()) {
            if (node->element.key == key) {
                node->element.value = value;
                return *this;
            }
        }
        _queue.enqueue(OrderlySymbolTableElement<Key, Value>(key, value));
        return *this;
    }

    template <typename Key, typename Value> inline
    Value OrderlySymbolTable<Key, Value>::get(const Key &key){
        for (auto node = _queue.begin(); node != _queue.end(); node = node->next()) {
            if (node->element.key == key) {
                return node->element.value;
            }
        }
        throw std::out_of_range("Key error, no such key in this table !");
    }

    template <typename Key, typename Value> inline
    Value OrderlySymbolTable<Key, Value>::del(const Key &key){
        auto pre_node = _queue.header();
        for (auto node = _queue.begin(); node != _queue.end(); node = node->next()) {
            if (node->element.key == key) {
                auto result = node->element.value;
                pre_node->deleteAfter();
                return result;
            }
            pre_node = node;
        }
        throw std::out_of_range("Key error, no such key in this table !");
    }

    template <typename Key, typename Value> inline
    OrderlySymbolTable<Key, Value>& OrderlySymbolTable<Key, Value>::clear(){
        _queue.clear();
        return *this;
    }

    template <typename Key, typename Value> inline
    std::vector<Key> OrderlySymbolTable<Key, Value>::keys(){
        auto keys = std::vector<Key>();
        for (auto node = _queue.begin(); node != _queue.end(); node = node->next()) {
            keys.push_back(node->element.key);
        }
        return keys;
    }

    template <typename Key, typename Value> inline
    std::vector<OrderlySymbolTableElement<Key, Value>> OrderlySymbolTable<Key, Value>::elements(){
        auto elements = std::vector<OrderlySymbolTableElement<Key, Value>>();
        for (auto node = _queue.begin(); node != _queue.end(); node = node->next()) {
            elements.push_back(node->element);
        }
        return elements;
    }

    template <typename Key, typename Value> inline
    Key OrderlySymbolTable<Key, Value>::maxNKey(const size_t n){
        return _queue.maxN(n).key;
    }

    template <typename Key, typename Value> inline
    Key OrderlySymbolTable<Key, Value>::minNKey(const size_t n){
        return _queue.minN(n).key;
    }

    template <typename Key, typename Value> inline
    Value OrderlySymbolTable<Key, Value>::deleteMaxNKey(const size_t n){
        return _queue.dequeueMaxN(n).value;
    }

    template <typename Key, typename Value> inline
    Value OrderlySymbolTable<Key, Value>::deleteMinNKey(const size_t n){
        return _queue.dequeueMinN(n).value;
    }

    template <typename Key, typename Value> inline
    size_t OrderlySymbolTable<Key, Value>::rankKey(const Key &key){
        size_t i = 1;
        for (auto node = _queue.begin(); node != _queue.end(); node = node->next()) {
            if (node->element.key == key) {
                return i;
            }
            i++;
        }
        throw std::out_of_range("Key error, no such key in this table !");
    }

    template <typename Key, typename Value> inline
    size_t OrderlySymbolTable<Key, Value>::sizeBetweenKeys(const Key &key1, const Key &key2){
        return rankKey(key2) - rankKey(key1);
    }

}


#endif //ALGORITHM_ORDERLY_SYMBOL_TABLE_H
