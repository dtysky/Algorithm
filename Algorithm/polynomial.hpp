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

    
    template <typename Units>
    class Polynomail {
        
    private:
        LinkedList<Units>* _list;
        
    public:
        Polynomail();
        Polynomail(const vector<Units>& units);
        ~Polynomail();
        friend ostream& operator<<(ostream& out, Polynomail& py){
            if (py._list->isEmpty()) {
                return out;
            }
            ListNode<Units>* _current = py._list->header();
            while (!py._list->isTail(_current)) {
                cout << _current->element << " + ";
                _current = _current->next();
            }
            cout << _current->element;
            return out;
        };
    };

    template <typename Units> inline
    Polynomail<Units>::Polynomail() {
        _list = new LinkedList<Units>();
    }
    
    
    template <typename Units> inline
    Polynomail<Units>::Polynomail(const vector<Units>& units) {
        _list = new LinkedList<Units>();
        for (const Units& unit: units) {
            _list->insertToTail(unit);
        }
    }
    
    template <typename Units> inline
    Polynomail<Units>::~Polynomail() {
        delete _list;
    }
}


#endif /* polynomial_hpp */
