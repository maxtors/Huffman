#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include "Huffman.h"
#include "Node.h"


// ---------- CONSTRUCTOR ---------------------------------------------------------------
Huffman::Huffman() {
    encodingMap = new std::map<char, std::pair<int, int>>;
    frequencies = NULL;
    datafile 	= NULL;
    tablefile 	= NULL;
}

// ---------- DECONSTRUCTOR -------------------------------------------------------------
Huffman::~Huffman() {
    delete encodingMap;
    delete frequencies;
    delete datafile;
    delete tablefile;
}

// ---------- ENCODE STRING -------------------------------------------------------------
void Huffman::encode(std::string filename) {
    char* charData;
    std::string stringData;
    int size, start, stop;
    if (frequencies) delete frequencies;
    std::ifstream file(filename.c_str(), std::ios::binary);

    if (!file) {
        std::cout << "Could not open file: " << filename << "\n";
        return;
    }
    else {
        file.seekg(0, std::ios::beg);
        start = file.tellg();
        file.seekg(0, std::ios::end);
        stop = file.tellg();
        file.seekg(0, std::ios::beg);
        size = stop - start;
        charData = new char[size];
        file.read(charData, size);

        frequencies = getFrequencies(charData, size);
        buildTree();
        showTree();

        encodedResult = buildEncodedResult(charData, size);

        /*
            MAKE THIS PART AS A FUNCTION
        int nSize = size * 8;
        int eSize = encodedResult.size();
        float comp = 1 - ((float)eSize / (float)nSize);

        std::cout << "\n\nAmount of bits in regular string: " << nSize;
        std::cout << "\nAmount of bits in encoded string: " << eSize;
        std::cout << "\nCompression: " << comp * 100 << "%";
        */
    }
}

// ---------- DECODE STRING -------------------------------------------------------------
void Huffman::decode(std::string data_filename, std::string table_filename) {
    // NOT STARTED
}

// ---------- MAKE ENCODED STRING FROM ENCODING MAP -------------------------------------
std::vector<std::pair<int, int>> Huffman::buildEncodedResult(char* data, int size) {
    std::map<char, std::pair<int, int>>::iterator m_it;
    std::vector<std::pair<int, int>>              result;

    // Loop through the string the user wants to encode
    for (int i = 0; i < size; i++) {

        // Append the current char's boolvector to the result
        m_it = encodingMap->find(data[i]);
        result.push_back(m_it->second);
    }
    return result;
}

// ---------- GET FREQUENCY OF EACH CHAR ------------------------------------------------
std::map<char, short>* Huffman::getFrequencies(char* data, int size) {
    std::map<char, short>*             f = new std::map<char, short>;
    std::map<char, short>::iterator    f_it;
	
    // Loop through the parameter string, and treat each character
    for (int i = 0; i < size; i++) {
        // If the char is in the map, add one, if not, insert into map
        f_it = f->find(data[i]);
        if (f_it == f->end()) f->insert(std::pair<char, short>(data[i], 1));
        else                  (*f)[data[i]] += 1;
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
    int                                 bits = 0;
    std::vector<Node*>                  nodes;
    std::map<char, short>              temp = *frequencies;
    std::map<char, short>::iterator    f_it, lowest;

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
        nodes.push_back(new Node(lowest->first, lowest->second));
        temp.erase(lowest);
    }
	
	// Create the Huffman tree
    while (nodes.size() != 1) {
    	
    	// Create new binding node, erase used nodes, and sort vector
    	nodes.push_back(new Node(nodes.at(0), nodes.at(1)));
        nodes.erase(nodes.begin(), nodes.begin()+2);
    	Sort(nodes);
    }

    // Set tree pointer, and fill the tree...
    tree = nodes.front();
    tree->fill(*encodingMap, bits, 0);
}

// ---------- SHOW THE HUFFMAN TREE -----------------------------------------------------
void Huffman::showTree() {
    std::map<char, std::pair<int, int>>::iterator e_it;

    // Loop through all the characters
    for (e_it = encodingMap->begin(); e_it != encodingMap->end(); e_it++) {
        std::cout << e_it->first << ": " << e_it->second.first << "\n";
    }
}