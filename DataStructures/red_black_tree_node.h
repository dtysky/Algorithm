//
//  red_black_tree_node
//  Algorithm
//
//  Created by dtysky on 16/11/30.
//  Copyright © 2016 dtysky@outlook.com. All rights reserved.
//

#ifndef ALGORITHM_RED_BLACK_TREE_NODE_H
#define ALGORITHM_RED_BLACK_TREE_NODE_H

#include <cstdio>
#include <iostream>
#include <string>
#include <sstream>


namespace data_structures {
    template <typename T>
    class RBTreeNode {
    protected:
        RBTreeNode<T> *_left, *_right, *_parent;
        bool _is_left, _is_red;
        void _init();
        void _copy(const RBTreeNode<T> &node);

    public:
        T element;
        size_t node_count;
        RBTreeNode();
        RBTreeNode(const T &element);
        RBTreeNode(const RBTreeNode<T> &node);
        virtual ~RBTreeNode();
        bool isLeft();
        bool isRed();
        RBTreeNode<T> *initRoot();
        RBTreeNode<T> *flipColors();
        RBTreeNode<T> *insertLeft(RBTreeNode<T> *node, const bool is_red = false);
        RBTreeNode<T> *insertRight(RBTreeNode<T> *node, const bool is_red = false);
        RBTreeNode<T> *deleteLeft();
        RBTreeNode<T> *deleteRight();
        RBTreeNode<T> *left();
        RBTreeNode<T> *right();
        RBTreeNode<T> *parent();
        std::string toString();
        RBTreeNode<T>& operator=(const RBTreeNode<T> &node);
        bool operator==(const RBTreeNode<T> &node);
        bool operator!=(const RBTreeNode<T> &node);
        friend std::ostream &operator<<(std::ostream &out, const RBTreeNode<T> &node) {
            out << "Current: " << &node << ", Element: " << node.element << ", Parent: " << node._parent
                << ", Left: " << node._left << ", Right: " << node._right;
            return out;
        }
    };

    template <typename T> inline
    void RBTreeNode<T>::_init() {
        _left = nullptr;
        _right = nullptr;
        _parent = nullptr;
        element = T();
        node_count = 1;
        _is_left = false;
        _is_red = false;
    }

    template <typename T> inline
    void RBTreeNode<T>::_copy(const RBTreeNode<T> &node){
        element = node.element;
        _left = node._left;
        _right = node._right;
        _parent = node._parent;
        node_count = 1;
        _is_left = false;
        _is_red = false;
    }

    template <typename T> inline
    RBTreeNode<T>::RBTreeNode(){
        _init();
    }

    template <typename T> inline
    RBTreeNode<T>::RBTreeNode(const T& element){
        _init();
        this->element = element;
    }

    template <typename T> inline
    RBTreeNode<T>::RBTreeNode(const RBTreeNode<T>& node){
        _copy(node);
    }

    template <typename T> inline
    RBTreeNode<T>::~RBTreeNode(){
        _init();
    }

    template <typename T> inline
    RBTreeNode<T>& RBTreeNode<T>::operator=(const RBTreeNode<T>& node){
        _copy(node);
        return *this;
    }

    template <typename T> inline
    bool RBTreeNode<T>::operator==(const RBTreeNode<T>& node){
        return (element == node.element) && (_parent == node._parent) && (_left == node._left);
    }

    template <typename T> inline
    bool RBTreeNode<T>::operator!=(const RBTreeNode<T>& node){
        return !(*this == node);
    }

    template <typename T> inline
    bool RBTreeNode<T>::isLeft(){
        return _is_left;
    }

    template <typename T> inline
    bool RBTreeNode<T>::isRed(){
        return _is_red;
    }

    template <typename T> inline
    RBTreeNode<T>* RBTreeNode<T>::initRoot(){
        _parent = nullptr;
        _is_left = false;
        _is_red = false;
        return this;
    }

    template <typename T> inline
    RBTreeNode<T> * RBTreeNode<T>::flipColors(){
        _is_red = !_is_red;
        return this;
    }

    template <typename T> inline
    RBTreeNode<T> * RBTreeNode<T>::insertLeft(RBTreeNode<T> *node, const bool is_red){
        RBTreeNode<T>* temp_node = _left;
        if (node != nullptr) {
            node->_parent = this;
            node->_is_left = true;
            node->_is_red = is_red;
        }
        _left = node;
        return temp_node;
    }

    template <typename T> inline
    RBTreeNode<T> * RBTreeNode<T>::insertRight(RBTreeNode<T> *node, const bool is_red){
        RBTreeNode<T>* temp_node = _right;
        if (node != nullptr) {
            node->_parent = this;
            node->_is_left = false;
            node->_is_red = is_red;
        }
        _right = node;
        return temp_node;
    }

    template <typename T> inline
    RBTreeNode<T>* RBTreeNode<T>::deleteLeft(){
        RBTreeNode<T>* temp_node = _left;
        _left = nullptr;
        return temp_node;
    }

    template <typename T> inline
    RBTreeNode<T>* RBTreeNode<T>::deleteRight(){
        RBTreeNode<T>* temp_node = _right;
        _right = nullptr;
        return temp_node;
    }

    template <typename T> inline
    RBTreeNode<T>* RBTreeNode<T>::left(){
        return _left;
    }

    template <typename T> inline
    RBTreeNode<T>* RBTreeNode<T>::right(){
        return _right;
    }

    template <typename T> inline
    RBTreeNode<T>* RBTreeNode<T>::parent(){
        return _parent;
    }

    template <typename T> inline
    std::string RBTreeNode<T>::toString(){
        std::ostringstream ss;
        ss << element << "(" << (_is_red ? "r" : "b") << "," << node_count << ")";
        return ss.str();
    }
}


#endif //ALGORITHM_RED_BLACK_TREE_NODE_H
