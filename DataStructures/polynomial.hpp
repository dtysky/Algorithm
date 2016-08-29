//
//  polynomial.hpp
//  Algorithm
//
//  Created by DaiTianyu on 16/8/28.
//  Copyright © 2016年 dtysky@outlook.com. All rights reserved.
//

#ifndef polynomial_hpp
#define polynomial_hpp

#include <stdio.h>
#include <vector>
#include "linked_list.hpp"
#include "polynomial_unit.hpp"


namespace data_structures {
    using namespace std;
    
    template <typename Unit>
    class Polynomail : public LinkedList<Unit> {

    public:
        Polynomail(): LinkedList<Unit>(){};
        Polynomail(const Polynomail<Unit>& py): LinkedList<Unit>(py){};
        Polynomail(const vector<Unit>& units);
        Polynomail<Unit> operator+(const Polynomail<Unit>& py);
        Polynomail<Unit> operator-(const Polynomail<Unit>& py);
        Polynomail<Unit> operator*(const Polynomail<Unit>& py);
        friend ostream& operator<<(ostream& out, const Polynomail<Unit>& py){
            auto tail = py.tail();
            for(auto node = py.header(); node != py.end(); node = node->next()) {
                cout << node->element << (node == tail ? "" : " + ");
            }
            return out;
        };
    };
    
    template <typename Unit> inline
    Polynomail<Unit>::Polynomail(const vector<Unit>& units) {
        this->_header = new ListNode<Unit>();
        auto _current = this->_header;
        for (const Unit& unit: units) {
            _current->insertAfter(new ListNode<Unit>(unit));
            _current = _current->next();
        }
    }
    
    template <typename Unit> inline
    Polynomail<Unit> Polynomail<Unit>::operator+(const Polynomail<Unit>& py) {
        if (this->isEmpty()) {
            return py;
        }
        if (py.isEmpty()) {
            return *this;
        }
        auto _result = Polynomail<Unit>();
        auto _result_node = _result._header;
        auto element = Unit();
        auto n1 = this->header();
        auto n2 = py.header();
        
        while (n1 != this->end() || n2 != py.end()) {
            if (n1 == this->end()){
                element.exponent = n2->element.exponent;
                element.coefficient = n2->element.coefficient;
                n2 = n2->next();
            }
            else if (n2 == py.end()) {
                element.exponent = n1->element.exponent;
                element.coefficient = n1->element.coefficient;
                n1 = n1->next();
            }
            else if (n1->element.exponent > n2->element.exponent) {
                element.exponent = n1->element.exponent;
                element.coefficient = n1->element.coefficient;
                n1 = n1->next();
            }
            else if (n1->element.exponent < n2->element.exponent) {
                element.exponent = n2->element.exponent;
                element.coefficient = n2->element.coefficient;
                n2 = n2->next();
            }
            else {
                element.exponent = n1->element.exponent;
                element.coefficient = n1->element.coefficient + n2->element.coefficient;
                n1 = n1->next();
                n2 = n2->next();
            }
            _result_node->insertAfter(new ListNode<Unit>(element));
            _result_node = _result_node->next();
        }
        return _result;
    }
    
    template <typename Unit> inline
    Polynomail<Unit> Polynomail<Unit>::operator-(const Polynomail<Unit>& py) {
        
    }
    
    template <typename Unit> inline
    Polynomail<Unit> Polynomail<Unit>::operator*(const Polynomail<Unit>& py) {
        
    }
}


#endif /* polynomial_hpp */
