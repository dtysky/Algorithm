//
//  digraph_algorithm
//  Algorithm
//
//  Created by dtysky on 2017/2/21.
//  Copyright © 2017 dtysky@outlook.com. All rights reserved.
//

#ifndef ALGORITHM_DIGRAPH_ALGORITHM_TEST_H
#define ALGORITHM_DIGRAPH_ALGORITHM_TEST_H

#include <string>
#include <iostream>
#include <vector>
#include "digraph.h"
#include "digraph_algorithm.h"


namespace my_algorithm {
    using std::cout;
    using std::endl;
    using data_structures::Digraph;

    void testDiraphAlgorithm() {
        Digraph<std::string> graph;

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

        graph.addEdge("e", "a")
            .addEdge("e", "a")
            .addEdge("b", "a")
            .addEdge("a", "c")
            .addEdge("c", "d")
            .addEdge("d", "e")
            .addEdge("aa", "e")
            .addEdge("bb", "e")
            .addEdge("cc", "e")
            .addEdge("dd", "e")
            .addEdge("b", "c")
            .addEdge("c", "f")
            .addEdge("f", "d");

        cout << graph << endl;

        cout << "<---- DigraphFindCycle ---->" << endl;
        auto a_find_cycle = DigraphFindCycle<std::string>(graph);
        cout << a_find_cycle.hasCycle() << endl;
        if (a_find_cycle.hasCycle()) {
            for (auto &v: a_find_cycle.firstCycle()) {
                cout << v << " ";
            }
        }
        cout << endl << endl;

        graph.deleteEdge("e", "a")
            .deleteEdge("b", "a")
            .deleteEdge("a", "c")
            .deleteEdge("c", "d");

        cout << "<---- DigraphDFO ---->" << endl;
        auto a_dfo = DigraphDFO<std::string>(graph);
        cout << "<-- pre -->" << endl;
        for (auto &v: a_dfo.pre()) {
            cout << v << " ";
        }
        cout << endl;
        cout << "<-- post -->" << endl;
        for (auto &v: a_dfo.post()) {
            cout << v << " ";
        }
        cout << endl;
        cout << "<-- reversePost -->" << endl;
        for (auto &v: a_dfo.reversePost()) {
            cout << v << " ";
        }
        cout << endl << endl;

        cout << "<---- DigraphTopological ---->" << endl;
        auto a_topo = DigraphTopological<std::string>(graph);
        for (auto &v: a_topo.order()) {
            cout << v << " ";
        }
        cout << endl << endl;


        Digraph<int> graph1;
        for (int i = 0; i <= 12; i++) {
            graph1.addVertex(i);
        }

        graph1.addEdge(0, 1)
            .addEdge(0, 5)
            .addEdge(2, 0)
            .addEdge(2, 3)
            .addEdge(3, 2)
            .addEdge(3, 5)
            .addEdge(4, 2)
            .addEdge(4, 3)
            .addEdge(5, 4)
            .addEdge(6, 0)
            .addEdge(6, 4)
            .addEdge(6, 9)
            .addEdge(7, 6)
            .addEdge(7, 8)
            .addEdge(8, 7)
            .addEdge(8, 9)
            .addEdge(9, 10)
            .addEdge(9, 11)
            .addEdge(10, 12)
            .addEdge(11, 4)
            .addEdge(11, 12)
            .addEdge(12, 9);

        cout << "<---- DigraphSCCKosaraju ---->" << endl;
        cout << graph1 << endl;
        cout << "<---- scc ---->" << endl;
        auto a_scc = DigraphSCCKosaraju<int>(graph1);
        for (auto &ccs: a_scc.scc()) {
            for (auto &v: ccs) {
                cout << v << " ";
            }
            cout << endl;
        }
    }
}

#endif //ALGORITHM_DIGRAPH_ALGORITHM_TEST_H
