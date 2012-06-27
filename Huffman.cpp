#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include "Huffman.h"
#include "Node.h"


// ---------- CONSTRUCTOR ---------------------------------------------------------------
Huffman::Huffman() {
    encodingMap = new std::map<char, std::vector<bool>>;
    frequencies = NULL;
}

// ---------- DECONSTRUCTOR -------------------------------------------------------------
Huffman::~Huffman() {
    delete encodingMap;
    delete frequencies;
}

// ---------- ENCODE STRING -------------------------------------------------------------
void Huffman::encode(std::string s) {

    /*
        -> REVIEW AND CLEAN
    */
    delete frequencies;
    frequencies = getFrequencies(s);
    buildTree();
    showTree();

    encodedResult = buildEncodedResult(s);
    std::cout << "\n\n" << s << " = ";
    showBoolVector(encodedResult);

    /*
        MAKE THIS PART AS A FUNCTION
    */
    int nSize = s.length() * 8;
    int eSize = encodedResult.size();
    float comp = 1 - ((float)eSize / (float)nSize);

    std::cout << "\n\nAmount of bytes in regular string: " << nSize;
    std::cout << "\nAmount of bytes in encoded string: " << eSize;
    std::cout << "\nCompression: " << comp * 100 << "%";
}

// ---------- DECODE STRING -------------------------------------------------------------
void Huffman::decode(std::string s) {
    // NOT STARTED
}

// ---------- MAKE ENCODED STRING FROM ENCODING MAP -------------------------------------
std::vector<bool> Huffman::buildEncodedResult(std::string s) {
    std::map<char, std::vector<bool>>::iterator m_it;
    std::string::iterator                       s_it;
    std::vector<bool>                           result;

    // Loop through the string the user wants to encode
    for (s_it = s.begin(); s_it != s.end(); s_it++) {

        // Append the current char's boolvector to the result
        m_it = encodingMap->find(*s_it);
        result.insert(result.end(), m_it->second.begin(), m_it->second.end());
    }
    return result;
}

// ---------- GET FREQUENCY OF EACH CHAR ------------------------------------------------
std::map<char, double>* Huffman::getFrequencies(std::string s) {
    std::map<char, double>*             f = new std::map<char, double>;
    std::map<char, double>::iterator    f_it;
	
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
        (*f)[f_it->first] /= s.size();  f_it++;
    }

    // Return the mapping of character frequencies
    return f;
}

// ---------- SORT THE LIST OF NODES ----------------------------------------------------
void Huffman::Sort(std::vector<Node*>& v) {
    bool swap = true;
    int  n    = v.size(), i;
	
	// Simple bubble sort
    while (swap) {	
        swap = false;
        for (i = 1; i <= n - 1; i++) {
            if (v[i-1]->getFrequency() > v[i]->getFrequency()) {
                std::swap(v[i-1], v[i]);
                swap = true;
            }
        }
        --n;
    }
}

// ---------- BUILD THE HUFFMAN TREE ----------------------------------------------------
void Huffman::buildTree() {
    std::vector<Node*>                  nodes;
    std::vector<bool>                   bits;
    std::map<char, double>              temp = *frequencies;
    std::map<char, double>::iterator    f_it, lowest;

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
    tree = nodes.front();
    tree->fill(*encodingMap, bits);
}

// ---------- SHOW THE HUFFMAN TREE -----------------------------------------------------
void Huffman::showTree() {
    std::map<char, std::vector<bool>>::iterator     e_it;
    std::vector<bool>::iterator                     b_it;

    // Loop through all the characters
    for (e_it = encodingMap->begin(); e_it != encodingMap->end(); e_it++) {
        std::cout << e_it->first << ": ";
        showBoolVector(e_it->second);
        std::cout << "\n";
    }
}

// ---------- PRINT OUT A BOOLEAN VECTOR ------------------------------------------------
void Huffman::showBoolVector(std::vector<bool>& v) {
    std::vector<bool>::iterator v_it;
    for (v_it = v.begin(); v_it != v.end(); v_it++) std::cout << *v_it;
}