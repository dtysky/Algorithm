//
//  polynomial.hpp
//  Algorithm
//
//  Created by dtysky on 16/8/28.
//  Copyright © 2016年 dtysky@outlook.com. All rights reserved.
//

#ifndef polynomial_hpp
#define polynomial_hpp

#include <cstdio>
#include <vector>
#include "linked_list.h"
#include "polynomial_unit.h"


namespace data_structures {
    using std::cout;
    using std::ostream;
    using std::vector;
    
    template <typename Unit, typename Value>
    class Polynomail : public LinkedList<Unit> {

    public:
        Polynomail(): LinkedList<Unit>(){};
        Polynomail(const Polynomail<Unit, Value>& py): LinkedList<Unit>(py){};
        Polynomail(const vector<Unit>& units);
        Value eval(const Value& x);
        Polynomail<Unit, Value> operator-() const;
        Polynomail<Unit, Value> operator-();
        Polynomail<Unit, Value> operator+(const Polynomail<Unit, Value>& py);
        Polynomail<Unit, Value> operator-(const Polynomail<Unit, Value>& py);
        Polynomail<Unit, Value> operator*(const Polynomail<Unit, Value>& py);
        friend ostream& operator<<(ostream& out, const Polynomail<Unit, Value>& py){
            auto tail = py.tail();
            for(auto node = py.begin(); node != py.end(); node = node->next()) {
                out << node->element << (node == tail ? "" : " + ");
            }
            return out;
        };
    };
    
    template <typename Unit, typename Value> inline
    Polynomail<Unit, Value>::Polynomail(const vector<Unit>& units) {
        this->_header = new ListNode<Unit>();
        auto _current = this->_header;
        for (const Unit& unit: units) {
            _current->insertAfter(new ListNode<Unit>(unit));
            _current = _current->next();
        }
    }
    
    template <typename Unit, typename Value> inline
    Value Polynomail<Unit, Value>::eval(const Value& x) {
        Value _result = Value();
        for(auto node = this->begin(); node != this->end(); node = node->next()) {
            _result += node->element.eval(x);
        }
        return _result;
    }
    
    template <typename Unit, typename Value> inline
    Polynomail<Unit, Value> Polynomail<Unit, Value>::operator-() const {
        auto _result = Polynomail<Unit, Value>(*this);
        for(auto node = _result.begin(); node != _result.end(); node = node->next()) {
            node->element.coefficient = -node->element.coefficient;
        }
        return _result;
    }
    
    template <typename Unit, typename Value> inline
    Polynomail<Unit, Value> Polynomail<Unit, Value>::operator-() {
        auto _result = Polynomail<Unit, Value>(*this);
        for(auto node = _result.begin(); node != _result.end(); node = node->next()) {
            node->element.coefficient = -node->element.coefficient;
        }
        return _result;
    }
    
    template <typename Unit, typename Value> inline
    Polynomail<Unit, Value> Polynomail<Unit, Value>::operator+(const Polynomail<Unit, Value>& py) {
        if (this->isEmpty()) {
            return py;
        }
        if (py.isEmpty()) {
            return *this;
        }
        auto _result = Polynomail<Unit, Value>();
        auto _result_node = _result._header;
        auto element = Unit();
        auto n1 = this->begin();
        auto n2 = py.begin();
        // nodes in lists are plused are from big to small
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
            if (element.isZero()) {
                continue;
            }
            _result_node->insertAfter(new ListNode<Unit>(element));
            _result_node = _result_node->next();
        }
        return _result;
    }
    
    template <typename Unit, typename Value> inline
    Polynomail<Unit, Value> Polynomail<Unit, Value>::operator-(const Polynomail<Unit, Value>& py) {
        if (py.isEmpty()) {
            return *this;
        }
        auto _tmp = -py;
        if (this->isEmpty()) {
            return _tmp;
        }
        return *this + _tmp;
    }

    
    template <typename Unit, typename Value> inline
    Polynomail<Unit, Value> Polynomail<Unit, Value>::operator*(const Polynomail<Unit, Value>& py) {
        auto _result = Polynomail<Unit, Value>();
        if (this->isEmpty() || py.isEmpty()) {
            return _result;
        }
        for (auto n1 = this->begin(); n1 != this->end(); n1 = n1 -> next()) {
            auto _tmp = Polynomail<Unit, Value>();
            auto _tmp_node = _tmp._header;
            for (auto n2 = py.begin(); n2 != py.end(); n2 = n2 -> next()) {
                _tmp_node->insertAfter(new ListNode<Unit>({
                    n1->element.exponent + n2->element.exponent,
                    n1->element.coefficient * n2->element.coefficient,
                }));
                _tmp_node = _tmp_node->next();
            }
            _result = _result + _tmp;
        }
        return _result;
    }
}


#endif /* polynomial_hpp */
