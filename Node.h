#ifndef NODE_H
#define NODE_H

// ---------- INCLUDES --------------------------------------------------------
#include <map>
#include <vector>
#include <string>

// ---------- TYPEDEFS --------------------------------------------------------
typedef std::map<char, std::vector<bool>> Encode_map;

// ---------- NODE CLASS ------------------------------------------------------
class Node {
protected:
    double	frequency;
    Node*	left;
    Node*	right;
public:
    Node()			{}
    virtual ~Node()	{}
    virtual void fill(Encode_map& enc, std::vector<bool>& bits) = 0;
    double getFrequency();
};

// ---------- LEAFNODE CLASS --------------------------------------------------
class LeafNode : public Node {
private:
    char data;
public:
    LeafNode(double f, char d);
    ~LeafNode()		{}
    void fill(Encode_map& enc, std::vector<bool>& bits);
};

// ---------- BINDNODE CLASS --------------------------------------------------
class BindNode : public Node {
private:
public:
    BindNode(Node* l, Node* r);
    ~BindNode();
    void fill(Encode_map& enc, std::vector<bool>& bits);
};

#endif