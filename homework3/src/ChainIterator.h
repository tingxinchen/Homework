#ifndef CHAINITERATOR_H
#define CHAINITERATOR_H

#include "ChainNode.h"

template <class T>
class ChainIterator {
private:
    ChainNode<T>* current;

public:
    ChainIterator(ChainNode<T>* node = nullptr)
        : current(node) {}

    T& operator*() {
        return current->element;
    }

    ChainNode<T>* operator->() {
        return current;
    }

    ChainIterator<T>& operator++() {
        current = current->link;
        return *this;
    }

    bool operator!=(const ChainIterator<T>& rhs) const {
        return current != rhs.current;
    }

    bool operator==(const ChainIterator<T>& rhs) const {
        return current == rhs.current;
    }

    ChainNode<T>* GetNode() const {
        return current;
    }
};

#endif
