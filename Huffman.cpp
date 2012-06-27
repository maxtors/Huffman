#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include "Huffman.h"
#include "Node.h"


// ---------- CONSTRUCTOR -----------------------------------------------------
Huffman::Huffman(std::string s) {
    encoded	    = new Encode_map;
    frequencies = getFrequencies(s);
}

// ---------- DECONSTRUCTOR ---------------------------------------------------
Huffman::~Huffman() {
    delete encoded;
    delete frequencies;
}

// ---------- GET FREQUENCY OF EACH CHAR --------------------------------------
Frequencies* Huffman::getFrequencies(std::string s) {
    Frequencies*            f = new Frequencies;
    Frequencies::iterator   f_it;
	
    // Loop through the parameter string, and treat each character
    for (unsigned int i = 0; i < s.length(); i++) {
        // If the char is in the map, add one, if not, insert into map
        f_it = f->find(s[i]);
        if (f_it == f->end()) f->insert(std::pair<char, double>(s[i], 1.0f));
        else                  (*f)[s[i]] += 1.0f;
    }

    // Get percentage frequency of each character
    f_it = f->begin();
    while (f_it != f->end()) {
        (*f)[(f_it)->first] /= s.size();
        f_it++;
    }

    // Return the mapping of character frequencies
    return f;
}

// ---------- SORT THE LIST OF NODES ------------------------------------------
void Huffman::Sort(std::vector<Node*>& v) {
	bool swap = true;
	int  n 	  = v.size(), i;
	
	// Simple bubble sort
	while (swap) {	
	    swap = false;
	    for (i = 1; i <= n - 1; i++) {
            if (v[i-1]->getFrequency() > v[i]->getFrequency()) {
                std::swap(v[i-1], v[i]);
	    		swap = true;
	    	}
	    }
	    n -= 1;
	}
}

// ---------- BUILD THE HUFFMAN TREE ------------------------------------------
void Huffman::buildTree() {
    std::vector<Node*>      nodes;
    std::vector<bool>       bits;
    Node*                   n1, *n2;
    Frequencies             temp = *frequencies;
    Frequencies::iterator   f_it, lowest;

    // Loop til map is empty
    while (!temp.empty()) {
        f_it    = temp.begin();
        lowest  = f_it;

        // Loop through all the elements
        while (f_it != temp.end()) {
            if (f_it->second < lowest->second) lowest = f_it;
            ++f_it;
        }
        
        // Create new leafnode and add to vector
        nodes.push_back(new LeafNode(lowest->second, lowest->first));
        temp.erase(lowest);
    }
	
	// Create the Huffman tree
    while (nodes.size() != 1) {
    	
    	// Create new binding node, erase used nodes, and sort vector
    	nodes.push_back(new BindNode(nodes.at(0), nodes.at(1)));
        nodes.erase(nodes.begin(), nodes.begin()+2);
    	Sort(nodes);
    }

    // Set tree pointer, and fill the tree...
    tree = nodes.at(0);
    tree->fill(*encoded, bits);
}

// ---------- SHOW THE HUFFMAN TREE -------------------------------------------
void Huffman::showTree() {
    Encode_map::iterator        e_it;
    std::vector<bool>::iterator b_it;

    // Loop through all the characters
    for (e_it = encoded->begin(); e_it != encoded->end(); e_it++) {
        std::cout << e_it->first << ": ";

        // Loop through all the boolean variables
        for (b_it = e_it->second.begin(); b_it != e_it->second.end(); b_it++) {
            std::cout << *b_it;
        }
        std::cout << "\n";
    }
}