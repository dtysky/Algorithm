//
//  red_black_tree
//  Algorithm
//
//  Created by dtysky on 16/12/4.
//  Copyright © 2016 dtysky@outlook.com. All rights reserved.
//

#include <string>
#include "red_black_tree.h"
#include <iostream>
#include <vector>


namespace data_structures {
    using std::cout;
    using std::endl;

    void testRBTree() {
        RBTree<std::string, uint32_t> tree;
//        RBTree<std::string, std::string> tree;
        cout << tree.isEmpty() << endl;

//        for (auto key: std::vector<std::string>{"e", "b", "c", "a", "d", "f", "aa", "bb", "cc", "dd", "ee"}) {
//            cout << key << ":" << endl << tree.set(key, key) << endl;
//        }
//
        tree.set("e", 0)
            .set("b", 1)
            .set("c", 2)
            .set("a", 3)
            .set("d", 4)
            .set("f", 5)
            .set("aa", 12)
            .set("bb", 32)
            .set("cc", 2231)
            .set("dd", 4233)
            .set("ee", 444);
        cout << tree << endl;
        cout << tree.size() << endl;
        cout << tree.get("a") << endl;
        tree.set("a", 334);
        cout << tree.get("a") << endl;

        for (auto key: std::vector<std::string>{"a", "b", "c", "d", "e", "f", "aa", "bb", "cc", "dd", "ee"}) {
            cout << key << " " << tree.rank(key) << endl;
        }

        for (auto rank: std::vector<size_t>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10}) {
            cout << rank << " " << tree.select(rank) << endl;
        }

        auto tree1 = tree;
        cout << (tree == tree1) << endl;

        for (auto key: std::vector<std::string>{"a", "b", "c", "d", "e", "f", "aa", "bb", "cc", "dd", "ee"}) {
            cout << "key, value: " << endl << key << ", " << tree.del(key) << endl;
            cout << "tree:" << endl << tree << endl;
        }

        cout << tree << endl;
        cout << tree1.isEmpty() << endl;
        tree1.clear();
        cout << tree1 << endl;
        cout << tree1.isEmpty() << endl;
        cout << tree.get("a") << endl;
    }
}
