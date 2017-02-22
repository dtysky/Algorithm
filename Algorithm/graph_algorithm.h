//
//  graph_algorithm
//  Algorithm
//
//  Created by dtysky on 16/12/16.
//  Copyright © 2016 dtysky@outlook.com. All rights reserved.
//

#ifndef ALGORITHM_GRAPH_ALGORITHM_H
#define ALGORITHM_GRAPH_ALGORITHM_H

#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>
#include "graph.h"
#include "graph_adj_set.h"
#include "symbol_table.h"
#include "queue.h"
#include "utils.h"


namespace my_algorithm {
    using data_structures::Graph;
    using data_structures::GraphAdjSet;
    using data_structures::TreeElement;
    using data_structures::RBTreeNode;
    using data_structures::SymbolTable;
    using data_structures::Queue;

    template <class G, typename T>
    class DFS {
        typedef RBTreeNode<TreeElement<T, GraphAdjSet<T>>> Node;
    protected:
        std::vector<Node*> _marked_nodes;
        size_t _count;
        void _dfs(Node* vertex) {
            _marked_nodes.push_back(vertex);
            _count++;
            auto adj_set = vertex->element.value.adjVertexNodes();
            for (auto v: adj_set) {
                if (isInVector<Node*>(_marked_nodes, v)) {
                    continue;
                }
                _dfs(v);
            }
        }
    public:
        DFS(G& graph, const T& vertex) {
            _count = 0;
            _dfs(graph.getNode(vertex));
        }
        bool marked(const T& vertex) {
            for (auto node: _marked_nodes) {
                if (node->element.key == vertex) {
                    return true;
                }
            }
            return false;
        }
        size_t count() {
            return _count;
        }
        void print() {
            for (auto node: _marked_nodes) {
                std::cout << node->element.key << ' ';
            }
        }
    };

    template <class G, typename T>
    class PathsDFS {
        typedef RBTreeNode<TreeElement<T, GraphAdjSet<T>>> Node;
        typedef std::vector<Node*> Path;
    protected:
        std::vector<Node*> _marked_nodes;
        SymbolTable<T, Path> _paths;
        void _dfs(Node* vertex, Path& path) {
            _marked_nodes.push_back(vertex);
            auto adj_set = vertex->element.value.adjVertexNodes();
            for (auto v: adj_set) {
                if (isInVector<Node*>(_marked_nodes, v)) {
                    continue;
                }
                auto new_path = Path(path);
                new_path.push_back(v);
                _paths.set(v->element.key, new_path);
                _dfs(v, new_path);
            }
        }
    public:
        PathsDFS(G& graph, const T& vertex) {
            auto new_path = Path();
            _dfs(graph.getNode(vertex), new_path);
        }
        bool hasPathTo(const T& vertex) {
            return _paths.has(vertex);
        }
        std::vector<T> pathTo(const T& vertex) {
            std::vector<T> result = {};
            auto nodes = _paths.get(vertex);
            for (auto node: nodes) {
                result.push_back(node->element.key);
            }
            return result;
        }
        Path pathNodesTo(const T& vertex) {
            return _paths.get(vertex);
        }
        void print() {
            auto self = _marked_nodes[0]->element.key;
            auto paths = _paths.elements();
            for (auto path: paths) {
                std::cout << self << " -> " << path.key;
                std::cout << ": ";
                for (auto node: path.value) {
                    std::cout << node->element.key << ' ';
                }
                std::cout << std::endl;
            }
        }
    };

    template <class G, typename T>
    class PathsBFS {
        typedef RBTreeNode<TreeElement<T, GraphAdjSet<T>>> Node;
        typedef std::vector<Node*> Path;
    protected:
        std::vector<Node*> _marked_nodes;
        Queue<Node*> _queue;
        SymbolTable<T, Path> _paths;
        void _bfs(Node* start) {
            _paths.clear();
            _queue.enqueue(start);
            _paths.set(start->element.key, Path());
            while (!_queue.isEmpty()) {
                auto vertex = _queue.dequeue();
                _marked_nodes.push_back(vertex);
                auto adj_set = vertex->element.value.adjVertexNodes();
                for (auto v: adj_set) {
                    if (isInVector<Node*>(_marked_nodes, v)) {
                        continue;
                    }
                    _queue.enqueue(v);
                    if (!_paths.has(v->element.key)) {
                        _paths.set(v->element.key, _paths.get(vertex->element.key));
                    }
                    auto new_path = _paths.get(v->element.key);
                    new_path.push_back(v);
                    _paths.set(v->element.key, new_path);
                }
            }
        }
    public:
        PathsBFS(G& graph, const T& vertex) {
            _bfs(graph.getNode(vertex));
        }
        bool hasPathTo(const T& vertex) {
            return _paths.has(vertex);
        }
        std::vector<T> pathTo(const T& vertex) {
            std::vector<T> result = {};
            auto nodes = _paths.get(vertex);
            for (auto node: nodes) {
                result.push_back(node->element.key);
            }
            return result;
        }
        Path pathNodesTo(const T& vertex) {
            return _paths.get(vertex);
        }
        void print() {
            auto self = _marked_nodes[0]->element.key;
            auto paths = _paths.elements();
            for (auto path: paths) {
                std::cout << self << " -> " << path.key;
                std::cout << ": ";
                for (auto node: path.value) {
                    std::cout << node->element.key << ' ';
                }
                std::cout << std::endl;
            }
        }
    };

    template<typename T>
    class GraphDFS: public DFS<Graph<T>, T> {
    public:
        GraphDFS(Graph<T>& graph, const T& vertex): DFS<Graph<T>, T>(graph, vertex) {};
    };

    template<typename T>
    class GraphPathsDFS: public PathsDFS<Graph<T>, T> {
    public:
        GraphPathsDFS(Graph<T>& graph, const T& vertex): PathsDFS<Graph<T>, T>(graph, vertex) {};
    };

    template<typename T>
    class GraphPathsBFS: public PathsBFS<Graph<T>, T> {
    public:
        GraphPathsBFS(Graph<T>& graph, const T& vertex): PathsBFS<Graph<T>, T>(graph, vertex) {};
    };
}


#endif //ALGORITHM_GRAPH_ALGORITHM_H
