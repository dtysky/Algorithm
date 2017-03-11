//
//  weighted_digraph
//  Algorithm
//
//  Created by dtysky on 2017/3/11.
//  Copyright © 2017 dtysky@outlook.com. All rights reserved.
//

#ifndef ALGORITHM_WEIGHTED_DIGRAPH_H
#define ALGORITHM_WEIGHTED_DIGRAPH_H

#include <cstdio>
#include "weighted_graph.h"

namespace data_structures {
    template <typename T, typename Weight>
    class WeightedDigraph : public WeightedGraph<T, Weight> {
    public:
        WeightedDigraph(): WeightedGraph<T, Weight>() {};
        WeightedDigraph(WeightedDigraph<T, Weight> &graph): WeightedGraph<T, Weight>(graph) {};
        virtual ~WeightedDigraph();
        WeightedDigraph<T, Weight>& addEdge(const T& v, const T& w, Weight weight);
        WeightedDigraph<T, Weight>& deleteEdge(const T& v, const T& w);
        void reverse(WeightedDigraph<T, Weight>& res_graph);
        friend std::ostream &operator<<(std::ostream &out, WeightedDigraph<T, Weight> &graph) {
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
    WeightedDigraph<T, Weight>::~WeightedDigraph() {}

    template <typename T, typename Weight> inline
    WeightedDigraph<T, Weight>& WeightedDigraph<T, Weight>::addEdge(const T& v, const T& w, Weight weight){
        if (v == w) {
            return *this;
        }
        auto vp = this->_tree.getNode(v);
        auto wp = this->_tree.getNode(w);
        if (vp->element.value.addEdge(wp, weight)) {
            this->_edge_count++;
        }
        return *this;
    }

    template <typename T, typename Weight> inline
    WeightedDigraph<T, Weight>& WeightedDigraph<T, Weight>::deleteEdge(const T& v, const T& w){
        auto vp = this->_tree.getNode(v);
        auto wp = this->_tree.getNode(w);
        if (vp->element.value.deleteEdge(wp)) {
            this->_edge_count--;
        }
        return *this;
    }

    template <typename T, typename Weight> inline
    void WeightedDigraph<T, Weight>::reverse(WeightedDigraph<T, Weight>& res_graph){
        res_graph.clear();
        auto nodes = this->_tree.getAllNodes();
        for (auto &node: nodes) {
            res_graph.addVertex(node->element.key);
        }
        for (auto &node: nodes) {
            auto adj_set = node->element.value.adjEdges();
            for (auto &edge: adj_set) {
                res_graph.addEdge(edge.to->element.key, edge.from->element.key, edge.weight);
            }
        }
    }
}

#endif //ALGORITHM_WEIGHTED_DIGRAPH_H
