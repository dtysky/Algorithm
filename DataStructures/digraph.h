//
//  digraph
//  Algorithm
//
//  Created by dtysky on 2017/2/18.
//  Copyright © 2017 dtysky@outlook.com. All rights reserved.
//

#ifndef ALGORITHM_DIGRAPH_H
#define ALGORITHM_DIGRAPH_H

#include <cstdio>
#include <vector>
#include "graph.h"


namespace data_structures {
    template <typename T>
    class Digraph: public Graph<T> {
    public:
        Digraph(): Graph<T>() {};
        Digraph(Digraph<T> &graph): Graph<T>(graph) {};
        virtual ~Digraph();
        Digraph<T>& addEdge(const T& v, const T& w);
        Digraph<T>& deleteEdge(const T& v, const T& w);
        void reverse(Digraph<T>& res_graph);
        friend std::ostream &operator<<(std::ostream &out, Digraph<T> &graph) {
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
    Digraph<T>::~Digraph() {}

    template <typename T> inline
    Digraph<T>& Digraph<T>::addEdge(const T& v, const T& w){
        auto vp = this->_tree.getNode(v);
        auto wp = this->_tree.getNode(w);
        if (vp->element.value.addEdge(wp)) {
            this->_edge_count++;
        }
        return *this;
    }

    template <typename T> inline
    Digraph<T>& Digraph<T>::deleteEdge(const T& v, const T& w){
        auto vp = this->_tree.getNode(v);
        auto wp = this->_tree.getNode(w);
        if (vp->element.value.deleteEdge(wp)) {
            this->_edge_count--;
        }
        return *this;
    }

    template <typename T> inline
    void Digraph<T>::reverse(Digraph<T>& res_graph){
        res_graph.clear();
        auto nodes = this->_tree.getAllNodes();
        for (auto &node: nodes) {
            res_graph.addVertex(node->element.key);
        }
        for (auto &node: nodes) {
            auto adj_set = node->element.value.adjVertexNodes();
            for (auto &v: adj_set) {
                res_graph.addEdge(v->element.key, node->element.key);
            }
        }
    }
}


#endif //ALGORITHM_DIGRAPH_H
