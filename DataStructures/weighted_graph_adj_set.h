//
//  graph_weighted_adj_set
//  Algorithm
//
//  Created by dtysky on 2017/2/25.
//  Copyright © 2017 dtysky@outlook.com. All rights reserved.
//

#ifndef ALGORITHM_WEIGHTED_GRAPH_ADJ_SET_H
#define ALGORITHM_WEIGHTED_GRAPH_ADJ_SET_H

#include <cstdio>
#include <iostream>
#include <vector>
#include "symbol_table.h"
#include "red_black_tree_node.h"
#include "tree_element.h"


namespace data_structures {
    template <typename Node, typename Weight>
    class WeightedGraphEdge {
    public:
        Node* from;
        Node* to;
        Weight weight;
        WeightedGraphEdge() {
            from = nullptr;
            to = nullptr;
            weight = 0;
        }
        WeightedGraphEdge(Node *from, Node *to, Weight weight) {
            this->from = from;
            this->to = to;
            this->weight = weight;
        }
        WeightedGraphEdge(const WeightedGraphEdge<Node, Weight>& edge) {
            from = edge.from;
            to = edge.to;
            weight = edge.weight;
        }
        WeightedGraphEdge<Node, Weight>& operator=(const WeightedGraphEdge<Node, Weight> &edge) {
            from = edge.from;
            to = edge.to;
            weight = edge.weight;
            return *this;
        }
        bool operator==(const WeightedGraphEdge<Node, Weight> &edge) {
            return from == edge.from && to == edge.to && weight == edge.weight;
        }
        bool operator!=(const WeightedGraphEdge<Node, Weight> &edge) {
            return !(*this == edge);
        }
        bool operator>(const WeightedGraphEdge<Node, Weight> &edge) const {
            return weight > edge.weight;
        }
        bool operator<(const WeightedGraphEdge<Node, Weight> &edge) const {
            return weight < edge.weight;
        }
        bool operator>=(const WeightedGraphEdge<Node, Weight> &edge) const {
            return weight >= edge.weight;
        }
        bool operator<=(const WeightedGraphEdge<Node, Weight> &edge) const {
            return weight <= edge.weight;
        }
        friend std::ostream &operator<<(std::ostream &out, WeightedGraphEdge<Node, Weight> &edge) {
            out << edge.from->element.key << " <-> " << edge.to->element.key << ": " << edge.weight;
            return out;
        }
    };

    template <typename T, typename Weight>
    class WeightedGraphAdjSet {
        typedef RBTreeNode<TreeElement<T, WeightedGraphAdjSet<T, Weight>>> Node;
        typedef WeightedGraphEdge<Node, Weight> Edge;
    protected:
        SymbolTable<Node*, Edge> _table;
        Node* _vertex;
    public:
        WeightedGraphAdjSet();
        WeightedGraphAdjSet(Node* v);
        WeightedGraphAdjSet(const WeightedGraphAdjSet<T, Weight> &set);
        virtual ~WeightedGraphAdjSet();
        std::vector<Edge> adjEdges();
        std::vector<T> adjVertex();
        std::vector<Node*> adjVertexNodes();
        size_t degree();
        bool addEdge(Node *node, Weight weight);
        bool deleteEdge(Node *node);
        bool hasEdge(Node *node);
        WeightedGraphAdjSet<T, Weight>& operator=(const WeightedGraphAdjSet<T, Weight> &set);
        bool operator==(WeightedGraphAdjSet<T, Weight> &set);
        bool operator!=(WeightedGraphAdjSet<T, Weight> &set);
        friend std::ostream &operator<<(std::ostream &out, WeightedGraphAdjSet<T, Weight> &set) {
            out << set._vertex->element.key << ": ";
            for (auto &e: set.adjEdges()) {
                out << e.to->element.key << "(" << e.weight << ")" << " ";
            }
            return out;
        }
    };

    template <typename T, typename Weight> inline
    WeightedGraphAdjSet<T, Weight>::WeightedGraphAdjSet(){
        _table = SymbolTable<Node*, Edge>();
    }

    template <typename T, typename Weight> inline
    WeightedGraphAdjSet<T, Weight>::WeightedGraphAdjSet(Node* v){
        _vertex = v;
        _table = SymbolTable<Node*, Edge>();
    }

    template <typename T, typename Weight> inline
    WeightedGraphAdjSet<T, Weight>::WeightedGraphAdjSet(const WeightedGraphAdjSet<T, Weight>& set){
        _vertex = set._vertex;
        _table = set._table;
    }

    template <typename T, typename Weight> inline
    WeightedGraphAdjSet<T, Weight>::~WeightedGraphAdjSet(){}

    template <typename T, typename Weight> inline
    WeightedGraphAdjSet<T, Weight>& WeightedGraphAdjSet<T, Weight>::operator=(const WeightedGraphAdjSet<T, Weight>& set){
        _vertex = set._vertex;
        _table = set._table;
        return *this;
    }

    template <typename T, typename Weight> inline
    bool WeightedGraphAdjSet<T, Weight>::operator==(WeightedGraphAdjSet<T, Weight>& set){
        auto size = _table.size();
        if (size != set._table.size()) {
            return false;
        }
        auto values1 = _table.values();
        auto values2 = set._table.values();
        for (size_t i = 0; i < size; i++) {
            if (values1[i] != values2[i]) {
                return false;
            }
        }
        return true;
    }

    template <typename T, typename Weight> inline
    bool WeightedGraphAdjSet<T, Weight>::operator!=(WeightedGraphAdjSet<T, Weight>& set){
        return !(*this == set);
    }

    template <typename T, typename Weight> inline
    std::vector<WeightedGraphEdge<RBTreeNode<TreeElement<T, WeightedGraphAdjSet<T, Weight>>>, Weight>> WeightedGraphAdjSet<T, Weight>::adjEdges(){
        return _table.values();
    }

    template <typename T, typename Weight> inline
    std::vector<T> WeightedGraphAdjSet<T, Weight>::adjVertex(){
        std::vector<T> result;
        auto edges = _table.values();
        for (auto &e: edges) {
            result.push_back(e.to->element.key);
        }
        return result;
    }

    template <typename T, typename Weight> inline
    std::vector<RBTreeNode<TreeElement<T, WeightedGraphAdjSet<T, Weight>>>*> WeightedGraphAdjSet<T, Weight>::adjVertexNodes(){
        return _table.keys();
    }

    template <typename T, typename Weight> inline
    size_t WeightedGraphAdjSet<T, Weight>::degree(){
        return _table.size();
    }

    template <typename T, typename Weight> inline
    bool WeightedGraphAdjSet<T, Weight>::addEdge(Node *node, Weight weight){
        auto size = _table.size();
        _table.set(node, Edge(_vertex, node, weight));
        return size != _table.size();
    }

    template <typename T, typename Weight> inline
    bool WeightedGraphAdjSet<T, Weight>::deleteEdge(Node *node){
        auto size = _table.size();
        _table.del(node);
        return size != _table.size();
    }

    template <typename T, typename Weight> inline
    bool WeightedGraphAdjSet<T, Weight>::hasEdge(Node *node){
        return _table.has(node);
    }
}


#endif //ALGORITHM_WEIGHTED_GRAPH_ADJ_SET_H
