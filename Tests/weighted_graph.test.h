//
//  weighted_graph
//  Algorithm
//
//  Created by dtysky on 2017/2/25.
//  Copyright © 2017 dtysky@outlook.com. All rights reserved.
//

#ifndef ALGORITHM_WEIGHTED_GRAPH_TEST_H
#define ALGORITHM_WEIGHTED_GRAPH_TEST_H

#include <string>
#include <iostream>
#include <vector>
#include "weighted_graph.h"


namespace data_structures {
    using std::cout;
    using std::endl;

    void testWeightGraph() {
        WeightedGraph<std::string, int32_t> graph;
        cout << graph.isEmpty() << endl;
        cout << graph.vertexCount() << endl;
        cout << graph.edgeCount() << endl;

//        for (auto key: std::vector<std::string>{"e", "b", "c", "a", "d", "f", "aa", "bb", "cc", "dd", "ee"}) {
//            cout << key << ":" << endl << graph.addVertex(key) << endl;
//        }

        cout << "<---- AddVertex ---->" << endl;
        graph.addVertex("e")
            .addVertex("b")
            .addVertex("c")
            .addVertex("a")
            .addVertex("d")
            .addVertex("f")
            .addVertex("aa")
            .addVertex("bb")
            .addVertex("cc")
            .addVertex("dd")
            .addVertex("ee");
        cout << graph;
        cout << graph.vertexCount() << endl;
        cout << graph.edgeCount() << endl;
        cout << endl;

        cout << "<---- AddEdges ---->" << endl;
        graph.addEdge("e", "e", 1)
            .addEdge("e", "a", 2)
            .addEdge("e", "a", 3)
            .addEdge("b", "a", 4)
            .addEdge("c", "a", 5)
            .addEdge("a", "b", 6)
            .addEdge("d", "e", 7)
            .addEdge("f", "e", 8)
            .addEdge("aa", "e", -1)
            .addEdge("bb", "e", -2)
            .addEdge("cc", "e", -3)
            .addEdge("dd", "e", -4);
        cout << graph;
        cout << "<---- Edges ---->" << endl;

        for (auto &e: graph.getAllEdges()) {
            cout << e << endl;
        }
        cout << endl;
        cout << graph.vertexCount() << endl;
        cout << graph.edgeCount() << endl;
        cout << graph.selfLoopsCount() << endl;
        for (auto &v: graph.adjVertex("e")) {
            cout << v << " ";
        }
        cout << endl;
        cout << graph.degree("e") << endl;
        cout << graph.degree("ee") << endl;
        cout << graph.maxDegree() << endl;
        cout << graph.avgDegree() << endl;
        cout << graph.hasVertex("e") << endl;
        cout << graph.hasVertex("eee") << endl;
        cout << graph.hasEdge("e", "a") << endl;
        cout << graph.hasEdge("ee", "a") << endl;
        cout << endl;

        auto graph1 = graph;
        cout << graph1;
        cout << (graph == graph1) << endl;
        cout << endl;

        graph.deleteEdge("e", "a")
            .deleteEdge("b", "a")
            .deleteEdge("c", "a")
            .deleteEdge("d", "e")
            .deleteEdge("f", "e");
        cout << graph;
        cout << graph.vertexCount() << endl;
        cout << graph.edgeCount() << endl;
        cout << graph.selfLoopsCount() << endl;
        cout << endl;

        graph.deleteEdge("aa", "e")
            .deleteEdge("bb", "e")
            .deleteEdge("cc", "e")
            .deleteEdge("dd", "e");
        cout << graph;
        cout << endl;

        graph.deleteVertex("e")
            .deleteVertex("b")
            .deleteVertex("c")
            .deleteVertex("a")
            .deleteVertex("d")
            .deleteVertex("f")
            .deleteVertex("aa")
            .deleteVertex("bb")
            .deleteVertex("cc")
            .deleteVertex("dd")
            .deleteVertex("ee");
        cout << graph;
        cout << graph.vertexCount() << endl;
        cout << graph.edgeCount() << endl;
        cout << endl;

        cout << (graph == graph1) << endl;

        graph1.clear();
        cout << graph1 << endl;
    }
}


#endif //ALGORITHM_WEIGHTED_GRAPH_TEST_H
