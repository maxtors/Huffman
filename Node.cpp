#include <iostream>
#include "Node.h"

// ---------- NODE (LEAF) CONSTRUCTOR ---------------------------------------------------
Node::Node(char d, short s, NODE_TYPE t) {
    type = t;
    data = new char[2]; data[0] = d; data[1] = '\0';
    frequency = s;
    left = right = NULL;
}

// ---------- NODE (BIND) CONSTRUCTOR ---------------------------------------------------
Node::Node(Node* l, Node* r, NODE_TYPE t) {
    type = t;
    data = NULL;
    frequency = l->getFrequency() + r->getFrequency();
    left = l;
    right = r;
}

// ---------- NODE DECONSTRUCTOR --------------------------------------------------------
Node::~Node() {
    delete data;
    delete left;
    delete right;
}

// ---------- GET NODE FREQUENCY --------------------------------------------------------
short Node::getFrequency() {
    return frequency;
}

// ---------- FILL NODE WITH DATA -------------------------------------------------------
void Node::fill(std::map<char, std::pair<int, int>>& enc, int bits, int nbits) {
    if (type == LEAF) {
        enc[data[0]] = std::pair<int, int>(bits, nbits);
    }
    else if (type == BIND) {
        nbits += 1;
        bits <<= 1;
        left->fill(enc, bits, nbits);
        bits += 1;
        right->fill(enc, bits, nbits);
        bits >>= 1;
        nbits--;
    }
}