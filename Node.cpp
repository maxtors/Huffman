#include <iostream>
#include "Node.h"

// ---------- GET NODE FREQUENCY ----------------------------------------------
double Node::getFrequency() { return frequency; }

// ---------- LEFNODE CONSTRUCTOR ---------------------------------------------
LeafNode::LeafNode(double f, char d) {
	frequency   = f;
	left        = NULL;
	right       = NULL;
	data        = d;
}

// ---------- LEAFNODE FILL ---------------------------------------------------
void LeafNode::fill(Encode_map& enc, std::vector<bool>& bits) {
    enc[data] = bits;
}

// ---------- BINDNODE CONSTRUCTOR --------------------------------------------
BindNode::BindNode(Node* l, Node* r) {
    frequency   = (left->getFrequency() + right->getFrequency());
    left        = l;
    right       = r;
}

// ---------- BINDNODE DECONSTRUCTOR ------------------------------------------
BindNode::~BindNode() {
    delete left;
    delete right;
}

// ---------- BINDNODE FILL ---------------------------------------------------
void BindNode::fill(Encode_map& enc, std::vector<bool>& bits) {
    bits.push_back(0);
    left->fill(enc, bits);
    bits.back() = 1;
    right->fill(enc, bits);
}