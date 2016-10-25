//
//  binary_heap
//  Algorithm
//
//  Created by dtysky on 16/10/19.
//  Copyright © 2016 dtysky@outlook.com. All rights reserved.
//

#ifndef ALGORITHM_BINARY_HEAP_H
#define ALGORITHM_BINARY_HEAP_H

#include <cstdio>
#include <iostream>
#include <iomanip>
#include "heap_node.h"


namespace data_structures {
    template<typename T>
    class BinaryHeap {
    protected:
        HeapNode<T> *_root;
        HeapNode<T> *_tail;
        size_t _size;
        virtual bool _compare(const T &element1, const T &element2);
        void _exec(HeapNode<T> *node1, HeapNode<T> *node2);
        void _swim(HeapNode<T> *node);
        void _sink(HeapNode<T> *node);
        void _copy(HeapNode<T> *node, HeapNode<T> *node_src);
        void _delete(HeapNode<T> *node);

    public:
        BinaryHeap();
        BinaryHeap(BinaryHeap<T> &heap);
        virtual ~BinaryHeap();
        bool isEmpty();
        size_t size();
        BinaryHeap& clear();
        BinaryHeap& insert(const T &element);
        T top();
        T deleteTop();
        void operator=(const BinaryHeap<T> &node);
        bool operator==(const BinaryHeap<T> &node);
        bool operator!=(const BinaryHeap<T> &node);
        void printFromNode(HeapNode<T> *node, const int indent = 0) const;
        friend std::ostream &operator<<(std::ostream &out, const BinaryHeap<T> &heap) {
            heap.printFromNode(heap._root);
            return out;
        };
    };


    template<typename T> inline
    BinaryHeap<T>::BinaryHeap() {
        _root = new HeapNode<T>();
        _tail = _root;
        _size = 0;
    }

    template<typename T> inline
    BinaryHeap<T>::BinaryHeap(BinaryHeap<T> &heap) {
        _root = new HeapNode<T>();
        _tail = _root;
        _size = 0;
        _copy(_root, heap._root);
    }

    template<typename T> inline
    BinaryHeap<T>::~BinaryHeap() {
        _delete(_root);
        delete _tail;
        _size = 0;
    }

    template<typename T> inline
    void BinaryHeap<T>::_copy(HeapNode<T> *node, HeapNode<T> *node_src) {
        node->element = node_src->element;
        if (node_src->left() != nullptr) {
            node->insertLeft(new HeapNode<T>(node_src->left()->element));
            _tail = node->left();
            _size ++;
            _copy(node->left(), node_src->left());
        }
        if (node_src->right() != nullptr) {
            node->insertRight(new HeapNode<T>(node_src->right()->element));
            _tail = node->right();
            _size ++;
            _copy(node->right(), node_src->right());
        }
    }

    template<typename T> inline
    void BinaryHeap<T>::_delete(HeapNode<T> *node){
        if (node == nullptr) {
            return;
        }
        _delete(node->left());
        _delete(node->right());
        delete node;
    }

    template <typename T> inline
    void BinaryHeap<T>::operator=(const BinaryHeap<T>& heap) {
        _root = new HeapNode<T>();
        _tail = _root;
        _size = 0;
        _copy(_root, heap._root);
    }

    template <typename T> inline
    bool BinaryHeap<T>::operator==(const BinaryHeap<T>& heap) {
        return _root == heap._root;
    }

    template <typename T> inline
    bool BinaryHeap<T>::operator!=(const BinaryHeap<T>& heap) {
        return _root != heap._root;
    }

    template<typename T> inline
    void BinaryHeap<T>::printFromNode(HeapNode<T> *node, const int indent) const {
        if(node->left()) {
            printFromNode(node->left(), indent + 4);
        }
        if(node->right()) {
            printFromNode(node->right(), indent + 4);
        }
        if (indent) {
            std::cout << std::setw(indent) << ' ';
        }
        std::cout<< node->element << "\n ";
    }

    template <typename T> inline
    bool BinaryHeap<T>::isEmpty() {
        return _root == _tail;
    }

    template <typename T> inline
    BinaryHeap<T>& BinaryHeap<T>::clear() {
        _delete(_root);
        _root = new HeapNode<T>();
        _tail = _root;
        _size = 0;
        return *this;
    }

    template <typename T> inline
    size_t BinaryHeap<T>::size() {
        return _size;
    }

    template <typename T> inline
    bool BinaryHeap<T>::_compare(const T &element1, const T &element2) {}

    template <typename T> inline
    void BinaryHeap<T>::_exec(HeapNode<T> *node1, HeapNode<T> *node2) {
        auto tmp = node1->element;
        node1->element = node2->element;
        node2->element = tmp;
    }

    template <typename T> inline
    void BinaryHeap<T>::_swim(HeapNode<T> *node) {
        if (node->parent() == nullptr) {
            return;
        }
        auto current = node;
        auto parent = current->parent();
        while (parent != nullptr && _compare(current->element, parent->element)) {
            parent = current->parent();
            _exec(current, parent);
            current = parent;
        }
    }

    template <typename T> inline
    void BinaryHeap<T>::_sink(HeapNode<T> *node) {
        if (node->left() == nullptr && node->right() == nullptr) {
            return;
        }
        auto current = node;
        auto left = current->left();
        auto right = current->right();
        while (
            (left != nullptr && !_compare(current->element, left->element)) ||
            (right != nullptr && !_compare(current->element, right->element))
        ) {
            left = current->left();
            right = current->right();
            if (left == nullptr) {
                _exec(current, right);
                current = right;
                continue;
            }
            if (right == nullptr) {
                _exec(current, left);
                current = left;
                continue;
            }
            if (_compare(left->element, right->element)) {
                _exec(current, left);
                current = left;
            } else {
                _exec(current, right);
                current = right;
            }
        }
    }

    template<typename T> inline
    BinaryHeap<T>& BinaryHeap<T>::insert(const T &element) {
        if (_tail->left() == nullptr) {
            _tail->insertLeft(new HeapNode<T>(element));
            _tail = _tail->left();
        } else {
            _tail->insertRight(new HeapNode<T>(element));
            _tail = _tail->right();
        }
        _size++;
        _swim(_tail);
    }

    template<typename T> inline
    T BinaryHeap<T>::top() {
        return _root->element;
    }

    template<typename T> inline
    T BinaryHeap<T>::deleteTop() {
        auto tmp = _root->element;
        if (isEmpty()) {
            clear();
            return tmp;
        }
        _exec(_root, _tail);
        auto parent = _tail->parent();
        if (parent->right() != nullptr) {
            delete parent->deleteRight();
        } else {
            delete parent->deleteLeft();
        }
        _sink(_root);
        _size--;
        return tmp;
    }


    template <typename T>
    class MaxBinaryHeap: public BinaryHeap<T> {
    protected:
        bool _compare(const T &element1, const T &element2) {
            return element1 > element2;
        }
    };

    template <typename T>
    class MinBinaryHeap: public BinaryHeap<T> {
    protected:
        bool _compare(const T &element1, const T &element2) {
            return element1 < element2;
        }
    };
};


#endif //ALGORITHM_BINARY_HEAP_H
