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
//        auto tree = BinarySearchTree<std::string, uint32_t>();
        BinarySearchTree<std::string, uint32_t> tree;
        cout << tree.isEmpty() << endl;

//        BinarySearchTree<std::string, std::string> tree;
//        for (auto key: std::vector<std::string>{"e", "b", "c", "a", "d", "f", "aa", "bb", "cc", "dd", "ee"}) {
//            tree.set(key, key);
//            cout << key << endl;
//            cout << tree << endl;
//        }

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
        cout << tree.select(0) << endl;
        cout << tree.rank(tree.select(0)) << endl;
        cout << tree.select(4) << endl;
        cout << tree.rank(tree.select(4)) << endl;
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