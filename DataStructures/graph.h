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
#include <algorithm>


namespace data_structures {
    template <typename T>
    class Graph {
        typedef RBTreeNode<TreeElement<T, GraphAdjSet<T>>> Node;
    protected:
        RBTree<T, GraphAdjSet<T>> _tree;
        size_t _edge_count;
        void _copy(Graph<T> &graph);
        bool _equal(Graph<T> &graph);
    public:
        Graph();
        Graph(Graph<T> &graph);
        virtual ~Graph();
        bool isEmpty();
        size_t vertexCount();
        size_t edgeCount();
        size_t selfLoopsCount();
        RBTreeNode<TreeElement<T, GraphAdjSet<T>>>* getNode(const T& vertex);
        std::vector<T> adjVertex(const T& vertex);
        std::vector<Node*> adjVertexNodes(const T& vertex);
        std::vector<Node*> getAllNodes();
        size_t degree(const T& vertex);
        size_t maxDegree();
        size_t avgDegree();
        Graph<T>& addVertex(const T& v);
        Graph<T>& deleteVertex(const T& v);
        bool hasVertex(const T& v);
        Graph<T>& addEdge(const T& v, const T& w);
        Graph<T>& deleteEdge(const T& v, const T& w);
        bool hasEdge(const T& v, const T& w);
        Graph<T>& operator=(Graph<T> &graph);
        bool operator==(Graph<T> &graph);
        bool operator!=(Graph<T> &graph);
        friend std::ostream &operator<<(std::ostream &out, Graph<T> &graph) {
            auto nodes = graph._tree.getAllNodes();
            for (auto node: nodes) {
                out << node->element.key << ": ";
                for (auto &v: node->element.value.adjVertex()) {
                    out << v << " ";
                }
                out << std::endl;
            }
            return out;
        }
    };


    template <typename T> inline
    Graph<T>::Graph() {
        _tree = RBTree<T, GraphAdjSet<T>>();
        _edge_count = 0;
    }

    template <typename T> inline
    Graph<T>::Graph(Graph<T> &graph) {
        _copy(graph);
    }

    template <typename T> inline
    Graph<T>::~Graph() {}

    // keys in GraphAdjSet are pointers, we can't copy them by default method
    template <typename T> inline
    void Graph<T>::_copy(Graph<T> &graph){
        _tree = RBTree<T, GraphAdjSet<T>>();
        auto nodes = graph._tree.getAllNodes();
        for (auto node: nodes) {
            _tree.add(node->element.key);
        }
        for (auto node: nodes) {
            auto new_node = _tree.getNode(node->element.key);
            auto adj_vertex = node->element.value.adjVertex();
            for (auto v: adj_vertex) {
                new_node->element.value.addEdge(_tree.getNode(v));
            }
        }
    }

    // keys in GraphAdjSet are pointers, we can't copy them by default method
    template <typename T> inline
    bool Graph<T>::_equal(Graph<T> &graph){
        auto nodes1 = _tree.getAllNodes();
        std::sort(nodes1.begin(), nodes1.end(), [](Node* n1, Node* n2) {
            return n1->element.key < n2->element.key;
        });
        auto nodes2 = graph._tree.getAllNodes();
        std::sort(nodes2.begin(), nodes2.end(), [](Node* n1, Node* n2) {
            return n1->element.key < n2->element.key;
        });
        auto size = nodes1.size();
        if (size != nodes2.size()) {
            return false;
        }
        for (size_t i = 0; i < size; i++) {
            auto node1 = nodes1[i];
            auto node2 = nodes2[i];
            if (
                node1->element.key != node2->element.key ||
                node1->element.value != node2->element.value
                ) {
                return false;
            }
        }
        return true;
    }

    template <typename T> inline
    Graph<T>& Graph<T>::operator=(Graph<T> &graph) {
        _copy(graph);
        return *this;
    }

    template <typename T> inline
    bool Graph<T>::operator==(Graph<T> &graph) {
        return _equal(graph);
    }

    template <typename T> inline
    bool Graph<T>::operator!=(Graph<T> &graph) {
        return !(_equal(graph));
    }

    template <typename T> inline
    bool Graph<T>::isEmpty() {
        return vertexCount() == 0;
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
            count += node->element.value.hasEdge(node) ? 1 : 0;
        }
        return count;
    }

    template <typename T> inline
    RBTreeNode<TreeElement<T, GraphAdjSet<T>>>* Graph<T>::getNode(const T &vertex){
        return _tree.getNode(vertex);
    }

    template <typename T> inline
    std::vector<T> Graph<T>::adjVertex(const T& vertex){
        return _tree.get(vertex).adjVertex();
    }

    template <typename T> inline
    std::vector<RBTreeNode<TreeElement<T, GraphAdjSet<T>>>*> Graph<T>::adjVertexNodes(const T &vertex){
        return _tree.get(vertex).adjVertexNodes();
    }

    template <typename T> inline
    std::vector<RBTreeNode<TreeElement<T, GraphAdjSet<T>>>*> Graph<T>::getAllNodes(){
        return _tree.getAllNodes();
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
            auto d2 = node->element.value.degree();
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
        auto v = _tree.getNode(vertex);
        auto nodes = v->element.value.adjVertexNodes();
        for (auto node: nodes) {
            node->element.value.deleteEdge(v);
            _edge_count--;
        }
        _tree.del(vertex);
        return *this;
    }

    template <typename T> inline
    bool Graph<T>::hasVertex(const T &v){
        auto nodes = _tree.getAllNodes();
        for (auto &node: nodes) {
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
        if (wp != vp) {
            wp->element.value.deleteEdge(vp);
        }
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
