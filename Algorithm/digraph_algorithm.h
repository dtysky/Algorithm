//
//  digraph_algorithm
//  Algorithm
//
//  Created by dtysky on 2017/2/20.
//  Copyright © 2017 dtysky@outlook.com. All rights reserved.
//

#ifndef ALGORITHM_DIGRAPH_ALGORITHM_H
#define ALGORITHM_DIGRAPH_ALGORITHM_H

#include <cstdio>
#include "digraph.h"
#include "graph_algorithm.h"


namespace my_algorithm {
    using data_structures::Digraph;

    template <typename T>
    class DigraphDFS: public DFS<Digraph<T>, T> {
    public:
        DigraphDFS(Digraph<T>& graph, const T& vertex): DFS<Digraph<T>, T>(graph, vertex) {};
    };

    template <typename T>
    class DigraphPathsDFS: public PathsDFS<Digraph<T>, T> {
    public:
        DigraphPathsDFS(Digraph<T>& graph, const T& vertex): PathsDFS<Digraph<T>, T>(graph, vertex) {};
    };

    template <typename T>
    class DigraphPathsBFS: public PathsBFS<Digraph<T>, T> {
    public:
        DigraphPathsBFS(Digraph<T>& graph, const T& vertex): PathsBFS<Digraph<T>, T>(graph, vertex) {};
    };

    template <typename T>
    class DigraphFindCycle {
        typedef RBTreeNode<TreeElement<T, GraphAdjSet<T>>> Node;
    protected:
        std::vector<Node*> _marked_nodes;
        std::vector<Node*> _onstack_nodes;
        std::vector<Node*> _cycle_nodes;
        bool _has_cycle;
        void _dfs(Node* vertex) {
            auto adj_set = vertex->element.value.adjVertexNodes();
            _onstack_nodes.push_back(vertex);
            _marked_nodes.push_back(vertex);
            for (auto v: adj_set) {
                if (_has_cycle) {
                    return;
                }
                if (isInVector<Node*>(_onstack_nodes, v)) {
                    _has_cycle = true;
                    auto in_range = false;
                    for (auto node: _onstack_nodes) {
                        if(node == v) {
                            in_range = true;
                        }
                        if (in_range) {
                            _cycle_nodes.push_back(node);
                        }
                        if (node == vertex) {
                            return;
                        }
                    }
                    return;
                }
                if (isInVector<Node*>(_marked_nodes, v)) {
                    continue;
                }
                _dfs(v);
            }
            _onstack_nodes.pop_back();
        }

    public:
        DigraphFindCycle(Digraph<T>& graph) {
            _has_cycle = false;
            auto nodes = graph.getAllNodes();
            for (auto start_node: nodes) {
                if (_has_cycle) {
                    return;
                }
                _onstack_nodes = {};
                if (!isInVector<Node*>(_marked_nodes, start_node)) {
                    _dfs(start_node);
                }
            }

        }
        bool hasCycle() {
            return _has_cycle;
        }
        std::vector<Node*> firstCycleNodes() {
            return _cycle_nodes;
        }
        std::vector<T> firstCycle() {
            std::vector<T> result;
            for (auto &node: _cycle_nodes) {
                result.push_back(node->element.key);
            }
            return result;
        }
    };

    template <typename T>
    class DigraphDFO {
        typedef RBTreeNode<TreeElement<T, GraphAdjSet<T>>> Node;
    protected:
        std::vector<Node*> _marked_nodes;
        std::vector<Node*> _pre_nodes;
        std::vector<Node*> _post_nodes;
        std::vector<Node*> _reserve_post_nodes;
        void _dfs(Node* vertex) {
            auto adj_set = vertex->element.value.adjVertexNodes();
            _marked_nodes.push_back(vertex);
            _pre_nodes.insert(_pre_nodes.end(), vertex);
            for (auto v: adj_set) {
                if (isInVector<Node*>(_marked_nodes, v)) {
                    continue;
                }
                _dfs(v);
            }
            _post_nodes.insert(_post_nodes.end(), vertex);
            _reserve_post_nodes.insert(_reserve_post_nodes.begin(), vertex);
        }

    public:
        DigraphDFO(Digraph<T>& graph) {
            auto nodes = graph.getAllNodes();
            for (auto start_node: nodes) {
                if (!isInVector<Node*>(_marked_nodes, start_node)) {
                    _dfs(start_node);
                }
            }

        }
        std::vector<Node*> preNodes() {
            return _pre_nodes;
        }
        std::vector<Node*> postNodes() {
            return _post_nodes;
        }
        std::vector<Node*> reversePostNodes() {
            return _reserve_post_nodes;
        }
        std::vector<T> pre() {
            std::vector<T> result;
            for (auto &node: _pre_nodes) {
                result.insert(result.end(), node->element.key);
            }
            return result;
        }
        std::vector<T> post() {
            std::vector<T> result;
            for (auto &node: _post_nodes) {
                result.insert(result.end(), node->element.key);
            }
            return result;
        }
        std::vector<T> reversePost() {
            std::vector<T> result;
            for (auto &node: _reserve_post_nodes) {
                result.insert(result.end(), node->element.key);
            }
            return result;
        }
    };

    template <typename T>
    class DigraphTopological {
        typedef RBTreeNode<TreeElement<T, GraphAdjSet<T>>> Node;
    protected:
        std::vector<Node*> _nodes;
    public:
        DigraphTopological(Digraph<T>& graph) {
            if (!DigraphFindCycle<T>(graph).hasCycle()) {
                _nodes = DigraphDFO<T>(graph).reversePostNodes();
            }
        }
        std::vector<Node*> orderNodes() {
            return _nodes;
        }
        std::vector<T> order() {
            std::vector<T> result;
            for (auto &node: _nodes) {
                result.insert(result.end(), node->element.key);
            }
            return result;
        }
    };

    template <typename T>
    class DigraphSCCKosaraju {
        typedef RBTreeNode<TreeElement<T, GraphAdjSet<T>>> Node;
    protected:
        std::vector<Node*> _marked_nodes;
        std::vector<std::vector<Node*>> _scc_nodes;
        void _dfs(Node* vertex, size_t index) {
            auto adj_set = vertex->element.value.adjVertexNodes();
            _marked_nodes.push_back(vertex);
            _scc_nodes[index].push_back(vertex);
            for (auto v: adj_set) {
                if (isInVector<Node*>(_marked_nodes, v)) {
                    continue;
                }
                _dfs(v, index);
            }
        }
    public:
        DigraphSCCKosaraju(Digraph<T>& graph) {
            _marked_nodes = {};
            Digraph<T> reversed_graph;
            graph.reverse(reversed_graph);
            auto vertexes = DigraphDFO<T>(reversed_graph).reversePost();
            size_t index = 0;
            for (auto &vertex: vertexes) {
                auto node = graph.getNode(vertex);
                if (isInVector<Node*>(_marked_nodes, node)) {
                    continue;
                }
                _scc_nodes.push_back({});
                _dfs(node, index);
                index++;
            }
        }
        std::vector<std::vector<Node*>> sccNodes() {
            return _scc_nodes;
        }
        std::vector<std::vector<T>> scc() {
            std::vector<std::vector<T>> result;
            size_t i = 0;
            for (auto &nodes: _scc_nodes) {
                result.push_back({});
                for (auto &node: nodes) {
                    result[i].push_back(node->element.key);
                }
                i++;
            }
            return result;
        }
    };
}

#endif //ALGORITHM_DIGRAPH_ALGORITHM_H
