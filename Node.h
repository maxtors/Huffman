#ifndef NODE_H
#define NODE_H

// ---------- INCLUDES ------------------------------------------------------------------
#include <map>
#include <vector>
#include <string>

enum NODE_TYPE {LEAF, BIND};

// ---------- NODE CLASS ----------------------------------------------------------------
class Node {
private:
    NODE_TYPE type;
    int   frequency;
    char  data;
    Node* left;
    Node* right;
public:
    Node(char d, int s, NODE_TYPE t = LEAF);
    Node(Node* l, Node* r, NODE_TYPE t = BIND);
    ~Node();
    int  getFrequency();
    void fill(std::map<char, std::pair<int, int>>& enc, int bits, int nbits);
};

#endif