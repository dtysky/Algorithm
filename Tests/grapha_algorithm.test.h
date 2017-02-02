//
//  grapha_algorithm
//  Algorithm
//
//  Created by dtysky on 17/1/26.
//  Copyright © 2017 dtysky@outlook.com. All rights reserved.
//

#ifndef ALGORITHM_GRAPHA_ALGORITHM_TEST_H
#define ALGORITHM_GRAPHA_ALGORITHM_TEST_H

#include <string>
#include <iostream>
#include <vector>
#include "graph.h"
#include "graph_algorithm.h"


namespace my_algorithm {
    using std::cout;
    using std::endl;
    using data_structures::Graph;

    void testGraphAlgorithm() {
        Graph<std::string> graph;

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

        graph.addEdge("e", "e")
            .addEdge("e", "a")
            .addEdge("e", "a")
            .addEdge("b", "a")
            .addEdge("c", "a")
            .addEdge("a", "b")
            .addEdge("d", "e")
            .addEdge("aa", "e")
            .addEdge("bb", "e")
            .addEdge("cc", "e")
            .addEdge("dd", "e")
            .addEdge("b", "c")
            .addEdge("c", "f")
            .addEdge("f", "d");

        cout << graph << endl;

        cout << "<---- GraphDFS ---->" << endl;
        auto a_dfs = GraphDFS<std::string>(graph, "e");
        cout << a_dfs.count() << endl;
        a_dfs.print();
        cout << endl;
        for (auto key: std::vector<std::string>{"e", "b", "c", "a", "d", "f", "aa", "bb", "cc", "dd", "ee"}) {
            cout << key << ":" << a_dfs.marked(key) << endl;
        }
        cout << endl;

        cout << "<---- GraphPathsDFS ---->" << endl;
        auto a_path_dfs = GraphPathsDFS<std::string>(graph, "e");
        for (auto key: std::vector<std::string>{"e", "b", "c", "a", "d", "f", "aa", "bb", "cc", "dd", "ee"}) {
            cout << "-> " << key << " - " << a_path_dfs.hasPathTo(key) << endl;
        }
        a_path_dfs.print();
        cout << endl;

        cout << "<---- GraphPathsBFS ---->" << endl;
        auto a_path_bfs = GraphPathsBFS<std::string>(graph, "e");
        for (auto key: std::vector<std::string>{"e", "b", "c", "a", "d", "f", "aa", "bb", "cc", "dd", "ee"}) {
            cout << "-> " << key << " - " << a_path_bfs.hasPathTo(key) << endl;
        }
        a_path_bfs.print();
    }
}

#endif //ALGORITHM_GRAPHA_ALGORITHM_TEST_H
