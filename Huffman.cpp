#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include "Huffman.h"


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