//
//  2_3_tree_node
//  Algorithm
//
//  Created by dtysky on 16/11/30.
//  Copyright © 2016 dtysky@outlook.com. All rights reserved.
//

#ifndef ALGORITHM_2_3_TREE_NODE_H
#define ALGORITHM_2_3_TREE_NODE_H

#include <cstdio>
#include <iostream>


/*
 * This data structure will not be completed in a long time.
*/


namespace data_structures {
    template <typename T>
    class TwoThreeTreeNode {
    protected:
        TwoThreeTreeNode<T>* _parent;
        TwoThreeTreeNode<T>* _children[];
        size_t _child_index;
        void _init(const size_t type);
        void _copy(const TwoThreeTreeNode<T> &node);
        void _check(const size_t index);

    public:
        size_t type, node_count;
        T elements[];
        TwoThreeTreeNode(const size_t type = 1);
        TwoThreeTreeNode(const T &elements[], const size_t type = 1);
        TwoThreeTreeNode(const T &elements, const size_t type = 1);
        TwoThreeTreeNode(const TwoThreeTreeNode<T> &node);
        virtual ~TwoThreeTreeNode();
        T getElement(const size_t child);
        void setElement(const size_t child, T element);
        size_t getIndex();
        bool isLeaf();
        TwoThreeTreeNode<T>* insertChild(const size_t child, TwoThreeTreeNode<T>* node);
        TwoThreeTreeNode<T>* deleteChild(const size_t child);
        size_t type1to2(const T& element);
        TwoThreeTreeNode<T>* type1to0(const size_t child);
        TwoThreeTreeNode<T>* type2to1(const size_t element, const size_t child);
        size_t type2to3(const T& element);
        size_t type1to2(TwoThreeTreeNode<T>* node);
        size_t type0to1(const T& element);
        TwoThreeTreeNode<T>* expandRoot();
        TwoThreeTreeNode<T>* expand();
        TwoThreeTreeNode<T>* parent();
        TwoThreeTreeNode<T>* child(const size_t index);
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
    void TwoThreeTreeNode<T>::_init(const size_t type) {
        if (type == 0) {
            throw std::out_of_range("Type error, it can not be zero !");
        }
        _parent = nullptr;
        _children = {};
        elements = {};
        this->type = 2;
        node_count = 1;
        _child_index = 0;
        for (int i = 0; i < type; i++) {
            elements[i] = T();
            _children[i] = nullptr;
        }
        _children[type] = nullptr;
    }

    template <typename T> inline
    void TwoThreeTreeNode<T>::_copy(const TwoThreeTreeNode<T> &node){
        elements = node.elements;
        _parent = node._parent;
        _children = {};
        node_count = 1;
        _child_index = 0;
        type = node.type;
        for (int i = 0; i <= type; i++) {
            _children[i] = nullptr;
        }
    }

    template <typename T> inline
    TwoThreeTreeNode<T>::TwoThreeTreeNode(const size_t type){
        _init(type);
    }

    template <typename T> inline
    TwoThreeTreeNode<T>::TwoThreeTreeNode(const T& elements, const size_t type){
        _init(type);
        this->elements[0] = elements;
    }

    template <typename T> inline
    TwoThreeTreeNode<T>::TwoThreeTreeNode(const T& elements[], const size_t){
        _init(type);
        this->elements = elements;
    }

    template <typename T> inline
    TwoThreeTreeNode<T>::TwoThreeTreeNode(const TwoThreeTreeNode<T>& node){
        _copy(node);
    }

    template <typename T> inline
    TwoThreeTreeNode<T>::~TwoThreeTreeNode(){
        _init(type);
    }

    template <typename T> inline
    TwoThreeTreeNode<T>& TwoThreeTreeNode<T>::operator=(const TwoThreeTreeNode<T>& node){
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

    template <typename T> inline
    void TwoThreeTreeNode<T>::_check(const size_t index) {
        if (index >= type) {
            throw std::out_of_range("Index error, it's larger than tree-node's size !");
        }
    }

    template <typename T> inline
    bool TwoThreeTreeNode<T>::isLeaf(){
        for (size_t i = 0; i <= type; i++) {
            if (_children[i] != nullptr) {
                return false;
            }
        }
        return true;
    }

    template <typename T> inline
    void TwoThreeTreeNode<T>::setElement(const size_t child, T element){
        _check(child);
        elements[child] = element;
    }

    template <typename T> inline
    T TwoThreeTreeNode<T>::getElement(const size_t child) {
        _check(child);
        return elements[child];
    }

    template <typename T> inline
    size_t TwoThreeTreeNode<T>::getIndex(){
        for (size_t i = 0; i < _parent->type; i++) {
            if (_parent->child(i) == this) {
                return i;
            }
        }
    }

    template <typename T> inline
    TwoThreeTreeNode<T>* TwoThreeTreeNode<T>::insertChild(const size_t child, TwoThreeTreeNode<T> *node){
        _check(child);
        TwoThreeTreeNode<T>*  tmp_node = _children[child];
        if (node != nullptr) {
            node->_parent = this;
            node->_child_index = child;
        }
        _children[child] = node;
        return tmp_node;
    }

    template <typename T> inline
    TwoThreeTreeNode<T>* TwoThreeTreeNode<T>::deleteChild(const size_t child){
        _check(child);
        TwoThreeTreeNode<T>*  tmp_node = _children[child];
        _children[child] = nullptr;
        return tmp_node;
    }

    template <typename T> inline
    size_t TwoThreeTreeNode<T>::type1to2(const T& element){
        if (type != 1) {
            throw std::out_of_range("Type error, type of current node is not 1 !");
        }
        type = 2;
        if (element.key < elements[0].key) {
            elements[1] = elements[0];
            elements[0] = element;
            _children[2] = _children[1];
            _children[1] = _children[0];
            _children[0] = nullptr;
            return 0;
        }
        elements[1] = element;
        _children[2] = nullptr;
        return 1;
    }

    template <typename T> inline
    size_t TwoThreeTreeNode<T>::type0to1(const T& element){
        if (type != 0) {
            throw std::out_of_range("Type error, type of current node is not 0 !");
        }
        type = 1;
        elements[0] = element;
        _children[1] = nullptr;
        return 0;
    }

    template <typename T> inline
    TwoThreeTreeNode<T>* TwoThreeTreeNode<T>::type2to1(const size_t element, const size_t child){
        if (type != 2) {
            throw std::out_of_range("Type error, type of current node is not 2 !");
        }
        auto tmp_node = _children[child];
        type = 1;
        if (child == 0) {
            _children[0] = _children[1];
            _children[1] = _children[2];
        } else if (child == 1 && element == 1) {
            _children[1] = _children[2];
            elements[0] = elements[1];
        } else {
            elements[0] = elements[1];
        }
        return tmp_node;
    }

    template <typename T> inline
    TwoThreeTreeNode<T>* TwoThreeTreeNode<T>::type1to0(const size_t child){
        if (type != 2) {
            throw std::out_of_range("Type error, type of current node is not 2 !");
        }
        auto tmp_node = _children[child];
        type = 0;
        if (child == 0) {
            _children[0] = _children[1];
        }
        return tmp_node;
    }

    template <typename T> inline
    size_t TwoThreeTreeNode<T>::type2to3(const T& element){
        if (type != 2) {
            throw std::out_of_range("Type error, type of current node is not 2 !");
        }
        type = 3;
        _children[3] = nullptr;
        if (element.key < elements[0].key) {
            elements[2] = elements[1];
            elements[1] = elements[0];
            elements[0] = element;
            return 0;
        } else if (element.key < elements[1].key) {
            elements[2] = elements[1];
            elements[1] = element;
            return 1;
        } else {
            elements[2] = element;
            return 2;
        }
    }

    template <typename T> inline
    size_t TwoThreeTreeNode<T>::type1to2(TwoThreeTreeNode<T>* node){
        if (type != 1 || node->type != 1) {
            throw std::out_of_range("Type error, type of current node is not 1 !");
        }
        if (!isLeaf()) {
            throw std::out_of_range("Type error, node is not a leaf !");
        }
        type = 2;
        if (node->getElement(0).key < elements[0].key) {
            elements[1] = elements[0];
            elements[0] = node->getElement(0);
            _children[2] = _children[1];
            _children[0] = node->child(1);
            _children[1] = node->child(2);
            return 0;
        } else {
            elements[1] = node->getElement(0);
            _children[1] = node->child(1);
            _children[2] = node->child(2);
            return 1;
        }
    }

    template <typename T> inline
    TwoThreeTreeNode<T>* TwoThreeTreeNode<T>::expandRoot(){
        if (type != 3) {
            throw std::out_of_range("Type error, type of current node is not 3 !");
        }
        type = 1;
        auto left = new TwoThreeTreeNode<T>(elements[0]);
        left->insertChild(0, _children[0]);
        left->insertChild(1, _children[1]);
        auto right = new TwoThreeTreeNode<T>(elements[2]);
        right->insertChild(0, _children[2]);
        right->insertChild(1, _children[3]);
        _children[0] = left;
        _children[1] = right;
        _children[2] = nullptr;
        _children[3] = nullptr;
        return this;
    }

    template <typename T> inline
    TwoThreeTreeNode<T>* TwoThreeTreeNode<T>::expand(){
        if (type != 3) {
            throw std::out_of_range("Type error, type of current node is not 3 !");
        }
        type = 1;
        auto right = new TwoThreeTreeNode<T>(elements[2]);
        right->insertChild(0, _children[2]);
        right->insertChild(1, _children[3]);
        _children[2] = nullptr;
        _children[3] = nullptr;
        if (_parent->type == 1) {
            _parent->type1to2(elements[1]);
            if (_child_index == 0) {
                _parent->insertChild(2, _parent->child(1));
            }
            _parent->insertChild(_child_index + 1, right);
        } else {
            _parent->type2to3(elements[1]);
            if (_child_index == 0) {
                _parent->insertChild(3, _parent->child(2));
                _parent->insertChild(2, _parent->child(1));
            } else if (_child_index == 1) {
                _parent->insertChild(3, _parent->child(2));
            }
            _parent->insertChild(_child_index + 1, right);
        }
        return _parent;
    }

    template <typename T> inline
    TwoThreeTreeNode<T>* TwoThreeTreeNode<T>::parent(){
        return _parent;
    }

    template <typename T> inline
    TwoThreeTreeNode<T>* TwoThreeTreeNode<T>::child(const size_t index){
        _check(index);
        return _children[index];
    }
}

#endif //ALGORITHM_2_3_TREE_NODE_H
