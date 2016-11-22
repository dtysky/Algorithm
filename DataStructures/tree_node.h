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
#include <iostream>


namespace data_structures {
    template <typename T>
    class TreeNode {
    protected:
        TreeNode *_left, *_right, *_parent;

    public:
        T element;
        size_t node_count;
        bool is_left;
        TreeNode();
        TreeNode(const T &element);
        TreeNode(const TreeNode &node);
        virtual ~TreeNode();
        void insertLeft(TreeNode<T> *node);
        void insertRight(TreeNode<T> *node);
        TreeNode<T> *deleteLeft();
        TreeNode<T> *deleteRight();
        TreeNode<T> *left();
        TreeNode<T> *right();
        TreeNode<T> *parent();
        TreeNode<T>& operator=(const TreeNode<T> &node);
        bool operator==(const TreeNode<T> &node);
        bool operator!=(const TreeNode<T> &node);
        friend std::ostream &operator<<(std::ostream &out, const TreeNode<T> &node) {
            out << "Current: " << &node << ", Element: " << node.element << ", Parent: " << node._parent
                      << ", Left: " << node._left << ", Right: " << node._right;
            return out;
        }
    };

    template <typename T> inline
    TreeNode<T>::TreeNode(){
        _left = nullptr;
        _right = nullptr;
        _parent = nullptr;
        element = T();
        node_count = 1;
        is_left = false;
    }

    template <typename T> inline
    TreeNode<T>::TreeNode(const T& element){
        _left = nullptr;
        _right = nullptr;
        _parent = nullptr;
        node_count = 1;
        is_left = false;
        this->element = element;
    }

    template <typename T> inline
    TreeNode<T>::TreeNode(const TreeNode<T>& node){
        element = node.element;
        _left = node._left;
        _right = node._right;
        _parent = node._parent;
        node_count = 1;
        is_left = false;
    }

    template <typename T> inline
    TreeNode<T>::~TreeNode(){
        _left = nullptr;
        _right = nullptr;
        _parent = nullptr;
        node_count = 1;
        is_left = false;
    }

    template <typename T> inline
    TreeNode<T>& TreeNode<T>::operator=(const TreeNode<T>& node){
        element = node.element;
        _left = node._left;
        _right = node._right;
        _parent = node._parent;
        node_count = 1;
        is_left = false;
        return *this;
    }

    template <typename T> inline
    bool TreeNode<T>::operator==(const TreeNode<T>& node){
        return (element == node.element) && (_parent == node._parent) && (_left == node._left);
    }

    template <typename T> inline
    bool TreeNode<T>::operator!=(const TreeNode<T>& node){
        return !(*this == node);
    }

    template <typename T> inline
    void TreeNode<T>::insertLeft(TreeNode<T> *node){
        if (node != nullptr) {
            node->_parent = this;
            node->is_left = true;
        }
        _left = node;
    }

    template <typename T> inline
    void TreeNode<T>::insertRight(TreeNode<T> *node){
        if (node != nullptr) {
            node->_parent = this;
            node->is_left = false;
        }
        _right = node;
    }

    template <typename T> inline
    TreeNode<T>* TreeNode<T>::deleteLeft(){
        TreeNode<T>* temp_node = _left;
        _left = nullptr;
        return temp_node;
    }

    template <typename T> inline
    TreeNode<T>* TreeNode<T>::deleteRight(){
        TreeNode<T>* temp_node = _right;
        _right = nullptr;
        return temp_node;
    }

    template <typename T> inline
    TreeNode<T>* TreeNode<T>::left(){
        return _left;
    }

    template <typename T> inline
    TreeNode<T>* TreeNode<T>::right(){
        return _right;
    }

    template <typename T> inline
    TreeNode<T>* TreeNode<T>::parent(){
        return _parent;
    }
}

#endif //ALGORITHM_TREE_NODE_H
