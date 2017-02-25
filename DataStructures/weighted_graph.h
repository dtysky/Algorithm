//
//  weighted_graph
//  Algorithm
//
//  Created by dtysky on 2017/2/25.
//  Copyright © 2017 dtysky@outlook.com. All rights reserved.
//

#ifndef ALGORITHM_WEIGHTED_GRAPH_H
#define ALGORITHM_WEIGHTED_GRAPH_H

#include <cstdio>
#include <iostream>
#include "red_black_tree.h"
#include "weighted_graph_adj_set.h"
#include <vector>
#include <algorithm>


namespace data_structures {
    template <typename T, typename Weight>
    class WeightedGraph {
        typedef RBTreeNode<TreeElement<T, WeightedGraphAdjSet<T, Weight>>> Node;
        typedef WeightedGraphEdge<Node, Weight> Edge;
    protected:
        RBTree<T, WeightedGraphAdjSet<T, Weight>> _tree;
        size_t _edge_count;
        void _copy(WeightedGraph<T, Weight> &graph);
        bool _equal(WeightedGraph<T, Weight> &graph);
    public:
        WeightedGraph();
        WeightedGraph(WeightedGraph<T, Weight> &graph);
        virtual ~WeightedGraph();
        bool isEmpty();
        WeightedGraph<T, Weight>& clear();
        size_t vertexCount();
        size_t edgeCount();
        size_t selfLoopsCount();
        RBTreeNode<TreeElement<T, WeightedGraphAdjSet<T, Weight>>>* getNode(const T& vertex);
        std::vector<T> adjVertex(const T& vertex);
        std::vector<Node*> adjVertexNodes(const T& vertex);
        std::vector<Node*> getAllNodes();
        std::vector<Edge> getAllEdges();
        size_t degree(const T& vertex);
        size_t maxDegree();
        size_t avgDegree();
        WeightedGraph<T, Weight>& addVertex(const T& v);
        WeightedGraph<T, Weight>& deleteVertex(const T& v);
        bool hasVertex(const T& v);
        WeightedGraph<T, Weight>& addEdge(const T& v, const T& w, Weight weight);
        WeightedGraph<T, Weight>& deleteEdge(const T& v, const T& w);
        bool hasEdge(const T& v, const T& w);
        WeightedGraph<T, Weight>& operator=(WeightedGraph<T, Weight> &graph);
        bool operator==(WeightedGraph<T, Weight> &graph);
        bool operator!=(WeightedGraph<T, Weight> &graph);
        friend std::ostream &operator<<(std::ostream &out, WeightedGraph<T, Weight> &graph) {
            auto nodes = graph._tree.getAllNodes();
            for (auto node: nodes) {
                out << node->element.key << ": ";
                for (auto &e: node->element.value.adjEdges()) {
                    out << e.to->element.key << "(" << e.weight << ")" << " ";
                }
                out << std::endl;
            }
            return out;
        }
    };

    template <typename T, typename Weight> inline
    WeightedGraph<T, Weight>::WeightedGraph() {
        _tree = RBTree<T, WeightedGraphAdjSet<T, Weight>>();
        _edge_count = 0;
    }

    template <typename T, typename Weight> inline
    WeightedGraph<T, Weight>::WeightedGraph(WeightedGraph<T, Weight> &graph) {
        _copy(graph);
    }

    template <typename T, typename Weight> inline
    WeightedGraph<T, Weight>::~WeightedGraph() {}

    // keys in WeightedGraphAdjSet are pointers, we can't copy them by default method
    template <typename T, typename Weight> inline
    void WeightedGraph<T, Weight>::_copy(WeightedGraph<T, Weight> &graph){
        _tree = RBTree<T, WeightedGraphAdjSet<T, Weight>>();
        auto nodes = graph._tree.getAllNodes();
        for (auto node: nodes) {
            _tree.add(node->element.key);
            _tree.set(node->element.key, WeightedGraphAdjSet<T, Weight>(_tree.getNode(node->element.key)));
        }
        for (auto node: nodes) {
            auto new_node = _tree.getNode(node->element.key);
            auto adj_edges = node->element.value.adjEdges();
            for (auto e: adj_edges) {
                new_node->element.value.addEdge(_tree.getNode(e.to->element.key), e.weight);
            }
        }
    }

    // keys in WeightedGraphAdjSet are pointers, we can't copy them by default method
    template <typename T, typename Weight> inline
    bool WeightedGraph<T, Weight>::_equal(WeightedGraph<T, Weight> &graph){
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

    template <typename T, typename Weight> inline
    WeightedGraph<T, Weight>& WeightedGraph<T, Weight>::operator=(WeightedGraph<T, Weight> &graph) {
        _copy(graph);
        return *this;
    }

    template <typename T, typename Weight> inline
    bool WeightedGraph<T, Weight>::operator==(WeightedGraph<T, Weight> &graph) {
        return _equal(graph);
    }

    template <typename T, typename Weight> inline
    bool WeightedGraph<T, Weight>::operator!=(WeightedGraph<T, Weight> &graph) {
        return !(_equal(graph));
    }

    template <typename T, typename Weight> inline
    bool WeightedGraph<T, Weight>::isEmpty() {
        return vertexCount() == 0;
    }

    template <typename T, typename Weight> inline
    WeightedGraph<T, Weight>& WeightedGraph<T, Weight>::clear(){
        _tree.clear();
        return *this;
    }

    template <typename T, typename Weight> inline
    size_t WeightedGraph<T, Weight>::vertexCount(){
        return _tree.size();
    }

    template <typename T, typename Weight> inline
    size_t WeightedGraph<T, Weight>::edgeCount(){
        return _edge_count;
    }

    template <typename T, typename Weight> inline
    size_t WeightedGraph<T, Weight>::selfLoopsCount(){
        auto nodes = _tree.getAllNodes();
        size_t count = 0;
        for (auto node: nodes) {
            count += node->element.value.hasEdge(node) ? 1 : 0;
        }
        return count;
    }

    template <typename T, typename Weight> inline
    RBTreeNode<TreeElement<T, WeightedGraphAdjSet<T, Weight>>>* WeightedGraph<T, Weight>::getNode(const T &vertex){
        return _tree.getNode(vertex);
    }

    template <typename T, typename Weight> inline
    std::vector<T> WeightedGraph<T, Weight>::adjVertex(const T& vertex){
        return _tree.get(vertex).adjVertex();
    }

    template <typename T, typename Weight> inline
    std::vector<RBTreeNode<TreeElement<T, WeightedGraphAdjSet<T, Weight>>>*> WeightedGraph<T, Weight>::adjVertexNodes(const T &vertex){
        return _tree.get(vertex).adjVertexNodes();
    }

    template <typename T, typename Weight> inline
    std::vector<RBTreeNode<TreeElement<T, WeightedGraphAdjSet<T, Weight>>>*> WeightedGraph<T, Weight>::getAllNodes(){
        return _tree.getAllNodes();
    }

    template <typename T, typename Weight> inline
    std::vector<WeightedGraphEdge<RBTreeNode<TreeElement<T, WeightedGraphAdjSet<T, Weight>>>, Weight>> WeightedGraph<T, Weight>::getAllEdges(){
        std::vector<Edge> result;
        auto nodes = _tree.getAllNodes();
        for (auto node: nodes) {
            auto adj_edges = node->element.value.adjEdges();
            for (auto e: adj_edges) {
                result.push_back(e);
            }
        }
        return result;
    }

    template <typename T, typename Weight> inline
    size_t WeightedGraph<T, Weight>::degree(const T &vertex){
        return _tree.get(vertex).degree();
    }

    template <typename T, typename Weight> inline
    size_t WeightedGraph<T, Weight>::maxDegree(){
        auto nodes = _tree.getAllNodes();
        size_t d = 0;
        for (auto node: nodes) {
            auto d2 = node->element.value.degree();
            d = d2 > d ? d2 : d;
        }
        return d;
    }

    template <typename T, typename Weight> inline
    size_t WeightedGraph<T, Weight>::avgDegree(){
        return vertexCount() / edgeCount();
    }

    template <typename T, typename Weight> inline
    WeightedGraph<T, Weight>& WeightedGraph<T, Weight>::addVertex(const T &vertex){
        _tree.add(vertex);
        _tree.set(vertex, WeightedGraphAdjSet<T, Weight>(_tree.getNode(vertex)));
        return *this;
    }

    template <typename T, typename Weight> inline
    WeightedGraph<T, Weight>& WeightedGraph<T, Weight>::deleteVertex(const T &vertex){
        auto v = _tree.getNode(vertex);
        auto nodes = v->element.value.adjVertexNodes();
        for (auto node: nodes) {
            node->element.value.deleteEdge(v);
            _edge_count--;
        }
        _tree.del(vertex);
        return *this;
    }

    template <typename T, typename Weight> inline
    bool WeightedGraph<T, Weight>::hasVertex(const T &v){
        auto nodes = _tree.getAllNodes();
        for (auto &node: nodes) {
            if (node->element.key == v) {
                return true;
            }
        }
        return false;
    }

    template <typename T, typename Weight> inline
    WeightedGraph<T, Weight>& WeightedGraph<T, Weight>::addEdge(const T &v, const T &w, Weight weight){
        auto vp = _tree.getNode(v);
        auto wp = _tree.getNode(w);
        if (vp->element.value.addEdge(wp, weight)) {
            _edge_count++;
        }
        wp->element.value.addEdge(vp, weight);
        return *this;
    }

    template <typename T, typename Weight> inline
    WeightedGraph<T, Weight>& WeightedGraph<T, Weight>::deleteEdge(const T &v, const T &w){
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

    template <typename T, typename Weight> inline
    bool WeightedGraph<T, Weight>::hasEdge(const T &v, const T &w){
        auto vp = _tree.getNode(v);
        auto wp = _tree.getNode(w);
        return vp->element.value.hasEdge(wp);
    }
}

#endif //ALGORITHM_WEIGHTED_GRAPH_H
