//
//  heap_node
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
    class HeapNode {
    protected:
        HeapNode *_left, *_right, *_parent;

    public:
        T element;
        HeapNode();
        HeapNode(const T& element);
        HeapNode(const HeapNode& node);
        virtual ~HeapNode();
        void insertLeft(HeapNode<T>* node);
        void insertRight(HeapNode<T>* node);
        HeapNode<T>* deleteLeft();
        HeapNode<T>* deleteRight();
        HeapNode<T>* left();
        HeapNode<T>* right();
        HeapNode<T>* parent();
        void operator=(const HeapNode<T>& node);
        bool operator==(const HeapNode<T>& node);
        bool operator!=(const HeapNode<T>& node);
        friend std::ostream& operator<<(std::ostream& out, const HeapNode<T>& node){
//            std::cout << "Current: " << &node << ", Element: " << node.element << ", Next: " << node._next;
            return out;
        }


        template <typename T> inline
        HeapNode<T>::HeapNode(){
            _left = nullptr;
            _right = nullptr;
            _parent = nullptr;
            element = T();
        }

        template <typename T> inline
        HeapNode<T>::HeapNode(const T& element){
            _left = nullptr;
            _right = nullptr;
            _parent = nullptr;
            this->element = element;
        }

        template <typename T> inline
        HeapNode<T>::HeapNode(const HeapNode<T>& node){
            element = node.element;
            _left = node._left;
            _right = node._right;
            _parent = node._parent;
        }

        template <typename T> inline
        HeapNode<T>::~HeapNode(){
            _left = nullptr;
            _right = nullptr;
            _parent = nullptr;
        }

        template <typename T> inline
        void HeapNode<T>::operator=(const HeapNode<T>& node){
            element = node.element;
            _left = node._left;
            _right = node._right;
            _parent = node._parent;
        }

        template <typename T> inline
        bool HeapNode<T>::operator==(const HeapNode<T>& node){
            return (element == node.element) && (_parent == node._parent) && (_left == node._left);
        }

        template <typename T> inline
        bool HeapNode<T>::operator!=(const HeapNode<T>& node){
            return !(*this == node);
        }

        template <typename T> inline
        void HeapNode<T>::insertLeft(HeapNode<T> *node){
            node->_left = _left;
            node->_parent = this;
            _left = node;
        }

        template <typename T> inline
        void HeapNode<T>::insertRight(HeapNode<T> *node){
            node->_left = _right;
            node->_parent = this;
            _right = node;
        }

        template <typename T> inline
        HeapNode<T>* HeapNode<T>::deleteLeft(){
            HeapNode<T>* temp_node = _left;
            _left = nullptr;
            return temp_node;
        }

        template <typename T> inline
        HeapNode<T>* HeapNode<T>::deleteRight(){
            HeapNode<T>* temp_node = _right;
            _right = nullptr;
            return temp_node;
        }

        template <typename T> inline
        HeapNode<T>* HeapNode<T>::left(){
            return _left;
        }

        template <typename T> inline
        HeapNode<T>* HeapNode<T>::right(){
            return _right;
        }

        template <typename T> inline
        HeapNode<T>* HeapNode<T>::parent(){
            return _parent;
        }
    };
}

#endif //ALGORITHM_TREE_NODE_H
