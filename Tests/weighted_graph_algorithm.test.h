//
//  weighted_graph_algorithm
//  Algorithm
//
//  Created by dtysky on 2017/2/27.
//  Copyright © 2017 dtysky@outlook.com. All rights reserved.
//

#ifndef ALGORITHM_WEIGHTED_GRAPH_ALGORITHM_TEST_H
#define ALGORITHM_WEIGHTED_GRAPH_ALGORITHM_TEST_H

#include <string>
#include <iostream>
#include <vector>
#include "weighted_graph.h"
#include "weighted_graph_algorithm.h"


namespace my_algorithm {
    using std::cout;
    using std::endl;
    using data_structures::WeightedGraph;

    void testWeightGraphAlgorithm() {
        WeightedGraph<int, int> graph;
        for (int i = 0; i <= 7; i++) {
            graph.addVertex(i);
        }

        graph.addEdge(4, 5, 35)
            .addEdge(4, 7, 47)
            .addEdge(5, 7, 28)
            .addEdge(0, 7, 16)
            .addEdge(1, 5, 32)
            .addEdge(0, 4, 38)
            .addEdge(2, 3, 17)
            .addEdge(1, 7, 19)
            .addEdge(0, 2, 26)
            .addEdge(1, 2, 36)
            .addEdge(1, 3, 29)
            .addEdge(2, 7, 34)
            .addEdge(6, 2, 40)
            .addEdge(3, 6, 52)
            .addEdge(6, 0, 58)
            .addEdge(6, 4, 93);

        cout << graph << endl;

        cout << "<---- WeightedGraphMSTPrim ---->" << endl;
        auto a_mst = WeightedGraphMSTPrim<int, int>(graph);
        for (auto &edge: a_mst.edges()) {
            cout << edge << endl;
        }
        cout << a_mst.weight() << endl;
    }
}

#endif //ALGORITHM_WEIGHTED_GRAPH_ALGORITHM_TEST_H
