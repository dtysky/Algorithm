//
//  binary_search_tree
//  Algorithm
//
//  Created by dtysky on 16/10/19.
//  Copyright © 2016 dtysky@outlook.com. All rights reserved.
//

#ifndef ALGORITHM_SEARCH_BINARY_HEAP_H
#define ALGORITHM_SEARCH_BINARY_HEAP_H

#include <cstdio>
#include <iostream>
#include <iomanip>
#include "utils.h"
#include "binary_tree_node.h"
#include "tree_element.h"


namespace data_structures {
    template<typename Key, typename Value>
    class BinarySearchTree {
    protected:
        BinaryTreeNode<TreeElement<Key, Value>> *_root;
        void _copy(BinaryTreeNode<TreeElement<Key, Value>> *node, BinaryTreeNode<TreeElement<Key, Value>> *node_src);
        void _clearFromNode(BinaryTreeNode<TreeElement<Key, Value>> *node);
        BinaryTreeNode<TreeElement<Key, Value>> *_deleteMinFromNode(BinaryTreeNode<TreeElement<Key, Value>> *node);
        BinaryTreeNode<TreeElement<Key, Value>> *_find(const Key& key);
        size_t _rankOfNode(BinaryTreeNode<TreeElement<Key, Value>> *node);

    public:
        BinarySearchTree();
        BinarySearchTree(BinarySearchTree<Key, Value> &tree);
        virtual ~BinarySearchTree();
        bool isEmpty();
        size_t size();
        BinarySearchTree& clear();
        BinarySearchTree& set(const Key& key, const Value &value);
        Value get(const Key& key);
        Value del(const Key& key);
        Key select(const size_t k);
        size_t rank(const Key& key);
        BinarySearchTree<Key, Value>& operator=(const BinarySearchTree<Key, Value> &tree);
        bool operator==(const BinarySearchTree<Key, Value> &tree);
        bool operator!=(const BinarySearchTree<Key, Value> &tree);
        friend std::ostream &operator<<(std::ostream &out, const BinarySearchTree<Key, Value> &tree) {
            printBinaryTree<BinaryTreeNode<TreeElement<Key, Value>>>(tree._root, 8, 0, out);
            return out;
        };
    };


    template<typename Key, typename Value> inline
    BinarySearchTree<Key, Value>::BinarySearchTree() {
        _root = nullptr;
    }

    template<typename Key, typename Value> inline
    BinarySearchTree<Key, Value>::BinarySearchTree(BinarySearchTree<Key, Value> &tree) {
        if (tree._root == nullptr) {
            _root = nullptr;
            return;
        }
        _root = new BinaryTreeNode<TreeElement<Key, Value>>();
        _copy(_root, tree._root);
    }

    template<typename Key, typename Value> inline
    BinarySearchTree<Key, Value>::~BinarySearchTree() {
        _clearFromNode(_root);
    }

    template<typename Key, typename Value> inline
    void BinarySearchTree<Key, Value>::_copy(BinaryTreeNode<TreeElement<Key, Value>> *node, BinaryTreeNode<TreeElement<Key, Value>> *node_src) {
        node->element = node_src->element;
        if (node_src->left() != nullptr) {
            node->insertLeft(new BinaryTreeNode<TreeElement<Key, Value>>(node_src->left()->element));
            _copy(node->left(), node_src->left());
        }
        if (node_src->right() != nullptr) {
            node->insertRight(new BinaryTreeNode<TreeElement<Key, Value>>(node_src->right()->element));
            _copy(node->right(), node_src->right());
        }
    }

    template<typename Key, typename Value> inline
    void BinarySearchTree<Key, Value>::_clearFromNode(BinaryTreeNode<TreeElement<Key, Value>> *node){
        if (node == nullptr) {
            return;
        }
        _clearFromNode(node->left());
        _clearFromNode(node->right());
        delete node;
    }

    template <typename Key, typename Value> inline
    BinarySearchTree<Key, Value>& BinarySearchTree<Key, Value>::operator=(const BinarySearchTree<Key, Value>& tree) {
        if (tree._root == nullptr) {
            _root = nullptr;
            return *this;
        }
        _root = new BinaryTreeNode<TreeElement<Key, Value>>();
        _copy(_root, tree._root);
        return *this;
    }

    /*---------------- todo: waiting for correcting ----------------*/
    template <typename Key, typename Value> inline
    bool BinarySearchTree<Key, Value>::operator==(const BinarySearchTree<Key, Value>& tree) {
        return _root == tree._root;
    }

    /*---------------- todo: waiting for correcting ----------------*/
    template <typename Key, typename Value> inline
    bool BinarySearchTree<Key, Value>::operator!=(const BinarySearchTree<Key, Value>& tree) {
        return _root != tree._root;
    }

    template <typename Key, typename Value> inline
    bool BinarySearchTree<Key, Value>::isEmpty() {
        return _root == nullptr;
    }

    template <typename Key, typename Value> inline
    BinarySearchTree<Key, Value>& BinarySearchTree<Key, Value>::clear() {
        _clearFromNode(_root);
        _root = nullptr;
        return *this;
    }

    template <typename Key, typename Value> inline
    size_t BinarySearchTree<Key, Value>::size() {
        return _root->node_count;
    }

    template<typename Key, typename Value> inline
    BinarySearchTree<Key, Value>& BinarySearchTree<Key, Value>::set(const Key &key, const Value &value){
        if (isEmpty()) {
            _root = new BinaryTreeNode<TreeElement<Key, Value>>(TreeElement<Key, Value>(key, value));
            return *this;
        }
        auto node = _root;
        auto parent = _root->parent();
        while (node != nullptr) {
            if (node->element.key == key) {
                node->element.value = value;
                return *this;
            }
            parent = node;
            if (key < node->element.key) {
                node = node->left();
            } else {
                node = node->right();
            }
        }
        node = new BinaryTreeNode<TreeElement<Key, Value>>(TreeElement<Key, Value>(key, value));
        if (key < parent->element.key) {
            parent->insertLeft(node);
        } else {
            parent->insertRight(node);
        }
        while (parent != nullptr) {
            parent->node_count++;
            parent = parent->parent();
        }
        return *this;
    }

    template<typename Key, typename Value> inline
    BinaryTreeNode<TreeElement<Key, Value>>* BinarySearchTree<Key, Value>::_find(const Key& key) {
        BinaryTreeNode<TreeElement<Key, Value>>* node = _root;
        while (node != nullptr) {
            if (node->element.key == key) {
                return node;
            }
            if (key < node->element.key) {
                node = node->left();
            } else {
                node = node->right();
            }
        }
        throw std::out_of_range("Key error, no such key in this tree !");
    }

    template<typename Key, typename Value> inline
    Value BinarySearchTree<Key, Value>::get(const Key &key) {
        auto node = _find(key);
        return node->element.value;
    }

    template<typename Key, typename Value> inline
    BinaryTreeNode<TreeElement<Key, Value>>* BinarySearchTree<Key, Value>::_deleteMinFromNode(BinaryTreeNode<TreeElement<Key, Value>> *node){
        BinaryTreeNode<TreeElement<Key, Value>>* min_node = node;
        while (min_node->left() != nullptr) {
            min_node = min_node->left();
        }
        auto parent = min_node->parent();
        auto new_min_node = min_node->right();
        if (min_node->isLeft()) {
            parent->deleteLeft();
            parent->insertLeft(new_min_node);
        } else {
            parent->deleteRight();
            parent->insertRight(new_min_node);
        }
        return min_node;
    }

    template<typename Key, typename Value> inline
    Value BinarySearchTree<Key, Value>::del(const Key &key) {
        auto node = _find(key);
        auto parent = node->parent();
        auto result = node->element.value;
        auto new_node = node->left();
        if (node->left() == nullptr) {
            new_node = node->right();
        }
        if (node->left() == nullptr || node->right() == nullptr) {
            if (node->isLeft()) {
                node->parent()->deleteLeft();
                node->parent()->insertLeft(new_node);
            } else {
                node->parent()->deleteRight();
                node->parent()->insertRight(new_node);
            }
            delete node;
        } else {
            auto min_node = _deleteMinFromNode(node->right());
            node->element = min_node->element;
            parent = min_node->parent();
            delete min_node;
        }
        while (parent != nullptr) {
            parent->node_count--;
            parent = parent->parent();
        }
        return result;
    }

    template <typename Key, typename Value> inline
    size_t BinarySearchTree<Key, Value>::_rankOfNode(BinaryTreeNode<TreeElement<Key, Value>> *node){
        size_t r = 0;
        if (node->left()) {
            r = node->left()->node_count;
        }
        auto current_node = node;
        auto pre_node = node->left();
        while (current_node != nullptr) {
            if (current_node->left() && current_node->left() != pre_node) {
                r += current_node->left()->node_count + 1;
            } else if (pre_node && !pre_node->isLeft()) {
                r++;
            }
            pre_node = current_node;
            current_node = current_node->parent();
        }
        return r;
    }

    template<typename Key, typename Value> inline
    Key BinarySearchTree<Key, Value>::select(const size_t k) {
        if (isEmpty()) {
            throw std::out_of_range("Index error, k is out of range !");
        }
        if (size() < k) {
            throw std::out_of_range("Index error, k is out of range !");
        }
        auto node = _root;
        auto r = _rankOfNode(node);
        while (r != k) {
            if (k < r) {
                node = node->left();
            } else {
                node = node->right();
            }
            r = _rankOfNode(node);
        }
        return node->element.key;
    }

    template<typename Key, typename Value> inline
    size_t BinarySearchTree<Key, Value>::rank(const Key &key){
        auto node = _find(key);
        return _rankOfNode(node);
    }
};


#endif //ALGORITHM_SEARCH_BINARY_HEAP_H
