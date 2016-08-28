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


namespace algorithm {
    using namespace std;
    using namespace data_structures;

    
    template <typename Unit>
    class Polynomail {
        
    private:
        LinkedList<Unit>* _list;
        
    public:
        Polynomail();
        Polynomail(const vector<Unit>& units);
        ~Polynomail();
        Polynomail<Unit> operator+(const Polynomail<Unit>& py);
        Polynomail<Unit> operator-(const Polynomail<Unit>& py);
        Polynomail<Unit> operator*(const Polynomail<Unit>& py);
        friend ostream& operator<<(ostream& out, Polynomail& py){
            auto tail = py._list->tail();
            for(auto node = py._list->header(); node <= tail; node ++) {
                cout << node->element << " + ";
            }
            cout << tail->element;
            return out;
        };
    };

    template <typename Unit> inline
    Polynomail<Unit>::Polynomail() {
        _list = new LinkedList<Unit>();
    }
    
    
    template <typename Unit> inline
    Polynomail<Unit>::Polynomail(const vector<Unit>& units) {
        _list = new LinkedList<Unit>();
        for (const Unit& unit: units) {
            _list->insertToTail(unit);
        }
    }
    
    template <typename Unit> inline
    Polynomail<Unit>::~Polynomail() {
        delete _list;
    }
    
    template <typename Unit> inline
    Polynomail<Unit> Polynomail<Unit>::operator+(const Polynomail<Unit>& py) {
        
    }
    
    template <typename Unit> inline
    Polynomail<Unit> Polynomail<Unit>::operator-(const Polynomail<Unit>& py) {
        
    }
    
    template <typename Unit> inline
    Polynomail<Unit> Polynomail<Unit>::operator*(const Polynomail<Unit>& py) {
        
    }
}


#endif /* polynomial_hpp */
