#ifndef NODE_H
#define NODE_H

// ---------- INCLUDES ------------------------------------------------------------------
#include <map>
#include <vector>
#include <string>

// ---------- NODE CLASS ----------------------------------------------------------------

enum NODE_TYPE {LEAF, BIND};

class Node {
private:
    NODE_TYPE type;
    short frequency;
    char* data;
    Node* left;
    Node* right;
public:
    Node(char d, short s, NODE_TYPE t = LEAF);
    Node(Node* l, Node* r, NODE_TYPE t = BIND);
    ~Node();
    short  getFrequency();
    void    fill(std::map<char, std::pair<int, int>>& enc, int bits, int nbits);
};

#endif