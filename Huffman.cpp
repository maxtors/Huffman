#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include "Huffman.h"


Huffman::Huffman(std::string s) {
	encoded		= new Encode_map;
	frequencies = getFrequencies(s);
}

Huffman::~Huffman() {
	delete encoded;
	delete frequencies;
}

Frequencies* Huffman::getFrequencies(std::string s) {
	Frequencies* f = new Frequencies;
	Frequencies::iterator f_it;
	
	for (unsigned int i = 0; i < s.length(); i++) {

		f_it = f->find(s[i]);
		if (f_it == f->end()) {
			f->insert(std::pair<char, double>(s[i], 1.0f));
		}
		else {
			(*f)[s[i]] += 1.0f;
		}
	}

	f_it = f->begin();
	while (f_it != f->end()) {
		(*f)[f_it->first] /= s.size();
		f_it++;
	}

	return f;
}