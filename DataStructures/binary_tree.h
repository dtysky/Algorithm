//
//  binary_tree
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
#include "tree_node.h"


namespace data_structures {
    template<typename T>
    class BinaryTree {
    protected:
        TreeNode<T> *_root;
        TreeNode<T> *_tail;
        size_t _size;
        virtual bool _compare(const T &element1, const T &element2);
        void _exec(TreeNode<T> *node1, TreeNode<T> *node2);
        void _swim(TreeNode<T> *node);
        void _sink(TreeNode<T> *node);
        void _copy(TreeNode<T> *node, TreeNode<T> *node_src);
        void _delete(TreeNode<T> *node);

    public:
        BinaryTree();
        BinaryTree(BinaryTree<T> &tree);
        virtual ~BinaryTree();
        bool isEmpty();
        size_t size();
        BinaryTree& clear();
        BinaryTree& insert(const T &element);
        T top();
        T deleteTop();
        BinaryTree<T>& operator=(const BinaryTree<T> &tree);
        bool operator==(const BinaryTree<T> &tree);
        bool operator!=(const BinaryTree<T> &tree);
        void printFromNode(TreeNode<T> *node, const int indent = 0) const;
        friend std::ostream &operator<<(std::ostream &out, const BinaryTree<T> &tree) {
            tree.printFromNode(tree._root);
            return out;
        };
    };


    template<typename T> inline
    BinaryTree<T>::BinaryTree() {
        _root = new TreeNode<T>();
        _tail = _root;
        _size = 0;
    }

    template<typename T> inline
    BinaryTree<T>::BinaryTree(BinaryTree<T> &tree) {
        _root = new TreeNode<T>();
        _tail = _root;
        _size = 0;
        _copy(_root, tree._root);
    }

    template<typename T> inline
    BinaryTree<T>::~BinaryTree() {
        _delete(_root);
        delete _tail;
        _size = 0;
    }

    template<typename T> inline
    void BinaryTree<T>::_copy(TreeNode<T> *node, TreeNode<T> *node_src) {
        node->element = node_src->element;
        if (node_src->left() != nullptr) {
            node->insertLeft(new TreeNode<T>(node_src->left()->element));
            _tail = node->left();
            _size ++;
            _copy(node->left(), node_src->left());
        }
        if (node_src->right() != nullptr) {
            node->insertRight(new TreeNode<T>(node_src->right()->element));
            _tail = node->right();
            _size ++;
            _copy(node->right(), node_src->right());
        }
    }

    template<typename T> inline
    void BinaryTree<T>::_delete(TreeNode<T> *node){
        if (node == nullptr) {
            return;
        }
        _delete(node->left());
        _delete(node->right());
        delete node;
    }

    template <typename T> inline
    BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T>& tree) {
        _root = new TreeNode<T>();
        _tail = _root;
        _size = 0;
        _copy(_root, tree._root);
        return *this;
    }

    template <typename T> inline
    bool BinaryTree<T>::operator==(const BinaryTree<T>& tree) {
        return _root == tree._root;
    }

    template <typename T> inline
    bool BinaryTree<T>::operator!=(const BinaryTree<T>& tree) {
        return _root != tree._root;
    }

    template<typename T> inline
    void BinaryTree<T>::printFromNode(TreeNode<T> *node, const int indent) const {
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
    bool BinaryTree<T>::isEmpty() {
        return _root == _tail;
    }

    template <typename T> inline
    BinaryTree<T>& BinaryTree<T>::clear() {
        _delete(_root);
        _root = new TreeNode<T>();
        _tail = _root;
        _size = 0;
        return *this;
    }

    template <typename T> inline
    size_t BinaryTree<T>::size() {
        return _size;
    }

    template <typename T> inline
    bool BinaryTree<T>::_compare(const T &element1, const T &element2) {
        return element1 < element2;
    }

    template <typename T> inline
    void BinaryTree<T>::_exec(TreeNode<T> *node1, TreeNode<T> *node2) {
        auto tmp = node1->element;
        node1->element = node2->element;
        node2->element = tmp;
    }

    template <typename T> inline
    void BinaryTree<T>::_swim(TreeNode<T> *node) {
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
    void BinaryTree<T>::_sink(TreeNode<T> *node) {
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
    BinaryTree<T>& BinaryTree<T>::insert(const T &element) {
        if (_tail->left() == nullptr) {
            _tail->insertLeft(new TreeNode<T>(element));
            _tail = _tail->left();
        } else {
            _tail->insertRight(new TreeNode<T>(element));
            _tail = _tail->right();
        }
        _size++;
        _swim(_tail);
        return *this;
    }

    template<typename T> inline
    T BinaryTree<T>::top() {
        return _root->element;
    }

    template<typename T> inline
    T BinaryTree<T>::deleteTop() {
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
};


#endif //ALGORITHM_BINARY_HEAP_H
