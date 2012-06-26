#ifndef NODE_H
#define NODE_H

class Node {
protected:
	double	frequency;
	Node*	left;
	Node*	right;
public:
	Node()			{}
	virtual ~Node()	{}

	double getFrequency();
};

class LeafNode : public Node {
private:
	char data;
public:
	LeafNode(double f, char d);
	~LeafNode()		{}
};

class BindNode : public Node {
private:
public:
	BindNode(Node* l, Node* r);
	~BindNode();
};

#endif