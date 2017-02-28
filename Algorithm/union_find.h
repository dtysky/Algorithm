//
//  union_find
//  Algorithm
//
//  Created by dtysky on 2017/2/27.
//  Copyright © 2017 dtysky@outlook.com. All rights reserved.
//

#ifndef ALGORITHM_UNION_FIND_H
#define ALGORITHM_UNION_FIND_H

#include <cstdio>
#include "red_black_tree.h"
#include "optional.hpp"


namespace my_algorithm {
    using std::experimental::optional;

    template <typename T>
    class UnionFind {
    protected:
        size_t _count;
        size_t _max_id;
        data_structures::RBTree<T, size_t> _table;
    public:
        UnionFind();
        UnionFind(const UnionFind<T>& uf);
        virtual ~UnionFind();
        size_t count();
        bool connected(T v, T w);
        optional<size_t> id(T v);
        void un(T v, T w);
        friend std::ostream &operator<<(std::ostream &out, UnionFind<T> &uf) {
            auto nodes = uf._table.getAllNodes();
            for (auto &node: nodes) {
                out << node->element.key << " " << node->element.value << std::endl;
            }
            return out;
        }
    };

    template <typename T> inline
    UnionFind<T>::UnionFind() {
        _max_id = 0;
        _count = 0;
        _table.clear();
    }

    template <typename T> inline
    UnionFind<T>::UnionFind(const UnionFind<T>& uf) {
        _max_id = uf._max_id;
        _count = uf._count;
        _table = uf._table;
    }

    template <typename T> inline
    UnionFind<T>::~UnionFind() {}

    template <typename T> inline
    size_t UnionFind<T>::count() {
        return _count;
    }

    template <typename T> inline
    bool UnionFind<T>::connected(T v, T w) {
        auto id_v = id(v);
        auto id_w = id(w);
        if (id_v && id_w) {
            return id_v == id_w;
        }
        return false;
    }

    template <typename T> inline
    optional<size_t> UnionFind<T>::id(T v) {
        try {
            return _table.get(v);
        } catch (std::out_of_range) {
            return optional<size_t>();
        }
    }

    template <typename T> inline
    void UnionFind<T>::un(T v, T w) {
        auto id_v = id(v);
        auto id_w = id(w);
        if (id_v && id_w) {
            // wait for completing
            auto nodes = _table.getAllNodes();
            if (id_v > id_w) {
                for (auto &node: nodes) {
                    if (node->element.value == id_w) {
                        node->element.value = id_v.value();
                    }
                }
            } else {
                for (auto &node: nodes) {
                    if (node->element.value == id_v) {
                        node->element.value = id_w.value();
                    }
                }
            }
        } else if (id_v) {
            _table.set(w, id_v.value());
        } else if (id_w) {
            _table.set(v, id_w.value());
        } else {
            _max_id++;
            _table.set(v, _max_id);
            _table.set(w, _max_id);
            _count++;
        }
    }
}

#endif //ALGORITHM_UNION_FIND_H
