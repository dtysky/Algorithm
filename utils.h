//
//  utils.hpp
//  Algorithm
//
//  Created by dtysky on 16/8/31.
//  Copyright © 2016年 dtysky@outlook.com. All rights reserved.
//

#ifndef utils_hpp
#define utils_hpp

#include <cstdio>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <assert.h>
#include <array>
#include <iomanip>
#include <cmath>
#include <deque>
#include <string>
#include <sstream>


template <typename T>
void printVector(std::vector<T>& a) {
    for (auto i: a) {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}

template <typename T>
bool isInVector(const std::vector<T>& v, const T& e) {
    return std::find(v.begin(), v.end(), e) != v.end();
}

void fillVectorWithRandomNumbers(std::vector<uint32_t >& v, const uint32_t max, const uint32_t seed = 0) {
    auto size = v.size();
    srand(seed);

    for (size_t i = 0; i < size; i++) {
        v[i] = float(max) * rand() / RAND_MAX;
    }
}

void fillVectorWithRangeNumbers(std::vector<uint32_t >& v, const uint32_t max, const uint32_t seed = 0) {
    auto size = v.size();
    for (size_t i = 0; i < size; i++) {
        v[i] = i;
    }
}

void compareTwoVectorsWithAssert(std::vector<uint32_t >& v1, std::vector<uint32_t >& v2) {
    std::cout << std::endl;
    assert(v1 == v2);
}

template <typename T>
std::vector<T> refSort(const std::vector<T>& v) {
    auto tmp = v;
    std::sort(tmp.begin(), tmp.end());
    return tmp;
}



template <typename BinaryTreeNode>
std::string nodeToString(BinaryTreeNode* node) {
    std::ostringstream ss;
    ss << node->element << "(" << node->node_count << ")";
    return ss.str();
}

// Find the maximum height of the binary tree
template <typename BinaryTreeNode>
int maxHeight(BinaryTreeNode *p) {
    if (!p) return 0;
    int leftHeight = maxHeight(p->left());
    int rightHeight = maxHeight(p->right());
    return (leftHeight > rightHeight) ? leftHeight + 1: rightHeight + 1;
}

// Print the arm branches (eg, /    \ ) on a line
template <typename BinaryTreeNode>
void printBranches(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const std::deque<BinaryTreeNode*>& nodesQueue, std::ostream& out) {
    typename std::deque<BinaryTreeNode*>::const_iterator iter = nodesQueue.begin();
    for (int i = 0; i < nodesInThisLevel / 2; i++) {
        out << ((i == 0) ? std::setw(startLen-1) : std::setw(nodeSpaceLen-2)) << "" << ((*iter++) ? "/" : " ");
        out << std::setw(2*branchLen+2) << "" << ((*iter++) ? "\\" : " ");
    }
    out << std::endl;
}

// Print the branches and node (eg, ___10___ )
template <typename BinaryTreeNode>
void printNodes(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const std::deque<BinaryTreeNode*>& nodesQueue, std::ostream& out) {
    typename std::deque<BinaryTreeNode*>::const_iterator iter = nodesQueue.begin();
    for (int i = 0; i < nodesInThisLevel; i++, iter++) {
        out << ((i == 0) ? std::setw(startLen) : std::setw(nodeSpaceLen)) << "" << ((*iter && (*iter)->left()) ? std::setfill('_') : std::setfill(' '));
        out << std::setw(branchLen+2);
        if ((*iter)) {
            out << (*iter)->toString();
        } else {
            out << "";
        }
        out << ((*iter && (*iter)->right()) ? std::setfill('_') : std::setfill(' ')) << std::setw(branchLen) << "" << std::setfill(' ');
    }
    out << std::endl;
}

// Print the leaves only (just for the bottom row)
template <typename BinaryTreeNode>
void printLeaves(int indentSpace, int level, int nodesInThisLevel, const std::deque<BinaryTreeNode*>& nodesQueue, std::ostream& out) {
    typename std::deque<BinaryTreeNode*>::const_iterator iter = nodesQueue.begin();
    for (int i = 0; i < nodesInThisLevel; i++, iter++) {
        out << ((i == 0) ? std::setw(indentSpace+2) : std::setw(2*level+2));
        if ((*iter)) {
            out << (*iter)->toString();
        } else {
            out << "";
        }
    }
    out << std::endl;
}

// Pretty formatting of a binary tree to the output stream
// @ param
// level  Control how wide you want the tree to sparse (eg, level 1 has the minimum space between nodes, while level 2 has a larger space between nodes)
// indentSpace  Change this to add some indent space to the left (eg, indentSpace of 0 means the lowest level of the left node will stick to the left margin)
template <typename BinaryTreeNode>
void printBinaryTree(BinaryTreeNode *root, int level, int indentSpace, std::ostream& out) {
    int h = maxHeight(root);
    int nodesInThisLevel = 1;

    int branchLen = 2*((int)pow(2.0,h)-1) - (3-level)*(int)pow(2.0,h-1);  // eq of the length of branch for each node of each level
    int nodeSpaceLen = 2 + (level+1)*(int)pow(2.0,h);  // distance between left neighbor node's right arm and right neighbor node's left arm
    int startLen = branchLen + (3-level) + indentSpace;  // starting space to the first node to print of each level (for the left most node of each level only)

    typename std::deque<BinaryTreeNode*> nodesQueue;
    nodesQueue.push_back(root);
    for (int r = 1; r < h; r++) {
        printBranches(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue, out);
        branchLen = branchLen/2 - 1;
        nodeSpaceLen = nodeSpaceLen/2 + 1;
        startLen = branchLen + (3-level) + indentSpace;
        printNodes(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue, out);

        for (int i = 0; i < nodesInThisLevel; i++) {
            BinaryTreeNode *currNode = nodesQueue.front();
            nodesQueue.pop_front();
            if (currNode) {
                nodesQueue.push_back(currNode->left());
                nodesQueue.push_back(currNode->right());
            } else {
                nodesQueue.push_back(NULL);
                nodesQueue.push_back(NULL);
            }
        }
        nodesInThisLevel *= 2;
    }
    printBranches(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue, out);
    printLeaves(indentSpace, level, nodesInThisLevel, nodesQueue, out);
}


#endif /* utils_hpp */
