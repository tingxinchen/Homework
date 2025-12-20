#ifndef CHAIN_H
#define CHAIN_H

#include "ChainNode.h"
#include "ChainIterator.h"

template <class T>
class Chain {
public:
    typedef ChainIterator<T> iterator;

protected:
    ChainNode<T>* header;

public:
    Chain() {
        header = new ChainNode<T>();
        header->link = header;   // Àôª¬
    }

    ~Chain() {
        Release();
        delete header;
    }

    bool IsEmpty() const {
        return header->link == header;
    }

    iterator Begin() const {
        return iterator(header->link);
    }

    iterator End() const {
        return iterator(header);
    }

    void InsertBack(const T& x) {
        ChainNode<T>* node = new ChainNode<T>(x);

        ChainNode<T>* cur = header;
        while (cur->link != header)
            cur = cur->link;

        node->link = header;
        cur->link = node;
    }

    void Release() {
        ChainNode<T>* cur = header->link;
        while (cur != header) {
            ChainNode<T>* temp = cur;
            cur = cur->link;
            delete temp;
        }
        header->link = header;
    }
};

#endif
