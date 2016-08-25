//
//  list_node.hpp
//  Algorithm
//
//  Created by DaiTianyu on 16/8/22.
//  Copyright © 2016年 dtysky@outlook.com. All rights reserved.
//

#ifndef list_node_hpp
#define list_node_hpp

#include <stdio.h>
#include <iostream>
using namespace std;


namespace data_structures {
    template <class T>
    class ListNode{
        
    private:
        ListNode<T>* _next;
        
    public:
        T element;
        ListNode();
        ListNode(const T& element, ListNode<T>* next_node = nullptr);
        ListNode(const ListNode<T>* node);
        void insertAfter(ListNode<T>* node);
        ListNode<T>* deleteAfter();
        ListNode<T>* next() const;
        friend ostream& operator<<(ostream& out, const ListNode<T>& node){
            cout << "Current: " << &node << ", Element: " << node.element << ", Next: " << node._next;
            return out;
        };
    };
    
    void testListNode();
    
}

#endif /* list_node_hpp */
