#ifndef CHAINNODE_H
#define CHAINNODE_H

template <class T>
class ChainNode {
public:
    T element;
    ChainNode<T>* link;

    ChainNode(const T& e = T(), ChainNode<T>* l = nullptr)
        : element(e), link(l) {}
};

#endif