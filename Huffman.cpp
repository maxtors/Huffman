#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include "Huffman.h"
#include "Node.h"


// ---------- CONSTRUCTOR -----------------------------------------------------
Huffman::Huffman(std::string s) {
    encoded	= new Encode_map;
    frequencies = getFrequencies(s);
}

// ---------- DECONSTRUCTOR ---------------------------------------------------
Huffman::~Huffman() {
    delete encoded;
    delete frequencies;
}

// ---------- GET FREQUENCY OF EACH CHAR --------------------------------------
Frequencies* Huffman::getFrequencies(std::string s) {
    Frequencies* f = new Frequencies;
    Frequencies::iterator f_it;
	
    // Loop through the parameter string, and treat each character
    for (unsigned int i = 0; i < s.length(); i++) {

        // If the char is in the map, add one, if not, insert into map
        f_it = f->find(s[i]);
        if (f_it == f->end()) {
            f->insert(std::pair<char, double>(s[i], 1.0f));
        }
        else {
            (*f)[s[i]] += 1.0f;
        }
    }

    // Get percentage frequency of each character
    f_it = f->begin();
    while (f_it != f->end()) {
        (*f)[f_it->first] /= s.size();
        f_it++;
    }

    // Return the mapping of character frequencies
    return f;
}

// ---------- SORT THE LIST OF NODES ------------------------------------------
void Huffman::Sort(std::vector<Node*>& v) {
	bool 	swap = true;
	int 	n 	 = v.size();
	Node* 	temp;
	
	// Simple bubble sort
	while (swap) {	
	    swap = false;
	    for (int i = 1; i < n - 1; i++) {
	    	if (v[i-1] > v[i]) {
	    		temp = v[i];
	    		v[i] = v[i-1];
	    		v[i-1] = temp;
	    		swap = true;
	    	}
	    }
	    n -= 1;
	}
}

// ---------- BUILD THE HUFFMAN TREE ------------------------------------------
void Huffman::buildTree() {
    std::vector<Node*> nodes;
    Node* newnode, n1, n2;
    Frequencies temp = *frequencies;
    Frequencies::iterator f_it, lowest;

    // Loop til map is empty
    while (!temp.empty()) {   

        f_it = temp.begin();
        lowest = f_it;

        // Loop through all the elements
        while (f_it != temp.end()) {

            if (f_it->second < lowest->second) {
                lowest = f_it;
            }
            ++f_it;
        }
        
        // Create new leafnode and add to vector
        newnode = new LeafNode(lowest->second, lowest->first);
        nodes.push_back(newnode);
        temp.erase(lowest);
    }
	
	// Create the Huffman tree
    while (nodes.size() != 1) {
    	n1 = nodes.at(0);
    	n2 = nodes.at(1);
    	
    	// Create new binding node
    	newnode = new BindNode(n1, n2);
    	nodes.push_back(newnode);
    	
    	// Remove the two first elements
    	nodes.erase(nodes.begin());
    	nodes.erase(nodes.begin());
    	
    	Sort(nodes);
    }
    
    // VED NÅ ER DET BARE EN NODE IGJEN.
    // OG ALT ER ORGANISERT I ET TREE
    // DERETTER MÅ DET FYLLES UT BINÆR VERDIER
}