//
//  tree_node
//  Algorithm
//
//  Created by dtysky on 16/9/9.
//  Copyright © 2016 dtysky@outlook.com. All rights reserved.
//

#ifndef ALGORITHM_TREE_NODE_H
#define ALGORITHM_TREE_NODE_H

#include <cstdio>


template <typename T>
class TreeNode {

protected:
    TreeNode* _first_child, _next_sibling;

public:
    T element;
    TreeNode();
    TreeNode(const TreeNode& node);
    ~TreeNode();


};

#endif //ALGORITHM_TREE_NODE_H
