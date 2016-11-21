//
//  binary_search_tree
//  Algorithm
//
//  Created by dtysky on 16/8/24.
//  Copyright © 2016年 dtysky@outlook.com. All rights reserved.
//

#include <string>
#include "binary_search_tree.h"
#include <iostream>

#include <vector>


namespace data_structures {
    using std::cout;
    using std::endl;
    void testBinarySearchTree(){
        BinarySearchTree<std::string, uint32_t> tree;
        cout << tree.isEmpty() << endl;

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
        tree.del("a");
        cout << tree << endl;
        cout << tree1.isEmpty() << endl;
        tree1.clear();
        cout << tree1 << endl;
        cout << tree1.isEmpty() << endl;
        cout << tree.get("a") << endl;
    }

}