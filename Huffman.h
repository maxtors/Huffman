#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <map>
#include <vector>
#include <string>

typedef std::map<std::string, std::vector<bool>> Encode_map;
typedef std::map<char, double> Frequencies;

class Huffman {
private:
	Encode_map*		encoded;
	Frequencies*	frequencies;

	Frequencies* getFrequencies(std::string s);

public:
	Huffman(std::string s);
	~Huffman();
};

#endif