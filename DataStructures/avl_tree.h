//
//  avl_tree
//  Algorithm
//
//  Created by dtysky on 16/12/7.
//  Copyright © 2016 dtysky@outlook.com. All rights reserved.
//

#ifndef ALGORITHM_AVL_TREE_H
#define ALGORITHM_AVL_TREE_H

#include <cstdio>
#include <iostream>
#include "tree_element.h"
#include "binary_tree_node.h"
#include "utils.h"

namespace data_structures {
    template<typename Key, typename Value>
    class AVLTree {
    protected:
        BinaryTreeNode<TreeElement<Key, Value>> *_root;
        void _copy(BinaryTreeNode<TreeElement<Key, Value>> *node, BinaryTreeNode<TreeElement<Key, Value>> *node_src);
        void _clearFromNode(BinaryTreeNode<TreeElement<Key, Value>> *node);
        BinaryTreeNode<TreeElement<Key, Value>> *_find(const Key& key);
        BinaryTreeNode<TreeElement<Key, Value>>*  _deleteMinFromNode(BinaryTreeNode<TreeElement<Key, Value>> *node);
        size_t _rankOfNode(BinaryTreeNode<TreeElement<Key, Value>> *node);
        BinaryTreeNode<TreeElement<Key, Value>>* _llRotate(BinaryTreeNode<TreeElement<Key, Value>> *node);
        BinaryTreeNode<TreeElement<Key, Value>>* _rrRotate(BinaryTreeNode<TreeElement<Key, Value>> *node);
        BinaryTreeNode<TreeElement<Key, Value>>* _lrRotate(BinaryTreeNode<TreeElement<Key, Value>> *node);
        BinaryTreeNode<TreeElement<Key, Value>>* _rlRotate(BinaryTreeNode<TreeElement<Key, Value>> *node);
        void _balance(BinaryTreeNode<TreeElement<Key, Value>> *node);
        int _balanceFactor(BinaryTreeNode<TreeElement<Key, Value>> *node);
        void _reBalanceFactor(BinaryTreeNode<TreeElement<Key, Value>> *node, const int factor, const bool insertion = false);

    public:
        AVLTree();
        AVLTree(AVLTree<Key, Value> &tree);
        virtual ~AVLTree();
        bool isEmpty();
        size_t size();
        AVLTree& clear();
        AVLTree& set(const Key& key, const Value &value);
        Value get(const Key& key);
        Value del(const Key& key);
        Key select(const size_t k);
        size_t rank(const Key& key);
        AVLTree<Key, Value>& operator=(const AVLTree<Key, Value> &tree);
        bool operator==(const AVLTree<Key, Value> &tree);
        bool operator!=(const AVLTree<Key, Value> &tree);
        friend std::ostream &operator<<(std::ostream &out, const AVLTree<Key, Value> &tree) {
            printBinaryTree<BinaryTreeNode<TreeElement<Key, Value>>>(tree._root, 8, 0, out);
            return out;
        };
    };


    template<typename Key, typename Value> inline
    AVLTree<Key, Value>::AVLTree() {
        _root = nullptr;
    }

    template<typename Key, typename Value> inline
    AVLTree<Key, Value>::AVLTree(AVLTree<Key, Value> &tree) {
        if (tree._root == nullptr) {
            _root = nullptr;
            return;
        }
        _root = new BinaryTreeNode<TreeElement<Key, Value>>();
        _copy(_root, tree._root);
    }

    template<typename Key, typename Value> inline
    AVLTree<Key, Value>::~AVLTree() {
        _clearFromNode(_root);
    }

    template<typename Key, typename Value> inline
    void AVLTree<Key, Value>::_copy(BinaryTreeNode<TreeElement<Key, Value>> *node, BinaryTreeNode<TreeElement<Key, Value>> *node_src) {
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
    void AVLTree<Key, Value>::_clearFromNode(BinaryTreeNode<TreeElement<Key, Value>> *node){
        if (node == nullptr) {
            return;
        }
        _clearFromNode(node->left());
        _clearFromNode(node->right());
        delete node;
    }

    template <typename Key, typename Value> inline
    AVLTree<Key, Value>& AVLTree<Key, Value>::operator=(const AVLTree<Key, Value>& tree) {
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
    bool AVLTree<Key, Value>::operator==(const AVLTree<Key, Value>& tree) {
        return _root == tree._root;
    }

    /*---------------- todo: waiting for correcting ----------------*/
    template <typename Key, typename Value> inline
    bool AVLTree<Key, Value>::operator!=(const AVLTree<Key, Value>& tree) {
        return _root != tree._root;
    }

    template <typename Key, typename Value> inline
    bool AVLTree<Key, Value>::isEmpty() {
        return _root == nullptr;
    }

    template <typename Key, typename Value> inline
    AVLTree<Key, Value>& AVLTree<Key, Value>::clear() {
        _clearFromNode(_root);
        _root = nullptr;
        return *this;
    }

    template <typename Key, typename Value> inline
    size_t AVLTree<Key, Value>::size() {
        return _root == nullptr ? 0 : _root->node_count;
    }

    template <typename Key, typename Value> inline
    int AVLTree<Key, Value>::_balanceFactor(BinaryTreeNode<TreeElement<Key, Value>> *node){
        return node == nullptr ? -1 : node->b_factor;
    }

    template <typename Key, typename Value> inline
    void AVLTree<Key, Value>::_reBalanceFactor(BinaryTreeNode<TreeElement<Key, Value>> *node, const int factor, const bool insertion){
        auto parent = node->parent();
        auto is_left = node->isLeft();
        while (parent != nullptr) {
            auto org_factor = parent->b_factor;
            if (is_left) {
                parent->b_factor += factor;
            } else {
                parent->b_factor -= factor;
            }
            if (insertion) {
                if (!(is_left && org_factor >= 0 || !is_left && org_factor <= 0)) {
                    break;
                }
            } else {
                if (!(is_left && org_factor > 0 || !is_left && org_factor < 0)) {
                    break;
                }
            }
            is_left = parent->isLeft();
            parent = parent->parent();
        }
    }

    // use the node's right-child to instead of itself,
    // then make itself as its right-child's left-child,
    // at last, insert its right-child's left-child to its right
    template <typename Key, typename Value> inline
    BinaryTreeNode<TreeElement<Key, Value>>* AVLTree<Key, Value>::_rrRotate(
        BinaryTreeNode<TreeElement<Key, Value>> *node){
        auto right = node->right();
        auto tmp_node = right->left();

        // use the node's count to instead of right-child's and:
        // right-child's count = left child's count + right-child's left-child's count
        auto tmp_count = right->node_count;
        right->node_count = node->node_count;
        node->node_count -= tmp_count - (tmp_node != nullptr ? tmp_node->node_count : 0);

        // max(abs(left-child's max-height - right-child's max-height)) = 1
        right->b_factor = node->b_factor + 2;
        node->b_factor = _balanceFactor(node->left()) - _balanceFactor(right->left());

        if (node == _root) {
            _root = right;
            _root->initRoot();
        }
        else if (node->isLeft()) {
            node->parent()->insertLeft(right);
        } else {
            node->parent()->insertRight(right);
        }
        right->insertLeft(node);
        node->insertRight(tmp_node);

        // height reduction of one
        if (right->b_factor == 0) {
            _reBalanceFactor(right, -1);
        }

        return right;
    }


    // use the node's left-child to instead of itself,
    // then make itself as its left-child's right-child,
    // at last, insert its left-child's right-child to its left
    template <typename Key, typename Value> inline
    BinaryTreeNode<TreeElement<Key, Value>>* AVLTree<Key, Value>::_llRotate(
        BinaryTreeNode<TreeElement<Key, Value>> *node){
        auto left = node->left();
        auto tmp_node = left->right();

        // use the node's count to instead of left-child's and:
        // left-child's count = right-child's count + left-child's right-child's count
        auto tmp_count = left->node_count;
        left->node_count = node->node_count;
        node->node_count -= tmp_count - (tmp_node != nullptr ? tmp_node->node_count : 0);

        // max(abs(left-child's max-height - right-child's max-height)) = 1
        left->b_factor = node->b_factor - 2;
        node->b_factor = _balanceFactor(node->right()) - _balanceFactor(left->right());

        if (node == _root) {
            _root = left;
            _root->initRoot();
        } else if (node->isLeft()) {
            node->parent()->insertLeft(left);
        } else {
            node->parent()->insertRight(left);
        }
        left->insertRight(node);
        node->insertLeft(tmp_node);
        // height reduction of one
        if (left->b_factor == 0) {
            _reBalanceFactor(left, -1);
        }

        return left;
    }

    // right-rotate node's right-child and left-rotate itself
    template <typename Key, typename Value> inline
    BinaryTreeNode<TreeElement<Key, Value>>* AVLTree<Key, Value>::_rlRotate(
        BinaryTreeNode<TreeElement<Key, Value>> *node){
        auto right = node->right();
        _llRotate(right);
        node = _rrRotate(node);
        return node;
    }

    // left-rotate node's left-child and right-rotate itself
    template <typename Key, typename Value> inline
    BinaryTreeNode<TreeElement<Key, Value>>* AVLTree<Key, Value>::_lrRotate(
        BinaryTreeNode<TreeElement<Key, Value>> *node){
        // if node is red, left and right nodes are not red
        auto left = node->left();
        _rrRotate(left);
        node = _llRotate(node);
        return node;
    }

    template <typename Key, typename Value> inline
    void AVLTree<Key, Value>::_balance(BinaryTreeNode<TreeElement<Key, Value>> *node){
        auto left = node->left();
        auto right = node->right();
        if (left == nullptr && right == nullptr) {
            return;
        }
        if (left != nullptr && left->node_count == 1) {
            return;
        }
        if (right != nullptr && right->node_count == 1) {
            return;
        }
        if (_balanceFactor(node) == 2) {
            if (_balanceFactor(left) > 0) {
                node = _llRotate(node);
            } else {
                node = _lrRotate(node);
            }
        } else if (_balanceFactor(node) == -2) {
            if (_balanceFactor(right) < 0) {
                node = _rrRotate(node);
            } else {
                node = _rlRotate(node);
            }
        }
        _balance(node->left());
        _balance(node->right());
    }

    template<typename Key, typename Value> inline
    AVLTree<Key, Value>& AVLTree<Key, Value>::set(const Key &key, const Value &value){
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
        // insert to a new line: 1
        if (parent->node_count == 1) {
            _reBalanceFactor(node, 1, true);
        }
        // insert to a old line
        else {
            parent->b_factor = 0;
        }
        while (parent != nullptr) {
            parent->node_count++;
            parent = parent->parent();
        }
        _balance(_root);
        return *this;
    }

    // withMoving is used for finding a node witch is prepared to delete
    template<typename Key, typename Value> inline
    BinaryTreeNode<TreeElement<Key, Value>>* AVLTree<Key, Value>::_find(const Key& key) {
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
    Value AVLTree<Key, Value>::get(const Key &key) {
        auto node = _find(key);
        return node->element.value;
    }

    template<typename Key, typename Value> inline
    BinaryTreeNode<TreeElement<Key, Value>>*  AVLTree<Key, Value>::_deleteMinFromNode(BinaryTreeNode<TreeElement<Key, Value>> *node){
        BinaryTreeNode<TreeElement<Key, Value>>* min_node = node;
        while (min_node->left() != nullptr) {
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

    // we must ensure that the node will be deleted is a 3-node or 4-node
    template<typename Key, typename Value> inline
    Value AVLTree<Key, Value>::del(const Key &key) {
        auto node = _find(key);
        auto parent = node->parent();
        auto result = node->element.value;
        if (node->left() == nullptr && node->right() == nullptr) {
            if (node == _root) {
                _root = nullptr;
                delete node;
                return result;
            }
            if (node->isLeft()) {
                node->parent()->deleteLeft();
            } else {
                node->parent()->deleteRight();
            }
        } else if (node->right() == nullptr) {
            node = _llRotate(node);
            parent = node;
            node = node->deleteRight();
        }  else {
            auto min_node = _deleteMinFromNode(node->right());
            node->element = min_node->element;
            parent = min_node->parent();
            node = min_node;
        }
        // delete a line has single child: 1
        if (parent->node_count == 2) {
            _reBalanceFactor(node, -1);
        }
        // delete a line has two children
        else {
            if (node->isLeft()) {
                parent->b_factor -= 1;
            } else {
                parent->b_factor += 1;
            }
        }
        delete node;
        while (parent != nullptr) {
            parent->node_count--;
            parent = parent->parent();
        }
        _balance(_root);
        return result;
    }

    template <typename Key, typename Value> inline
    size_t AVLTree<Key, Value>::_rankOfNode(BinaryTreeNode<TreeElement<Key, Value>> *node){
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
    Key AVLTree<Key, Value>::select(const size_t k) {
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
    size_t AVLTree<Key, Value>::rank(const Key &key){
        auto node = _find(key);
        return _rankOfNode(node);
    }
}

#endif //ALGORITHM_AVL_TREE_H
