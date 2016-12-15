//
//  graph_adj_set
//  Algorithm
//
//  Created by dtysky on 16/12/14.
//  Copyright © 2016 dtysky@outlook.com. All rights reserved.
//

#ifndef ALGORITHM_GRAPH_ADJ_SET_H
#define ALGORITHM_GRAPH_ADJ_SET_H

#include <cstdio>
#include <iostream>
#include <vector>
#include "symbol_table.h"
#include "red_black_tree_node.h"
#include "tree_element.h"


namespace data_structures {
    template <typename T>
    class GraphAdjSet {
        typedef RBTreeNode<TreeElement<T, GraphAdjSet<T>>> Node;
    protected:
        SymbolTable<Node*, T> _table;
    public:
        GraphAdjSet();
        GraphAdjSet(const GraphAdjSet<T> &set);
        virtual ~GraphAdjSet();
        std::vector<T> adjVertex();
        std::vector<T> adjVertexNodes();
        size_t degree();
        bool addEdge(Node *node);
        bool deleteEdge(Node *node);
        bool hasEdge(Node *node);
        GraphAdjSet<T>& operator=(const GraphAdjSet<T> &set);
        bool operator==(const GraphAdjSet<T> &set);
        bool operator!=(const GraphAdjSet<T> &set);
        friend std::ostream &operator<<(std::ostream &out, const GraphAdjSet<T> &set) {
            out << set._table;
            return out;
        }
    };

    template <typename T> inline
    GraphAdjSet<T>::GraphAdjSet(){
        _table = SymbolTable<Node*, bool>();
    }

    template <typename T> inline
    GraphAdjSet<T>::GraphAdjSet(const GraphAdjSet<T>& node){
        _table = node._table;
    }

    template <typename T> inline
    GraphAdjSet<T>::~GraphAdjSet(){}

    template <typename T> inline
    GraphAdjSet<T>& GraphAdjSet<T>::operator=(const GraphAdjSet<T>& node){
        _table = node._table;
        return *this;
    }

    template <typename T> inline
    bool GraphAdjSet<T>::operator==(const GraphAdjSet<T>& node){
        return _table == node._table;
    }

    template <typename T> inline
    bool GraphAdjSet<T>::operator!=(const GraphAdjSet<T>& node){
        return _table != node._table;
    }

    template <typename T> inline
    std::vector<T> GraphAdjSet<T>::adjVertex(){
        return _table.values();
    }

    template <typename T> inline
    std::vector<RBTreeNode<TreeElement<T, GraphAdjSet<T>>>*> GraphAdjSet<T>::adjVertexNodes(){
        return _table.keys();
    }

    template <typename T> inline
    size_t GraphAdjSet<T>::degree(){
        return _table.size();
    }

    template <typename T> inline
    bool GraphAdjSet<T>::addEdge(Node *node){
        auto size = _table.size();
        _table.set(node, node->element.value);
        return size != _table.size();
    }

    template <typename T> inline
    bool GraphAdjSet<T>::deleteEdge(Node *node){
        auto size = _table.size();
        _table.del(node);
        return size != _table.size();
    }

    template <typename T> inline
    bool GraphAdjSet<T>::hasEdge(Node *node){
        return _table.has(node);
    }


}


#endif //ALGORITHM_GRAPH_ADJ_SET_H
