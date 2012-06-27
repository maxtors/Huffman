#include <iostream>
#include "Node.h"

// ---------- GET NODE FREQUENCY --------------------------------------------------------
double Node::getFrequency()     { return frequency; }

// ---------- LEFNODE CONSTRUCTOR -------------------------------------------------------
LeafNode::LeafNode(double f, char d) {
    left = right = NULL;
	frequency    = f;
	data         = d;
}

// ---------- LEAFNODE FILL -------------------------------------------------------------
void LeafNode::fill(std::map<char, std::vector<bool>>& enc, std::vector<bool>& bits) {
        enc[data] = bits;
}

// ---------- BINDNODE CONSTRUCTOR ------------------------------------------------------
BindNode::BindNode(Node* l, Node* r) {
    left        = l;
    right       = r;
    frequency   = (left->getFrequency() + right->getFrequency());
}

// ---------- BINDNODE DECONSTRUCTOR ----------------------------------------------------
BindNode::~BindNode() {
    delete left;
    delete right;
}

// ---------- BINDNODE FILL -------------------------------------------------------------
void BindNode::fill(std::map<char, std::vector<bool>>& enc, std::vector<bool>& bits) {
    
    bits.push_back(0);
    left->fill(enc, bits);
    bits.back() = 1;
    right->fill(enc, bits);
}