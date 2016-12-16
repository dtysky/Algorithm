//
//  graph
//  Algorithm
//
//  Created by dtysky on 16/12/16.
//  Copyright © 2016 dtysky@outlook.com. All rights reserved.
//

#include <string>
#include <iostream>
#include <vector>
#include "graph.h"


namespace data_structures {
    using std::cout;
    using std::endl;

    void testGraph() {
        Graph<std::string> graph;
        cout << graph.isEmpty() << endl;
        cout << graph.vertexCount() << endl;
        cout << graph.edgeCount() << endl;

//        for (auto key: std::vector<std::string>{"e", "b", "c", "a", "d", "f", "aa", "bb", "cc", "dd", "ee"}) {
//            cout << key << ":" << endl << graph.addVertex(key) << endl;
//        }

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

        graph.addEdge("e", "e")
            .addEdge("e", "a")
            .addEdge("e", "a")
            .addEdge("b", "a")
            .addEdge("c", "a")
            .addEdge("a", "b")
            .addEdge("d", "e")
            .addEdge("f", "e")
            .addEdge("aa", "e")
            .addEdge("bb", "e")
            .addEdge("cc", "e")
            .addEdge("dd", "e");
        cout << graph;
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

        graph.deleteEdge("e", "e")
            .deleteEdge("e", "a")
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
    }
}
