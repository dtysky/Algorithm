//
//  weighted_graph_algorithm
//  Algorithm
//
//  Created by dtysky on 2017/2/26.
//  Copyright © 2017 dtysky@outlook.com. All rights reserved.
//

#ifndef ALGORITHM_WEIGHTED_GRAPH_ALGORITHM_H
#define ALGORITHM_WEIGHTED_GRAPH_ALGORITHM_H

#include <cstdio>
#include "weighted_graph.h"
#include "priority_queue.h"
#include "union_find.h"


namespace my_algorithm {
    using data_structures::WeightedGraph;
    using data_structures::WeightedGraphEdge;
    using data_structures::WeightedGraphAdjSet;
    using data_structures::TreeElement;
    using data_structures::RBTreeNode;
    using data_structures::SymbolTable;
    using data_structures::PriorityQueue;

    // only works on connected graph
    template <typename T, typename Weight>
    class WeightedGraphMSTPrim {
        typedef RBTreeNode<TreeElement<T, WeightedGraphAdjSet<T, Weight>>> Node;
        typedef WeightedGraphEdge<Node, Weight> Edge;
    protected:
        std::vector<Node*> _marked_nodes;
        PriorityQueue<Edge> _edges_queue;
        std::vector<Edge> _tree;
        Weight _weight;
        void _visit(Node* vertex) {
            _marked_nodes.push_back(vertex);
            auto adj_edges = vertex->element.value.adjEdges();
            for (auto &e: adj_edges) {
                if (isInVector<Node*>(_marked_nodes, e.to)) {
                    continue;
                }
                _edges_queue.enqueue(e);
            }
        }

    public:
        WeightedGraphMSTPrim(WeightedGraph<T, Weight>& graph) {
            _marked_nodes.clear();
            _edges_queue.clear();
            auto count = 0;
            auto size = graph.vertexCount() - 1;
            _visit(graph.rootNode());
            while (!_edges_queue.isEmpty()) {
                auto edge = _edges_queue.dequeueMinN();
                auto markedFrom = isInVector<Node*>(_marked_nodes, edge.from);
                auto markedTo = isInVector<Node*>(_marked_nodes, edge.to);
                if (markedFrom && markedTo) {
                    continue;
                }
                _tree.push_back(edge);
                count++;
                _weight += edge.weight;
                if (count == size) {
                    return;
                }
                if (!markedFrom) {
                    _visit(edge.from);
                }
                if (!markedTo) {
                    _visit(edge.to);
                }
            }
        }
        std::vector<Edge> edges() {
            return _tree;
        }
        Weight weight() {
            return _weight;
        }
    };

    // only works on connected graph
    template <typename T, typename Weight>
    class WeightedGraphMSTKruskal {
        typedef RBTreeNode<TreeElement<T, WeightedGraphAdjSet<T, Weight>>> Node;
        typedef WeightedGraphEdge<Node, Weight> Edge;
    protected:
        UnionFind<Node*> _uf;
        PriorityQueue<Edge> _edges_queue;
        std::vector<Edge> _tree;
        Weight _weight;

    public:
        WeightedGraphMSTKruskal(WeightedGraph<T, Weight>& graph) {
            _uf = UnionFind<Node*>();
            _edges_queue = graph.getSortedEdges();
            auto count = 0;
            auto size = graph.vertexCount() - 1;
            while (!_edges_queue.isEmpty()) {
                auto edge = _edges_queue.dequeueMinN();
                if (_uf.connected(edge.from, edge.to)) {
                    continue;
                }
                _tree.push_back(edge);
                count++;
                _weight += edge.weight;
                if (count == size) {
                    return;
                }
                _uf.un(edge.from, edge.to);
            }
        }
        std::vector<Edge> edges() {
            return _tree;
        }
        Weight weight() {
            return _weight;
        }
    };
}

#endif //ALGORITHM_WEIGHTED_GRAPH_ALGORITHM_H
