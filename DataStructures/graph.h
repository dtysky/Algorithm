//
//  graph
//  Algorithm
//
//  Created by dtysky on 16/12/13.
//  Copyright © 2016 dtysky@outlook.com. All rights reserved.
//

#ifndef ALGORITHM_GRAPH_H
#define ALGORITHM_GRAPH_H

#include <cstdio>
#include <iostream>
#include "red_black_tree.h"
#include "graph_adj_set.h"
#include <vector>


namespace data_structures {
    template <typename T>
    class Graph {
    protected:
        RBTree<T, GraphAdjSet<T>> _tree;
        size_t _edge_count;
    public:
        Graph();
        Graph(const Graph<T> &graph);
        virtual ~Graph();
        size_t vertexCount();
        size_t edgeCount();
        size_t selfLoopsCount();
        std::vector<T> adjVertex(const T& vertex);
        size_t degree(const T& vertex);
        size_t maxDegree();
        size_t avgDegree();
        Graph<T>& addVertex(const T& v);
        Graph<T>& deleteVertex(const T& v);
        bool hasVertex(const T& v);
        Graph<T>& addEdge(const T& v, const T& w);
        Graph<T>& deleteEdge(const T& v, const T& w);
        bool hasEdge(const T& v, const T& w);
        Graph<T>& operator=(const Graph<T> &graph);
        bool operator==(const Graph<T> &graph);
        bool operator!=(const Graph<T> &graph);
        friend std::ostream &operator<<(std::ostream &out, const Graph<T> &graph) {
            return out;
        }
    };


    template <typename T> inline
    Graph<T>::Graph() {
        _tree = RBTree<T, GraphAdjSet<T>>();
    }

    // todo: waiting for completing, keys in GraphAdjSet are pointers, we can't copy them by default method
    template <typename T> inline
    Graph<T>::Graph(const Graph<T> &graph) {}

    template <typename T> inline
    Graph<T>::~Graph() {}

    // todo: waiting for completing, keys in GraphAdjSet are pointers, we can't copy them by default method
    template <typename T> inline
    Graph<T>& Graph<T>::operator=(const Graph<T> &graph) {
        return *this;
    }

    // todo: waiting for completing, keys in GraphAdjSet are pointers, we can't compare them by default method
    template <typename T> inline
    bool Graph<T>::operator==(const Graph<T> &graph) {
        return false;
    }

    template <typename T> inline
    bool Graph<T>::operator!=(const Graph<T> &graph) {
        return !(*this == graph);
    }

    template <typename T> inline
    size_t Graph<T>::vertexCount(){
        return _tree.size();
    }

    template <typename T> inline
    size_t Graph<T>::edgeCount(){
        return _edge_count;
    }

    template <typename T> inline
    size_t Graph<T>::selfLoopsCount(){
        auto nodes = _tree.getAllNodes();
        size_t count = 0;
        for (auto node: nodes) {
            count += node->element.value.has(node) ? 1 : 0;
        }
        return count;
    }

    template <typename T> inline
    std::vector<T> Graph<T>::adjVertex(const T& vertex){
        return _tree.get(vertex).adjVertex();
    }

    template <typename T> inline
    size_t Graph<T>::degree(const T &vertex){
        return _tree.get(vertex).degree();
    }

    template <typename T> inline
    size_t Graph<T>::maxDegree(){
        auto nodes = _tree.getAllNodes();
        size_t d = 0;
        for (auto node: nodes) {
            auto &d2 = node->element.value.degree();
            d = d2 > d ? d2 : d;
        }
        return d;
    }

    template <typename T> inline
    size_t Graph<T>::avgDegree(){
        return vertexCount() / edgeCount();
    }

    template <typename T> inline
    Graph<T>& Graph<T>::addVertex(const T &vertex){
        _tree.add(vertex);
        return *this;
    }

    template <typename T> inline
    Graph<T>& Graph<T>::deleteVertex(const T &vertex){
        auto v = _tree.get(vertex);
        auto nodes = v.adjVertexNodes();
        for (auto node: nodes) {
            node->element.value.deleteEdge(v);
            _edge_count--;
        }
        _tree.del(vertex);
        return *this;
    }

    template <typename T> inline
    bool Graph<T>::hasVertex(const T &v){
        auto nodes = v.adjVertexNodes();
        for (auto node: nodes) {
            if (node->element.key == v) {
                return true;
            }
        }
        return false;
    }

    template <typename T> inline
    Graph<T>& Graph<T>::addEdge(const T &v, const T &w){
        auto vp = _tree.getNode(v);
        auto wp = _tree.getNode(w);
        if (vp->element.value.addEdge(wp)) {
            _edge_count++;
        }
        wp->element.value.addEdge(vp);
        return *this;
    }

    template <typename T> inline
    Graph<T>& Graph<T>::deleteEdge(const T &v, const T &w){
        auto vp = _tree.getNode(v);
        auto wp = _tree.getNode(w);
        if (vp->element.value.deleteEdge(wp)) {
            _edge_count--;
        }
        wp->element.value.deleteEdge(vp);
        return *this;
    }

    template <typename T> inline
    bool Graph<T>::hasEdge(const T &v, const T &w){
        auto vp = _tree.getNode(v);
        auto wp = _tree.getNode(w);
        return vp->element.value.hasEdge(wp);
    }
}

#endif //ALGORITHM_GRAPH_H
