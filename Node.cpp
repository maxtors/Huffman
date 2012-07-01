#include <iostream>
#include "Node.h"

// ---------- NODE (LEAF) CONSTRUCTOR ---------------------------------------------------
Node::Node(char d, int s, NODE_TYPE t) {
    type = t;
    data = d;
    frequency = s;
    left = right = NULL;
}

// ---------- NODE (BIND) CONSTRUCTOR ---------------------------------------------------
Node::Node(Node* l, Node* r, NODE_TYPE t) {
    type = t;
    data = 0;
    frequency = l->getFrequency() + r->getFrequency();
    left = l;
    right = r;
}

// ---------- NODE DECONSTRUCTOR --------------------------------------------------------
Node::~Node() {
    delete left;
    delete right;
}

// ---------- GET NODE FREQUENCY --------------------------------------------------------
int Node::getFrequency() {
    return frequency;
}

// ---------- FILL NODE WITH DATA -------------------------------------------------------
void Node::fill(std::map<char, std::pair<int, int>>& enc, int bits, int nbits) {
    if (type == LEAF) {
        enc[data] = std::pair<int, int>(bits, nbits);
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