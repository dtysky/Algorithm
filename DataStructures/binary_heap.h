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
#include "heap_node.h"


namespace data_structures {
    template<typename T, bool MinHeap = false>
    class BinaryHeap {
    protected:
        HeapNode<T> *_root;
        size_t _size;
        bool _less(const T &element1, const T &element2);
        void _checkN(const size_t n);
        bool _swim(const size_t n);
        bool _sink(const size_t n);
        void _copy(HeapNode<T> *node, HeapNode<T> *node_src);
        void _delete(HeapNode<T> *node);

    public:
        BinaryHeap();
        BinaryHeap(BinaryHeap<T, MinHeap> &heap);
        ~BinaryHeap();
        bool isEmpty();
        size_t size();
        BinaryHeap& clear();
        BinaryHeap& insert(const T &element);
        T getN(const size_t n);
        T deleteN(const size_t n);
        void operator=(const BinaryHeap<T, MinHeap> &node);
        bool operator==(const BinaryHeap<T, MinHeap> &node);
        bool operator!=(const BinaryHeap<T, MinHeap> &node);
        friend std::ostream &operator<<(std::ostream &out, const BinaryHeap<T, MinHeap> &heap) {
//            std::cout << heap._array;
            return out;
        };
    };


    template<typename T, bool MinHeap = false> inline
    BinaryHeap<T, MinHeap>::BinaryHeap() {
        _root = new HeapNode<T>();
        _size = 0;
    }

    template<typename T, bool MinHeap = false> inline
    BinaryHeap<T, MinHeap>::BinaryHeap(BinaryHeap<T, MinHeap> &heap) {
        _copy(_root, heap._root);
        _size = 0;
    }

    template<typename T, bool MinHeap = false> inline
    BinaryHeap<T, MinHeap>::~BinaryHeap() {
        _delete(_root);
        _size = 0;
    }

    template<typename T, bool MinHeap = false> inline
    void BinaryHeap<T, MinHeap>::_copy(HeapNode<T> *node, HeapNode<T> *node_src){
        node->element = node_src->element;
        if (node_src->left() != nullptr) {
            node->insertLeft(new HeapNode<T>(node_src->left()->element));
            _copy(node->left(), node_src->left());
        }
        if (node_src->right() != nullptr) {
            node->insertRight(new HeapNode<T>(node_src->right()->element));
            _copy(node->right(), node_src->right());
        }
    }

    template<typename T, bool MinHeap = false> inline
    void BinaryHeap<T, MinHeap>::_delete(HeapNode<T> *node){
        if (node == nullptr) {
            return;
        }
        _delete(node->left());
        _delete(node->right());
        delete node;
    }

    template <typename T, bool MinHeap = false> inline
    void BinaryHeap<T, MinHeap>::operator=(const BinaryHeap<T, MinHeap>& heap){
        _copy(_root, heap._root);
        _size = 0;
    }

    template <typename T, bool MinHeap = false> inline
    bool BinaryHeap<T, MinHeap>::operator==(const BinaryHeap<T, MinHeap>& heap){
        return _root == heap._root;
    }

    template <typename T, bool MinHeap = false> inline
    bool BinaryHeap<T, MinHeap>::operator!=(const BinaryHeap<T, MinHeap>& heap){
        return _root != heap._root;
    }

    template <typename T, bool MinHeap = false> inline
    bool BinaryHeap<T, MinHeap>::isEmpty() {
        return _root->left() == nullptr && _root->right() == nullptr;
    }

    template <typename T, bool MinHeap = false> inline
    BinaryHeap<T, MinHeap>& BinaryHeap<T, MinHeap>::clear(){
        _delete(_root);
        _root = new HeapNode<T>();
        _size = 0;
        return *this;
    }

    template <typename T, bool MinHeap = false> inline
    size_t BinaryHeap<T, MinHeap>::size(){
        return _size;
    }

    template <typename T, bool MinHeap = false> inline
    bool BinaryHeap<T, MinHeap>::_less(const T &element1, const T &element2) {
        return element1 < element2;
    }

    template <typename T> inline
    void BinaryHeap<T>::_checkN(const size_t n) {
        if (n == 0 || n > _size) {
            throw std::out_of_range("N must be larger than 0 and less than this heap's size !");
        }
    }

    template<typename T, bool MinHeap = false> inline
    BinaryHeap<T, MinHeap>& BinaryHeap<T, MinHeap>::insert(const T &element) {

    }

    template<typename T, bool MinHeap = false> inline
    T &BinaryHeap<T, MinHeap>::getN(const size_t n) {

    }

    template<typename T, bool MinHeap = false> inline
    T &BinaryHeap<T, MinHeap>::deleteN(const size_t n) {

    }

};


#endif //ALGORITHM_BINARY_HEAP_H
