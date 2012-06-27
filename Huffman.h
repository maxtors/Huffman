#ifndef HUFFMAN_H
#define HUFFMAN_H

// ---------- INCLUDES --------------------------------------------------------
#include <map>
#include <vector>
#include <string>
#include "Node.h"

// ---------- HUFFMAN CLASS ---------------------------------------------------
class Huffman {
private:
    Node*                               tree;
    std::map<char, std::vector<bool>>*  encoded;
    std::map<char, double>*             frequencies;
    std::map<char, double>*             getFrequencies(std::string s);
    void                                Sort(std::vector<Node*>& v);

public:
    Huffman(std::string s);
    ~Huffman();
    void buildTree();
    void showTree();
};

#endif