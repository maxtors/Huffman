#ifndef HUFFMAN_H
#define HUFFMAN_H

// ---------- INCLUDES --------------------------------------------------------
#include <map>
#include <vector>
#include <string>
#include "Node.h"

// ---------- TYPEDEFS --------------------------------------------------------
typedef std::map<char, std::vector<bool>> Encode_map;
typedef std::map<char, double> Frequencies;

// ---------- HUFFMAN CLASS ---------------------------------------------------
class Huffman {
private:
    Node*        tree;
    Encode_map*	 encoded;
    Frequencies* frequencies;

    Frequencies* getFrequencies(std::string s);
    void         Sort(std::vector<Node*>& v)

public:
    Huffman(std::string s);
    ~Huffman();

    void buildTree();
};

#endif