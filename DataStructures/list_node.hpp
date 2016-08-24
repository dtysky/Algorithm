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
        ListNode<T>* next;
        T data;
        
    public:
        ListNode();
        ListNode(const T& data, ListNode<T>* next_node = nullptr);
        void insertAfter(ListNode<T>* node);
        ListNode<T>* deleteAfter();
        void setData(T data);
        T getData();
        ListNode<T>* nextNode();
        friend ostream& operator<<(ostream& out, const ListNode<T>& node){
            cout << "Current: " << &node << ", Data: " << node.data << ", Next: " << node.next;
            return out;
        };
    };
    
    
#ifdef test_data_structure_list_node
    void test();
#endif
    
}

#endif /* list_node_hpp */
