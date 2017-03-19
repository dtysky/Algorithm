//
//  weighted_digraph_algorithm
//  Algorithm
//
//  Created by dtysky on 2017/3/11.
//  Copyright © 2017 dtysky@outlook.com. All rights reserved.
//

#ifndef ALGORITHM_WEIGHTED_DIGRAPH_ALGORITHM_H
#define ALGORITHM_WEIGHTED_DIGRAPH_ALGORITHM_H

#include <cstdio>
#include "weighted_digraph.h"
#include "priority_queue.h"
#include "union_find.h"


namespace my_algorithm {
    using data_structures::WeightedDigraph;
    using data_structures::WeightedGraphEdge;
    using data_structures::WeightedGraphAdjSet;
    using data_structures::TreeElement;
    using data_structures::RBTreeNode;
    using data_structures::SymbolTable;
    using data_structures::PriorityQueue;

    // only works on connected graph and the weight must be positive
    template <typename T, typename Weight>
    class WeightedDigraphSPDijkstra {
        typedef RBTreeNode<TreeElement<T, WeightedGraphAdjSet<T, Weight>>> Node;
        typedef WeightedGraphEdge<Node, Weight> Edge;
        struct SPElement {
        public:
            T vertex;
            Weight weight;
            SPElement() {}
            SPElement(T vertex, const Weight& weight) {
                this->vertex = vertex;
                this->weight = weight;
            }
            SPElement(const SPElement& element) {
                vertex = element.vertex;
                weight = element.weight;
            }
            SPElement& operator=(const SPElement& element) {
                vertex = element.vertex;
                weight = element.weight;
                return *this;
            }
            bool operator==(const SPElement& element) const {
                return vertex == element.vertex;
            }
            bool operator!=(const SPElement& element) const {
                return vertex != element.vertex;
            }
            bool operator>(const SPElement& element) const {
                return weight > element.weight;
            }
            bool operator<(const SPElement& element) const {
                return weight < element.weight;
            }
            bool operator>=(const SPElement& element) const {
                return weight >= element.weight;
            }
            bool operator<=(const SPElement& element) const {
                return weight <= element.weight;
            }
        };
    protected:
        T _start;
        SymbolTable<T, Edge> _edge_to;
        SymbolTable<T, Weight> _weight_to;
        PriorityQueue<SPElement> _queue;
        void _relax(WeightedDigraph<T, Weight> &graph, const SPElement& element) {
            auto vertex = element.vertex;
            auto weight = element.weight;
            auto node = graph.getNode(vertex);
            auto edges = node->element.value.adjEdges();
            for (auto &edge: edges) {
                auto to_vertex = edge.to->element.key;
                auto new_weight = weight + edge.weight;
                if (!_weight_to.has(to_vertex)) {
                    _weight_to.set(to_vertex, new_weight);
                    _edge_to.set(to_vertex, edge);
                    _queue.enqueue(SPElement(to_vertex, new_weight));
                    continue;
                }
                if (_weight_to.get(to_vertex) > new_weight) {
                    _weight_to.set(to_vertex, new_weight);
                    _edge_to.set(to_vertex, edge);
                    // todo: create a new priority queue which supports method `change`
                    auto size = _queue.size();
                    for (size_t i = 1; i <= size; i++) {
                        if (_queue.minN(i).vertex == to_vertex) {
                            _queue.dequeueMinN(i);
                            break;
                        }
                    }
                    _queue.enqueue(SPElement(to_vertex, new_weight));
                }
            }
        }
    public:
        WeightedDigraphSPDijkstra(WeightedDigraph<T, Weight> &graph, T vertex) {
            _start = vertex;
            _edge_to.clear();
            _weight_to.clear();
            _queue.clear();
            auto start = graph.getNode(vertex);
            _edge_to.set(vertex, Edge(start, start, Weight()));
            _weight_to.set(vertex, Weight());
            _queue.enqueue(SPElement(_start, Weight()));
            while (!_queue.isEmpty()) {
                _relax(graph, _queue.dequeueMinN(1));
            }
        }
        virtual ~WeightedDigraphSPDijkstra() {}
        Weight weightTo(T vertex) {
            if (!hasPathTo(vertex)) {
                throw std::out_of_range("No path!");
            }
            return _weight_to.get(vertex);
        }
        bool hasPathTo(T vertex) {
            return _weight_to.has(vertex);
        }
        std::vector<Edge>pathTo(T vertex) {
            if (!hasPathTo(vertex)) {
                throw std::out_of_range("No path!");
            }
            std::vector<Edge> path;
            auto edge = _edge_to.get(vertex);
            while (true) {
                path.insert(path.begin(), edge);
                if (edge.from->element.key == _start) {
                    break;
                }
                edge = _edge_to.get(edge.from->element.key);
            }
            return path;
        }
    };

    // only works on DAG
    template <typename T, typename Weight>
    class WeightedDigraphSPAcyclic {
        typedef RBTreeNode<TreeElement<T, WeightedGraphAdjSet<T, Weight>>> Node;
        typedef WeightedGraphEdge<Node, Weight> Edge;
    protected:
        T _start;
        SymbolTable<T, Edge> _edge_to;
        SymbolTable<T, Weight> _weight_to;
        std::vector<Node*> _marked_nodes;
        std::vector<Node*> _reserve_post_nodes;
        void _dfs(Node* vertex) {
            auto edges = vertex->element.value.adjEdges();
            _marked_nodes.push_back(vertex);
            for (auto &edge: edges) {
                if (isInVector<Node*>(_marked_nodes, edge.to)) {
                    continue;
                }
                _dfs(edge.to);
            }
            _reserve_post_nodes.insert(_reserve_post_nodes.begin(), vertex);
        }
        void _relax(WeightedDigraph<T, Weight> &graph, Node* node) {
            auto vertex = node->element.key;
            auto weight = _weight_to.get(vertex);
            auto edges = node->element.value.adjEdges();
            for (auto &edge: edges) {
                auto to_vertex = edge.to->element.key;
                auto new_weight = weight + edge.weight;
                if (!_weight_to.has(to_vertex)) {
                    _weight_to.set(to_vertex, new_weight);
                    _edge_to.set(to_vertex, edge);
                    continue;
                }
                if (_weight_to.get(to_vertex) > new_weight) {
                    _weight_to.set(to_vertex, new_weight);
                    _edge_to.set(to_vertex, edge);
                }
            }
        }
    public:
        WeightedDigraphSPAcyclic(WeightedDigraph<T, Weight> &graph) {
            _marked_nodes.clear();
            _reserve_post_nodes.clear();
            auto nodes = graph.getAllNodes();
            // Topological sorting
            for (auto node: nodes) {
                if (!isInVector<Node*>(_marked_nodes, node)) {
                    _dfs(node);
                }
            }

            auto start_node = _reserve_post_nodes[0];
            _start = start_node->element.key;
            _edge_to.clear();
            _weight_to.clear();
            _edge_to.set(_start, Edge(start_node, start_node, Weight()));
            _weight_to.set(_start, Weight());

            for (auto node: _reserve_post_nodes) {
                _relax(graph, node);
            }
        }
        virtual ~WeightedDigraphSPAcyclic() {}
        T start() {
            return _start;
        }
        Weight weightTo(T vertex) {
            if (!hasPathTo(vertex)) {
                throw std::out_of_range("No path!");
            }
            return _weight_to.get(vertex);
        }
        bool hasPathTo(T vertex) {
            return _weight_to.has(vertex);
        }
        std::vector<Edge>pathTo(T vertex) {
            if (!hasPathTo(vertex)) {
                throw std::out_of_range("No path!");
            }
            std::vector<Edge> path;
            auto edge = _edge_to.get(vertex);
            while (true) {
                path.insert(path.begin(), edge);
                if (edge.from->element.key == _start) {
                    break;
                }
                edge = _edge_to.get(edge.from->element.key);
            }
            return path;
        }
    };
}

#endif //ALGORITHM_WEIGHTED_DIGRAPH_ALGORITHM_H
