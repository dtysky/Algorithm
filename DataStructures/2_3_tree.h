//
//  2_3_tree
//  Algorithm
//
//  Created by dtysky on 16/11/23.
//  Copyright © 2016 dtysky@outlook.com. All rights reserved.
//

#ifndef ALGORITHM_2_3_TREE_H
#define ALGORITHM_2_3_TREE_H

#include <cstdio>
#include <iostream>
#include "tree_nodes.h"
#include "tree_elements.h"
#include "utils.h"


namespace data_structures {
    template<typename Key, typename Value>
    class TwoThreeTree {
    protected:
        TwoThreeTreeNode<TreeElement<Key, Value>> *_root;
        void _copy(TwoThreeTreeNode<TreeElement<Key, Value>> *node, TwoThreeTreeNode<TreeElement<Key, Value>> *node_src);
        void _clearFromNode(TwoThreeTreeNode<TreeElement<Key, Value>> *node);
        TreeElement<Key, Value> _deleteMinFromNode(TwoThreeTreeNode<TreeElement<Key, Value>> *node);
        TwoThreeTreeNode<TreeElement<Key, Value>> *_find(const Key& key);
        size_t _rankOfNode(TwoThreeTreeNode<TreeElement<Key, Value>> *node);

    public:
        TwoThreeTree();
        TwoThreeTree(TwoThreeTree<Key, Value> &tree);
        virtual ~TwoThreeTree();
        bool isEmpty();
        size_t size();
        TwoThreeTree& clear();
        TwoThreeTree& set(const Key& key, const Value &value);
        Value get(const Key& key);
        Value del(const Key& key);
        Key select(const size_t k);
        size_t rank(const Key& key);
        TwoThreeTree<Key, Value>& operator=(const TwoThreeTree<Key, Value> &tree);
        bool operator==(const TwoThreeTree<Key, Value> &tree);
        bool operator!=(const TwoThreeTree<Key, Value> &tree);
        friend std::ostream &operator<<(std::ostream &out, const TwoThreeTree<Key, Value> &tree) {
            printBinaryTree<TwoThreeTreeNode<TreeElement<Key, Value>>>(tree._root, 8, 0, out);
            return out;
        };
    };
    
}



#endif //ALGORITHM_2_3_TREE_H
