//
//  tree_nodes
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
    /* -------- TreeNode -------- */
    template <typename T, typename NodeType = TreeNode>
    class TreeNode {
    protected:
        NodeType<T> *_left, *_right, *_parent;
        void _init();
        void _copy(const NodeType<T> &node);

    public:
        T element;
        size_t node_count;
        bool is_left;
        TreeNode();
        TreeNode(const T &element);
        TreeNode(const NodeType<T> &node);
        virtual ~TreeNode();
        void insertLeft(NodeType<T> *node);
        void insertRight(NodeType<T> *node);
        NodeType<T> *deleteLeft();
        NodeType<T> *deleteRight();
        NodeType<T> *left();
        NodeType<T> *right();
        NodeType<T> *parent();
        NodeType<T>& operator=(const NodeType<T> &node);
        bool operator==(const NodeType<T> &node);
        bool operator!=(const NodeType<T> &node);
        friend std::ostream &operator<<(std::ostream &out, const NodeType<T> &node) {
            out << "Current: " << &node << ", Element: " << node.element << ", Parent: " << node._parent
                      << ", Left: " << node._left << ", Right: " << node._right;
            return out;
        }
    };

    template <typename T, typename NodeType> inline
    void TreeNode<T>::_init() {
        _left = nullptr;
        _right = nullptr;
        _parent = nullptr;
        element = T();
        node_count = 1;
        is_left = false;
    }

    template <typename T, typename NodeType> inline
    void TreeNode<T>::_copy(const NodeType<T> &node){
        element = node.element;
        _left = node._left;
        _right = node._right;
        _parent = node._parent;
        node_count = 1;
        is_left = false;
    }

    template <typename T, typename NodeType> inline
    TreeNode<T>::TreeNode(){
        _init();
    }

    template <typename T, typename NodeType> inline
    TreeNode<T>::TreeNode(const T& element){
        _init();
        this->element = element;
    }

    template <typename T, typename NodeType> inline
    TreeNode<T>::TreeNode(const NodeType<T>& node){
        _copy(node);
    }

    template <typename T, typename NodeType> inline
    TreeNode<T>::~TreeNode(){
        _init();
    }

    template <typename T, typename NodeType> inline
    NodeType<T>& TreeNode<T>::operator=(const NodeType<T>& node){
        _copy(node);
        return *this;
    }

    template <typename T, typename NodeType> inline
    bool TreeNode<T>::operator==(const NodeType<T>& node){
        return (element == node.element) && (_parent == node._parent) && (_left == node._left);
    }

    template <typename T, typename NodeType> inline
    bool TreeNode<T>::operator!=(const NodeType<T>& node){
        return !(*this == node);
    }

    template <typename T, typename NodeType> inline
    void TreeNode<T>::insertLeft(NodeType<T> *node){
        if (node != nullptr) {
            node->_parent = this;
            node->is_left = true;
        }
        _left = node;
    }

    template <typename T, typename NodeType> inline
    void TreeNode<T>::insertRight(NodeType<T> *node){
        if (node != nullptr) {
            node->_parent = this;
            node->is_left = false;
        }
        _right = node;
    }

    template <typename T, typename NodeType> inline
    NodeType<T>* TreeNode<T>::deleteLeft(){
        TreeNode<T>* temp_node = _left;
        _left = nullptr;
        return temp_node;
    }

    template <typename T, typename NodeType> inline
    NodeType<T>* TreeNode<T>::deleteRight(){
        TreeNode<T>* temp_node = _right;
        _right = nullptr;
        return temp_node;
    }

    template <typename T, typename NodeType> inline
    NodeType<T>* TreeNode<T>::left(){
        return _left;
    }

    template <typename T, typename NodeType> inline
    NodeType<T>* TreeNode<T>::right(){
        return _right;
    }

    template <typename T, typename NodeType> inline
    NodeType<T>* TreeNode<T>::parent(){
        return _parent;
    }


    /* -------- ThreeTreeNode -------- */
    template <typename T>
    class TwoThreeTreeNode {
    protected:
        TwoThreeTreeNode<T>* _parent;
        TwoThreeTreeNode<T> _children[];
        void _init(const size_t type = 2);
        void _copy(const TwoThreeTreeNode<T> &node);

    public:
        size_t type, node_count;
        T elements[];
        TwoThreeTreeNode(const size_t type = 2);
        TwoThreeTreeNode(const T &elements, const size_t type = 2);
        TwoThreeTreeNode(const TwoThreeTreeNode<T> &node);
        virtual ~TreeNode();
        TwoThreeTreeNode<T>* insertChild(const size_t position, TwoThreeTreeNode<T>* node);
        TwoThreeTreeNode<T>* delChild(const size_t position);
        TwoThreeTreeNode<T>* expand();
        TwoThreeTreeNode<T>* parent();
        TwoThreeTreeNode<T>* child(const size_t position);
        TwoThreeTreeNode<T>& operator=(const TwoThreeTreeNode<T> &node);
        bool operator==(const TwoThreeTreeNode<T> &node);
        bool operator!=(const TwoThreeTreeNode<T> &node);
        friend std::ostream &operator<<(std::ostream &out, const TwoThreeTreeNode<T> &node) {
            out << "Current: " << &node << ", Elements: " << node.elements << ", Parent: " << node._parent
                << ", Children: " << node._children;
            return out;
        }
    };

    template <typename T> inline
    void TwoThreeTreeNode<T>::_init(const size_t type = 2) {
        _parent = nullptr;
        _children = {};
        elements = {};
        this->type = 2;
        node_count = 1;
        for (int i = 0; i < type; i++) {
            _children[i] = nullptr;
            elements[i] = T();
        }
    }

    template <typename T> inline
    void TwoThreeTreeNode<T>::_copy(const TwoThreeTreeNode<T> &node){
        elements = node.elements;
        _parent = node._parent;
        _children = {};
        node_count = 1;
        type = node.type;
        for (int i = 0; i < type; i++) {
            _children[i] = nullptr;
        }
    }

    template <typename T> inline
    TwoThreeTreeNode<T>::TwoThreeTreeNode(const size_t type = 2){
        _init(type);
    }

    template <typename T> inline
    TwoThreeTreeNode<T>::TwoThreeTreeNode(const T& elements, const size_t type = 2){
        _init(type);
        this->elements = elements;
    }

    template <typename T> inline
    TwoThreeTreeNode<T>::TwoThreeTreeNode(const TwoThreeTreeNode<T>& node){
        _copy(node);
    }

    template <typename T> inline
    void TwoThreeTreeNode<T>::~TreeNode(){
        _init(type);
    }

    template <typename T> inline
    TwoThreeTreeNode<T>& TreeNode<T>::operator=(const TwoThreeTreeNode<T>& node){
        _copy(node);
        return *this;
    }

    template <typename T> inline
    bool TwoThreeTreeNode<T>::operator==(const TwoThreeTreeNode<T>& node){
        return (elements == node.elements) && (_parent == node._parent) && (_children == node._children);
    }

    template <typename T> inline
    bool TwoThreeTreeNode<T>::operator!=(const TwoThreeTreeNode<T>& node){
        return !(*this == node);
    }


}

#endif //ALGORITHM_TREE_NODE_H
