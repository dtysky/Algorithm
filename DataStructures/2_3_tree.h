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
        void _deleteEmptyNode(TwoThreeTreeNode<TreeElement<Key, Value>> *node);
        TwoThreeTreeNode<TreeElement<Key, Value>> *_find(const Key& key);

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
        TwoThreeTree<Key, Value>& operator=(const TwoThreeTree<Key, Value> &tree);
        bool operator==(const TwoThreeTree<Key, Value> &tree);
        bool operator!=(const TwoThreeTree<Key, Value> &tree);
        friend std::ostream &operator<<(std::ostream &out, const TwoThreeTree<Key, Value> &tree) {
//            printBinaryTree<TwoThreeTreeNode<TreeElement<Key, Value>>>(tree._root, 8, 0, out);
            return out;
        };
    };

    template<typename Key, typename Value> inline
    TwoThreeTree<Key, Value>::TwoThreeTree() {
        _root = nullptr;
    }

    template<typename Key, typename Value> inline
    TwoThreeTree<Key, Value>::TwoThreeTree(TwoThreeTree<Key, Value> &tree) {
        if (tree._root == nullptr) {
            _root = nullptr;
            return;
        }
        _root = new TwoThreeTreeNode<TreeElement<Key, Value>>();
        _copy(_root, tree._root);
    }

    template<typename Key, typename Value> inline
    TwoThreeTree<Key, Value>::~TwoThreeTree() {
        _clearFromNode(_root);
    }

    template<typename Key, typename Value> inline
    void TwoThreeTree<Key, Value>::_copy(TwoThreeTreeNode<TreeElement<Key, Value>> *node, TwoThreeTreeNode<TreeElement<Key, Value>> *node_src) {
        if (node->type != node_src->type) {
            throw std::out_of_range("Type error, source node's type is different from dist !");
        }
        node->elements = node_src->elements;
        for (size_t i = 0; i <= node_src->type ; i++) {
            node->insertChild(i, new TwoThreeTreeNode<TreeElement<Key, Value>>(node_src->child(i)->elements, node_src->type));
            _copy(node->child(i), node_src->child(i));
        }
    }

    template<typename Key, typename Value> inline
    void TwoThreeTree<Key, Value>::_clearFromNode(TwoThreeTreeNode<TreeElement<Key, Value>> *node){
        if (node == nullptr) {
            return;
        }
        for (size_t i = 0; i <= node->type ; i++) {
            _clearFromNode(node->child(i));
        }
        delete node;
    }

    template <typename Key, typename Value> inline
    TwoThreeTree<Key, Value>& TwoThreeTree<Key, Value>::operator=(const TwoThreeTree<Key, Value>& tree) {
        if (tree._root == nullptr) {
            _root = nullptr;
            return *this;
        }
        _root = new TwoThreeTreeNode<TreeElement<Key, Value>>();
        _copy(_root, tree._root);
        return *this;
    }

    template <typename Key, typename Value> inline
    bool TwoThreeTree<Key, Value>::operator==(const TwoThreeTree<Key, Value>& tree) {
        return _root == tree._root;
    }

    template <typename Key, typename Value> inline
    bool TwoThreeTree<Key, Value>::operator!=(const TwoThreeTree<Key, Value>& tree) {
        return _root != tree._root;
    }

    template <typename Key, typename Value> inline
    bool TwoThreeTree<Key, Value>::isEmpty() {
        return _root == nullptr;
    }

    template <typename Key, typename Value> inline
    TwoThreeTree<Key, Value>& TwoThreeTree<Key, Value>::clear() {
        _clearFromNode(_root);
        _root = nullptr;
        return *this;
    }

    template <typename Key, typename Value> inline
    size_t TwoThreeTree<Key, Value>::size() {
        return _root->node_count;
    }

    template<typename Key, typename Value> inline
    TwoThreeTreeNode<TreeElement<Key, Value>>* TwoThreeTree<Key, Value>::_find(const Key& key) {
        TwoThreeTreeNode<TreeElement<Key, Value>>* node = _root;
        TwoThreeTreeNode<TreeElement<Key, Value>>* tmp_node;
        TreeElement<Key, Value> element;
        while (node != nullptr) {
            tmp_node = node;
            for (size_t i = 0; i < node->type; i++) {
                element = node->getElement(i);
                if (key == element.key) {
                    return node;
                }
                if (key < element.key) {
                    node = node->child(i);
                    continue;
                }
            }
            if (node == tmp_node && key > element.key) {
                node = node->child(node->type);
            }
        }
        throw std::out_of_range("Key error, no such key in this tree !");
    }

    template<typename Key, typename Value> inline
    TwoThreeTree<Key, Value>& TwoThreeTree<Key, Value>::set(const Key &key, const Value &value){
        if (isEmpty()) {
            _root = new TwoThreeTreeNode<TreeElement<Key, Value>>(TreeElement<Key, Value>(key, value));
            return *this;
        }
        auto node = _root;
        auto tmp_node = node;
        auto parent = _root->parent();
        TreeElement<Key, Value> element;
        while (node != nullptr) {
            tmp_node = node;
            parent = node->parent();
            for (size_t i = 0; i < node->type; i++) {
                element = node->getElement(i);
                if (key == element.key) {
                    node->setElement(i, value);
                    return *this;
                }
                if (key < element.key) {
                    node = node->child(i);
                    continue;
                }
            }
            if (node == tmp_node && key > element.key) {
                node = node->child(node->type);
            }
        }
        if (parent->type == 1) {
            parent->type1to2(TreeElement<Key, Value>(key, value));
            return *this;
        }
        if (parent->type == 2 && parent == _root) {
            parent->type2to3(TreeElement<Key, Value>(key, value));
            parent->expandRoot();
            return *this;
        }
        if (parent->type == 2) {
            parent->type2to3(TreeElement<Key, Value>(key, value));
            while (parent->expand()->type == 2) {
                parent = parent->parent();
                if (parent == _root) {
                    parent->expandRoot();
                    return *this;
                }
            }
        }
        return *this;
    }

    template <typename Key, typename Value> inline
    Value TwoThreeTree<Key, Value>::get(const Key &key) {
        auto node = _find(key);
        TreeElement<Key, Value> element;
        for (size_t i = 0; i < node->type; i++) {
            element = node->getElement(i);
            if (key == element.key) {
                return element.value;
            }
        }
    }

    template <typename Key, typename Value> inline
    void TwoThreeTree<Key, Value>::_deleteEmptyNode(TwoThreeTreeNode<TreeElement<Key, Value>> *node){
        auto parent = node->parent();
        auto node_index = node->getIndex();
        if (node == _root) {
            _root = _root->child(0);
            delete node;
            return;
        }
        if (parent->type == 2) {
            if (node_index == 0) {
                auto brother = parent->child(1);
                if (brother->type == 1) {
                    brother->type1to2(parent->getElement(0));
                    brother->insertChild(0, node->child(0));
                    delete parent->type2to1(0, 0);
                } else if (brother->type == 2) {
                    node->type0to1(parent->getElement(0));
                    node->insertChild(1, brother->child(0));
                    parent->setElement(0, brother->getElement(0));
                    delete brother->type2to1(0, 1);
                }
                return;
            }
            if (node_index == 1) {
                auto brother = parent->child(2);
                if (brother->type == 1) {
                    brother->type1to2(parent->getElement(1));
                    brother->insertChild(0, node->child(0));
                    delete parent->type2to1(1, 1);
                } else if (brother->type == 2) {
                    node->type0to1(parent->getElement(1));
                    node->insertChild(1, brother->child(0));
                    parent->setElement(1, brother->getElement(0));
                    delete brother->type2to1(1, 2);
                }
                return;
            }
            if (node_index == 2) {
                auto brother = parent->child(2);
                if (brother->type == 1) {
                    brother->type1to2(parent->getElement(1));
                    brother->insertChild(1, node->child(0));
                    delete parent->type2to1(2, 1);
                } else if (brother->type == 2) {
                    node->type0to1(parent->getElement(1));
                    node->insertChild(0, brother->child(2));
                    parent->setElement(1, brother->getElement(1));
                    delete brother->type2to1(1, 2);
                }
                return;
            }
        }
        if (parent->type == 1) {

            if (node_index == 0) {
                auto brother = parent->child(1);
                if (brother->type == 1) {
                    brother->type1to2(parent->getElement(0));
                    brother->insertChild(0, node->child(0));
                    delete parent->type1to0(0);
                } else if (brother->type == 2) {
                    node->type0to1(parent->getElement(0));
                    node->insertChild(1, brother->child(0));
                    parent->setElement(0, brother->getElement(0));
                    brother->type2to1(0, 0);
                    return;
                }
            } else if (node_index == 1) {
                auto brother = parent->child(1);
                if (brother->type == 1) {
                    brother->type1to2(parent->getElement(0));
                    brother->insertChild(1, node->child(0));
                    delete parent->type1to0(0);
                } else if (brother->type == 2) {
                    node->type0to1(parent->getElement(0));
                    node->insertChild(0, brother->child(2));
                    parent->setElement(0, brother->getElement(1));
                    brother->type2to1(1, 2);
                    return;
                }
            }
            _deleteEmptyNode(parent);
        }
    }

    template <typename Key, typename Value> inline
    Value TwoThreeTree<Key, Value>::del(const Key &key){
        auto node = _find(key);
        Value result;
        size_t index = 0;
        for (size_t i = 0; i < node->type; i++) {
            if (node->elements[i].key == key) {
                index = i;
                result = node->elements[i].value;
            }
        }
        if (!node->isLeaf()) {
            auto tmp_node = node->child(index);
            while (!tmp_node->isLeaf()) {
                tmp_node = tmp_node->child(0);
            }
            node->setElement(index, tmp_node->getElement(0));
            node = tmp_node;
            index = 0;
        }
        if (node->type == 2) {
            // leaf node has no child
            node->type2to1(index, 0);
            return result;
        }
        node->type1to0(0);
        _deleteEmptyNode(node);
        return result;
    }
    
}



#endif //ALGORITHM_2_3_TREE_H
