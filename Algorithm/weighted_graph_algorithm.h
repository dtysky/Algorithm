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
            auto size = graph.vertexCount();
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
                if (count == size - 1) {
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
}

#endif //ALGORITHM_WEIGHTED_GRAPH_ALGORITHM_H
