#pragma once
#include <vector>
using namespace std;

#ifndef UNTITLED23_CONTAINER_H
#define UNTITLED23_CONTAINER_H

#endif //UNTITLED23_CONTAINER_H
template<typename T>
class Container {
    vector<T*> items;
public:
    Container() {}

    void add(T* item) {
        items.push_back(item);
    }

    T* get(size_t index) const {
        if (index < items.size()) return items[index];
        return nullptr;
    }

    const vector<T*>& getAll() const { return items; }

    size_t size() const { return items.size(); }

    void remove(size_t index) {
        if (index < items.size()) {
            delete items[index];
            items.erase(items.begin() + index);
        }
    }

    ~Container() {
        for (auto* item : items)
            delete item;
        items.clear();
    }
};
