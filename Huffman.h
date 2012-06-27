#ifndef HUFFMAN_H
#define HUFFMAN_H

// ---------- INCLUDES ------------------------------------------------------------------
#include <map>
#include <vector>
#include <string>
#include "Node.h"

// ---------- HUFFMAN CLASS -------------------------------------------------------------
class Huffman {
private:
    Node*                               tree;
    std::string                         decodedResult;
    std::vector<bool>                   encodedResult;
    std::map<char, std::vector<bool>>*  encodingMap;
    std::map<char, double>*             frequencies;
    std::map<char, double>*             getFrequencies(std::string s);
    void Sort(std::vector<Node*>& v);
    void buildTree();
    void showTree();
    std::vector<bool> buildEncodedResult(std::string s);
public:
    Huffman();
    ~Huffman();
    void encode(std::string s);
    void decode(std::string s);
};

#endif