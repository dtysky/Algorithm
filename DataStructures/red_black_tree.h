//
//  red_black_tree
//  Algorithm
//
//  Created by dtysky on 16/11/30.
//  Copyright © 2016 dtysky@outlook.com. All rights reserved.
//

#ifndef ALGORITHM_RED_BLACK_TREE_H
#define ALGORITHM_RED_BLACK_TREE_H

#include <cstdio>
#include <iostream>
#include "tree_element.h"
#include "red_black_tree_node.h"
#include "utils.h"

namespace data_structures {
    template<typename Key, typename Value>
    class RBTree {
    protected:
        RBTreeNode<TreeElement<Key, Value>> *_root;
        void _copy(RBTreeNode<TreeElement<Key, Value>> *node, RBTreeNode<TreeElement<Key, Value>> *node_src);
        void _clearFromNode(RBTreeNode<TreeElement<Key, Value>> *node);
        RBTreeNode<TreeElement<Key, Value>> *_find(const Key& key, const bool withMoving = false);
        RBTreeNode<TreeElement<Key, Value>>*  _deleteMinFromNode(RBTreeNode<TreeElement<Key, Value>> *node);
        size_t _rankOfNode(RBTreeNode<TreeElement<Key, Value>> *node);
        RBTreeNode<TreeElement<Key, Value>>* _leftRotate(RBTreeNode<TreeElement<Key, Value>> *node);
        RBTreeNode<TreeElement<Key, Value>>* _rightRotate(RBTreeNode<TreeElement<Key, Value>> *node);
        bool _flipColors(RBTreeNode<TreeElement<Key, Value>> *node);
        RBTreeNode<TreeElement<Key, Value>>* _leftMove(RBTreeNode<TreeElement<Key, Value>> *node);
        RBTreeNode<TreeElement<Key, Value>>* _rightMove(RBTreeNode<TreeElement<Key, Value>> *node);
        RBTreeNode<TreeElement<Key, Value>>* _balance(RBTreeNode<TreeElement<Key, Value>> *node);

    public:
        RBTree();
        RBTree(RBTree<Key, Value> &tree);
        virtual ~RBTree();
        bool isEmpty();
        size_t size();
        RBTree& clear();
        RBTree& set(const Key& key, const Value &value);
        Value get(const Key& key);
        Value del(const Key& key);
        Key select(const size_t k);
        size_t rank(const Key& key);
        RBTree<Key, Value>& operator=(const RBTree<Key, Value> &tree);
        bool operator==(const RBTree<Key, Value> &tree);
        bool operator!=(const RBTree<Key, Value> &tree);
        friend std::ostream &operator<<(std::ostream &out, const RBTree<Key, Value> &tree) {
            printBinaryTree<RBTreeNode<TreeElement<Key, Value>>>(tree._root, 8, 0, out);
            return out;
        };
    };


    template<typename Key, typename Value> inline
    RBTree<Key, Value>::RBTree() {
        _root = nullptr;
    }

    template<typename Key, typename Value> inline
    RBTree<Key, Value>::RBTree(RBTree<Key, Value> &tree) {
        if (tree._root == nullptr) {
            _root = nullptr;
            return;
        }
        _root = new RBTreeNode<TreeElement<Key, Value>>();
        _copy(_root, tree._root);
    }

    template<typename Key, typename Value> inline
    RBTree<Key, Value>::~RBTree() {
        _clearFromNode(_root);
    }

    template<typename Key, typename Value> inline
    void RBTree<Key, Value>::_copy(RBTreeNode<TreeElement<Key, Value>> *node, RBTreeNode<TreeElement<Key, Value>> *node_src) {
        node->element = node_src->element;
        if (node_src->left() != nullptr) {
            node->insertLeft(new RBTreeNode<TreeElement<Key, Value>>(node_src->left()->element));
            _copy(node->left(), node_src->left());
        }
        if (node_src->right() != nullptr) {
            node->insertRight(new RBTreeNode<TreeElement<Key, Value>>(node_src->right()->element));
            _copy(node->right(), node_src->right());
        }
    }

    template<typename Key, typename Value> inline
    void RBTree<Key, Value>::_clearFromNode(RBTreeNode<TreeElement<Key, Value>> *node){
        if (node == nullptr) {
            return;
        }
        _clearFromNode(node->left());
        _clearFromNode(node->right());
        delete node;
    }

    template <typename Key, typename Value> inline
    RBTree<Key, Value>& RBTree<Key, Value>::operator=(const RBTree<Key, Value>& tree) {
        if (tree._root == nullptr) {
            _root = nullptr;
            return *this;
        }
        _root = new RBTreeNode<TreeElement<Key, Value>>();
        _copy(_root, tree._root);
        return *this;
    }

    template <typename Key, typename Value> inline
    bool RBTree<Key, Value>::operator==(const RBTree<Key, Value>& tree) {
        return _root == tree._root;
    }

    template <typename Key, typename Value> inline
    bool RBTree<Key, Value>::operator!=(const RBTree<Key, Value>& tree) {
        return _root != tree._root;
    }

    template <typename Key, typename Value> inline
    bool RBTree<Key, Value>::isEmpty() {
        return _root == nullptr;
    }

    template <typename Key, typename Value> inline
    RBTree<Key, Value>& RBTree<Key, Value>::clear() {
        _clearFromNode(_root);
        _root = nullptr;
        return *this;
    }

    template <typename Key, typename Value> inline
    size_t RBTree<Key, Value>::size() {
        return _root->node_count;
    }

    template <typename Key, typename Value> inline
    RBTreeNode<TreeElement<Key, Value>>* RBTree<Key, Value>::_leftRotate(RBTreeNode<TreeElement<Key, Value>> *node){
        auto right = node->right();
        auto tmp_node = right->left();
        auto tmp_count = right->node_count;
        right->node_count = node->node_count;
        node->node_count -= tmp_count - (tmp_node != nullptr ? tmp_node->node_count : 0);
        if (node == _root) {
            _root = right;
            _root->initRoot();
        }
        else if (node->isLeft()) {
            node->parent()->insertLeft(right, node->isRed());
        } else {
            node->parent()->insertRight(right, node->isRed());
        }
        right->insertLeft(node, true);
        node->insertRight(tmp_node);
        return right;
    }

    template <typename Key, typename Value> inline
    RBTreeNode<TreeElement<Key, Value>>* RBTree<Key, Value>::_rightRotate(RBTreeNode<TreeElement<Key, Value>> *node){
        auto left = node->left();
        auto tmp_node = left->right();
        auto tmp_count = left->node_count;
        left->node_count = node->node_count;
        node->node_count -= tmp_count - (tmp_node != nullptr ? tmp_node->node_count : 0);
        if (node == _root) {
            _root = left;
            _root->initRoot();
        } else if (node->isLeft()) {
            node->parent()->insertLeft(left, node->isRed());
        } else {
            node->parent()->insertRight(left, node->isRed());
        }
        left->insertRight(node, true);
        node->insertLeft(tmp_node);
        return left;
    }

    template <typename Key, typename Value> inline
    bool RBTree<Key, Value>::_flipColors(RBTreeNode<TreeElement<Key, Value>> *node){
        auto left = node->left();
        auto right = node->right();
        if (left == nullptr || right == nullptr) {
            return false;
        }
        if (!node->isRed() && left->isRed() && right->isRed()) {
            if (node != _root) {
                node->flipColors();
            }
            left->flipColors();
            right->flipColors();
            return true;
        }
        if (node->isRed() && !left->isRed() && !right->isRed()) {
            node->flipColors();
            left->flipColors();
            right->flipColors();
            return true;
        }
        return false;
    }

    template <typename Key, typename Value> inline
    RBTreeNode<TreeElement<Key, Value>>* RBTree<Key, Value>::_leftMove(RBTreeNode<TreeElement<Key, Value>> *node){
        if (!node->isRed()) {
            return node;
        }
        if (!_flipColors(node)) {
            return node;
        }
        // if node is red, left and right are not red
        auto right = node->right();
        if (right->left() == nullptr || !right->left()->isRed()) {
            return node;
        }
        _rightRotate(right);
        node = _leftRotate(node);
        _flipColors(node);
        return node;
    }

    template <typename Key, typename Value> inline
    RBTreeNode<TreeElement<Key, Value>>* RBTree<Key, Value>::_rightMove(RBTreeNode<TreeElement<Key, Value>> *node){
        if (!node->isRed()) {
            return node;
        }
        if (!_flipColors(node)) {
            return node;
        }
        // if node is red, left and right are not red
        auto left = node->left();
        if (left->left() == nullptr || !left->left()->isRed()) {
            return node;
        }
        _rightRotate(left);
        node = _rightRotate(node);
        _flipColors(node);
        return node;
    }

    template <typename Key, typename Value> inline
    RBTreeNode<TreeElement<Key, Value>>* RBTree<Key, Value>::_balance(RBTreeNode<TreeElement<Key, Value>> *node){
        auto left = node->left();
        auto right = node->right();
        if (right != nullptr && right->isRed()) {
            if (left != nullptr && left->isRed()) {
                _flipColors(node);
            } else {
                node = _leftRotate(node);
            }
        }
        if (
            (left != nullptr && left->left() != nullptr)
            && (left->isRed() && left->left()->isRed())
            ) {
            node = _rightRotate(node);
            _flipColors(node);
        }
        return node;
    }

    template<typename Key, typename Value> inline
    RBTree<Key, Value>& RBTree<Key, Value>::set(const Key &key, const Value &value){
        if (isEmpty()) {
            _root = new RBTreeNode<TreeElement<Key, Value>>(TreeElement<Key, Value>(key, value));
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
        node = new RBTreeNode<TreeElement<Key, Value>>(TreeElement<Key, Value>(key, value));
        if (key < parent->element.key) {
            parent->insertLeft(node, true);
        } else {
            parent->insertRight(node, true);
        }
        while (parent != nullptr) {
            parent->node_count++;
            parent = _balance(parent)->parent();
        }
        return *this;
    }

    template<typename Key, typename Value> inline
    RBTreeNode<TreeElement<Key, Value>>* RBTree<Key, Value>::_find(const Key& key, const bool withMoving) {
        RBTreeNode<TreeElement<Key, Value>>* node = _root;
        while (node != nullptr) {
            if (node->element.key == key) {
                return node;
            }
            if (key < node->element.key) {
                if (withMoving) {
                    node = _leftMove(node);
                }
                node = node->left();
            } else {
                if (withMoving) {
                    node = _rightMove(node);
                }
                node = node->right();
            }
        }
        throw std::out_of_range("Key error, no such key in this tree !");
    }

    template<typename Key, typename Value> inline
    Value RBTree<Key, Value>::get(const Key &key) {
        auto node = _find(key);
        return node->element.value;
    }

    template<typename Key, typename Value> inline
    RBTreeNode<TreeElement<Key, Value>>*  RBTree<Key, Value>::_deleteMinFromNode(RBTreeNode<TreeElement<Key, Value>> *node){
        RBTreeNode<TreeElement<Key, Value>>* min_node = node;
        while (min_node->left() != nullptr) {
            min_node = _leftMove(min_node);
            min_node = min_node->left();
        }
        auto parent = min_node->parent();
        if (min_node->isLeft()) {
            parent->deleteLeft();
        } else {
            parent->deleteRight();
        }
        return min_node;
    }

    template<typename Key, typename Value> inline
    Value RBTree<Key, Value>::del(const Key &key) {
        _root->flipColors();
        auto node = _find(key, true);
        auto parent = node->parent();
        auto result = node->element.value;
        if (node->left() == nullptr || node->right() == nullptr) {
//            if (node == _root && size() == 1) {
//                if (size() == 1) {
//                    _root = nullptr;
//                } else if (node->left() == nullptr) {
//                    _root = node->left();
//                    _root->initRoot();
//                } else {
//                    _root = node->right();
//                    _root->initRoot();
//                }
//                delete node;
//                return result;
//            }
            if (!node->isRed()) {
                node = _rightRotate(node);
            }
            if (node->isLeft()) {
                node->parent()->deleteLeft();
            } else {
                node->parent()->deleteRight();
            }
            delete node;
        } else {
            node = _rightMove(node);
            auto min_node = _deleteMinFromNode(node->right());
            node->element = min_node->element;
            parent = min_node->parent();
            delete min_node;
        }
//        printBinaryTree<RBTreeNode<TreeElement<Key, Value>>>(_root, 8, 0, std::cout);
        while (parent != nullptr) {
            parent->node_count--;
            parent = _balance(parent)->parent();
        }
        return result;

    }

    template <typename Key, typename Value> inline
    size_t RBTree<Key, Value>::_rankOfNode(RBTreeNode<TreeElement<Key, Value>> *node){
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
                r ++;
            }
            pre_node = current_node;
            current_node = current_node->parent();
        }
        return r;
    }

    template<typename Key, typename Value> inline
    Key RBTree<Key, Value>::select(const size_t k) {
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
    size_t RBTree<Key, Value>::rank(const Key &key){
        auto node = _find(key);
        return _rankOfNode(node);
    }
}


#endif //ALGORITHM_RED_BLACK_TREE_H
