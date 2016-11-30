//
//  binary_tree_node
//  Algorithm
//
//  Created by dtysky on 16/11/30.
//  Copyright © 2016 dtysky@outlook.com. All rights reserved.
//

#ifndef ALGORITHM_BINARY_TREE_NODE_H
#define ALGORITHM_BINARY_TREE_NODE_H

#include <cstdio>
#include <iostream>
#include "tree_element.h"


namespace data_structures {
    template <typename T>
    class BinaryTreeNode {
    protected:
        BinaryTreeNode<T> *_left, *_right, *_parent;
        void _init();
        void _copy(const BinaryTreeNode<T> &node);

    public:
        T element;
        size_t node_count;
        bool is_left;
        BinaryTreeNode();
        BinaryTreeNode(const T &element);
        BinaryTreeNode(const BinaryTreeNode<T> &node);
        virtual ~BinaryTreeNode();
        BinaryTreeNode<T> * insertLeft(BinaryTreeNode<T> *node);
        BinaryTreeNode<T> * insertRight(BinaryTreeNode<T> *node);
        BinaryTreeNode<T> *deleteLeft();
        BinaryTreeNode<T> *deleteRight();
        BinaryTreeNode<T> *left();
        BinaryTreeNode<T> *right();
        BinaryTreeNode<T> *parent();
        BinaryTreeNode<T>& operator=(const BinaryTreeNode<T> &node);
        bool operator==(const BinaryTreeNode<T> &node);
        bool operator!=(const BinaryTreeNode<T> &node);
        friend std::ostream &operator<<(std::ostream &out, const BinaryTreeNode<T> &node) {
            out << "Current: " << &node << ", Element: " << node.element << ", Parent: " << node._parent
                << ", Left: " << node._left << ", Right: " << node._right;
            return out;
        }
    };

    template <typename T> inline
    void BinaryTreeNode<T>::_init() {
        _left = nullptr;
        _right = nullptr;
        _parent = nullptr;
        element = T();
        node_count = 1;
        is_left = false;
    }

    template <typename T> inline
    void BinaryTreeNode<T>::_copy(const BinaryTreeNode<T> &node){
        element = node.element;
        _left = node._left;
        _right = node._right;
        _parent = node._parent;
        node_count = 1;
        is_left = false;
    }

    template <typename T> inline
    BinaryTreeNode<T>::BinaryTreeNode(){
        _init();
    }

    template <typename T> inline
    BinaryTreeNode<T>::BinaryTreeNode(const T& element){
        _init();
        this->element = element;
    }

    template <typename T> inline
    BinaryTreeNode<T>::BinaryTreeNode(const BinaryTreeNode<T>& node){
        _copy(node);
    }

    template <typename T> inline
    BinaryTreeNode<T>::~BinaryTreeNode(){
        _init();
    }

    template <typename T> inline
    BinaryTreeNode<T>& BinaryTreeNode<T>::operator=(const BinaryTreeNode<T>& node){
        _copy(node);
        return *this;
    }

    template <typename T> inline
    bool BinaryTreeNode<T>::operator==(const BinaryTreeNode<T>& node){
        return (element == node.element) && (_parent == node._parent) && (_left == node._left);
    }

    template <typename T> inline
    bool BinaryTreeNode<T>::operator!=(const BinaryTreeNode<T>& node){
        return !(*this == node);
    }

    template <typename T> inline
    BinaryTreeNode<T> * BinaryTreeNode<T>::insertLeft(BinaryTreeNode<T> *node){
        BinaryTreeNode<T>* temp_node = _left;
        if (node != nullptr) {
            node->_parent = this;
            node->is_left = true;
        }
        _left = node;
        return temp_node;
    }

    template <typename T> inline
    BinaryTreeNode<T> * BinaryTreeNode<T>::insertRight(BinaryTreeNode<T> *node){
        BinaryTreeNode<T>* temp_node = _right;
        if (node != nullptr) {
            node->_parent = this;
            node->is_left = false;
        }
        _right = node;
        return temp_node;
    }

    template <typename T> inline
    BinaryTreeNode<T>* BinaryTreeNode<T>::deleteLeft(){
        BinaryTreeNode<T>* temp_node = _left;
        _left = nullptr;
        return temp_node;
    }

    template <typename T> inline
    BinaryTreeNode<T>* BinaryTreeNode<T>::deleteRight(){
        BinaryTreeNode<T>* temp_node = _right;
        _right = nullptr;
        return temp_node;
    }

    template <typename T> inline
    BinaryTreeNode<T>* BinaryTreeNode<T>::left(){
        return _left;
    }

    template <typename T> inline
    BinaryTreeNode<T>* BinaryTreeNode<T>::right(){
        return _right;
    }

    template <typename T> inline
    BinaryTreeNode<T>* BinaryTreeNode<T>::parent(){
        return _parent;
    }
}

#endif //ALGORITHM_BINARY_TREE_NODE_H
