#ifndef NODE_H
#define NODE_H

class Node {
protected:
	double frequency;
	Node* left;
	Node* right;

public:
	Node();
	virtual ~Node();
};

class LeafNode : public Node {
private:

public:
	LeafNode(double f, char d);
};

class BindNode public Node {
private:
public:
	BindNode(Node* l, Node* r);
};

#endif