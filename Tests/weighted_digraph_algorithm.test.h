//
//  weighted_digraph_algorithm
//  Algorithm
//
//  Created by dtysky on 2017/3/19.
//  Copyright © 2017 dtysky@outlook.com. All rights reserved.
//

#ifndef ALGORITHM_WEIGHTED_DIGRAPH_ALGORITHM_TEST_H
#define ALGORITHM_WEIGHTED_DIGRAPH_ALGORITHM_TEST_H

#include <string>
#include <iostream>
#include <vector>
#include "weighted_digraph.h"
#include "weighted_digraph_algorithm.h"


namespace my_algorithm {
    using std::cout;
    using std::endl;
    using data_structures::WeightedDigraph;

    void testWeightDigraphAlgorithm() {
        WeightedDigraph<int, int> graph;
        for (int i = 0; i <= 7; i++) {
            graph.addVertex(i);
        }

        graph.addEdge(4, 5, 35)
            .addEdge(5, 4, 35)
            .addEdge(4, 7, 37)
            .addEdge(5, 7, 28)
            .addEdge(7, 5, 28)
            .addEdge(5, 1, 32)
            .addEdge(0, 4, 38)
            .addEdge(0, 2, 26)
            .addEdge(7, 3, 39)
            .addEdge(1, 3, 29)
            .addEdge(2, 7, 34)
            .addEdge(6, 2, 40)
            .addEdge(3, 6, 52)
            .addEdge(6, 0, 58)
            .addEdge(6, 4, 93);

        cout << graph << endl;

        cout << "<---- WeightedDigraphSPDijkstra ---->" << endl;
        auto a_sp_dij = WeightedDigraphSPDijkstra<int, int>(graph, 0);
        for (int i = 0; i <= 7; i++) {
            if (!a_sp_dij.hasPathTo(i)) {
                continue;
            }
            cout << 0 << " to " << i << ":" << endl;
            cout << "weight: " << a_sp_dij.weightTo(i) << endl;
            cout << "path: ";
            for (auto &edge: a_sp_dij.pathTo(i)) {
                cout << edge << " ";
            }
            cout << endl;
        }

        cout << endl << endl;

        graph.clear();
        for (int i = 0; i <= 7; i++) {
            graph.addVertex(i);
        }
        graph.addEdge(5, 4, 35)
            .addEdge(4, 7, 37)
            .addEdge(5, 7, 28)
            .addEdge(5, 1, 32)
            .addEdge(4, 0, 38)
            .addEdge(0, 2, 26)
            .addEdge(3, 7, 39)
            .addEdge(1, 3, 29)
            .addEdge(7, 2, 34)
            .addEdge(6, 2, 40)
            .addEdge(3, 6, 52)
            .addEdge(6, 0, 58)
            .addEdge(6, 4, 93);

        cout << graph << endl;

        cout << "<---- WeightedDigraphSPAcyclic ---->" << endl;
        auto a_sp_ac = WeightedDigraphSPAcyclic<int, int>(graph);
        auto start = a_sp_ac.start();
        for (int i = 0; i <= 7; i++) {
            if (!a_sp_ac.hasPathTo(i)) {
                continue;
            }
            cout << start << " to " << i << ":" << endl;
            cout << "weight: " << a_sp_ac.weightTo(i) << endl;
            cout << "path: ";
            for (auto &edge: a_sp_ac.pathTo(i)) {
                cout << edge << " ";
            }
            cout << endl;
        }

    }
}

#endif //ALGORITHM_WEIGHTED_DIGRAPH_ALGORITHM_TEST_H
