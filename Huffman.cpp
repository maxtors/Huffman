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
    encodingMap = new char_intpair_m;
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
    char*               charData;
    int                 size, start, stop;
    std::string         stringData;
    std::ifstream       file(filename.c_str(), std::ios::binary);
    int                 s = 0;
    intpair_v::iterator it;
    
    if (frequencies) delete frequencies;

    if (!file) {
        std::cout << "Could not open file: " << filename << "\n";
        return;
    }
    else {
    	// Get the file size
        file.seekg(0, std::ios::beg);
        start = file.tellg();
        file.seekg(0, std::ios::end);
        stop = file.tellg();
        file.seekg(0, std::ios::beg);
        size = stop - start;
        charData = new char[size];
        file.read(charData, size);

		// Get frequencies of chars, and build the huffman tree
        frequencies = getFrequencies(charData, size);
        buildTree();
        showTree();
        
        // Get the encoded result, create data and table files
        encodedResult = buildEncodedResult(charData, size);
        createDataFile(encodedResult);
        createTableFile(*encodingMap);
		
		// Write data and table file to disk
		if (!writeDataFile(filename)) return;
		if (!writeTataFile(filename)) return;
		
		/*
			LAG DENNE DELEN OM TIL EN EGEN FUNKSJON
		*/
        for (it = encodedResult.begin(); it != encodedResult.end(); it++) s+=it->second;

        float comp = 1 - ((float)s / (float)(size*8));
        std::cout << "\n\nAmount of bits in regular string: " << size * 8;
        std::cout << "\nAmount of bits in encoded string: " << s;
        std::cout << "\nCompression: " << comp * 100 << "%";
    }
}

// ---------- DECODE STRING -------------------------------------------------------------
void Huffman::decode(std::string data_filename, std::string table_filename) {
    // NOT STARTED
}

// ---------- MAKE ENCODED STRING FROM ENCODING MAP -------------------------------------
std::vector<std::pair<int, int>> Huffman::buildEncodedResult(char* data, int size) {
    char_intpair_m::iterator m_it;
    intpair_v                result;

    // Loop through the string the user wants to encode
    for (int i = 0; i < size; i++) {

        // Append the current char's boolvector to the result
        m_it = encodingMap->find(data[i]);
        result.push_back(m_it->second);
    }
    return result;
}

// ---------- GET FREQUENCY OF EACH CHAR ------------------------------------------------
char_int_m* Huffman::getFrequencies(char* data, int size) {
    char_int_m*          f = new char_int_m;
    char_int_m::iterator f_it;
	
    // Loop through the parameter string, and treat each character
    for (int i = 0; i < size; i++) {
        // If the char is in the map, add one, if not, insert into map
        f_it = f->find(data[i]);
        if (f_it == f->end()) f->insert(std::pair<char, int>(data[i], 1));
        else                  (*f)[data[i]] += 1;
    }

    // Return the mapping of character frequencies
    return f;
}

// ---------- SORT THE LIST OF NODES ----------------------------------------------------
void Huffman::Sort(node_v& v) {
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
    int                  bits = 0;
    node_v               nodes;
    char_int_m           temp = *frequencies;
    char_int_m::iterator f_it, lowest;

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
    char_intpair_m::iterator e_it;

    // Loop through all the characters
    for (e_it = encodingMap->begin(); e_it != encodingMap->end(); e_it++) {
        std::cout << e_it->first << ": (" << e_it->second.second << ")  "
        		  << e_it->second.first << "\n";
    }
}

// ---------- CREATE DATAFILE -----------------------------------------------------------
void Huffman::createDataFile(intpair_v& v) {
    intpair_v::iterator it;
	int size, poff, bitpos, bit, charpos, charbitpos;

    if (datafile) delete datafile;
    datafile = new DataFile;
    datafile->magicNumber = 0xA0;

    // Calculate the amount if bits in encoded result
    size = 0;
    for (it = v.begin(); it != v.end(); it++) size += it->second;

    // Calculate how much padding is needed to be divisible by 8
    poff = size;
    while (poff > 0) poff -= 8;
    poff *= -1;
    size += poff;
    size /= 8;

    // Add new data into the datafile struct
    datafile->size = size;
    datafile->data = new char[datafile->size];
    datafile->paddingOffset = poff;

    charpos = 0;
    charbitpos = 7;
    // Loop through every single encoded value in the vector
    for (it = v.begin(); it != v.end(); it++) {

        // Loop through all the bits that are to be inserted into data
        for (bitpos = it->second-1; bitpos >= 0; bitpos--) {

            // Extract the wanted bit
            bit = (it->first >> bitpos) & 1;

            // If the amount of bits has overflown size of char, move to next char
            if (charbitpos < 0) {
                charbitpos = 7;
                charpos++;
            }

            // If this is a new char, sett it to: 0000 0000
            if (charbitpos == 7) {
                datafile->data[charpos] = 0x0;
            }

            // Append the new bit to the char, then itterate to next bit position in char
            datafile->data[charpos] = (datafile->data[charpos]) | bit << charbitpos;
            charbitpos--;
        }
    }
}

// ---------- CREATE TABLE FILE ---------------------------------------------------------
void Huffman::createTableFile(char_intpair_m& m) {
	if (tablefile) delete tablefile;
	tablefile = new TableFile;
    TableEntry temp;
    char_intpair_m::iterator it;

    tablefile->magicNumber = 0xA0;

    for (it = encodingMap->begin(); it != encodingMap->end(); it++) {
        temp.data = it->first;
        temp.bits = it->second.first;
        temp.size = it->second.second;
        tablefile->data.push_back(temp);
    }
}

// ---------- READ THE DATAFILE FROM DISK -----------------------------------------------
bool Huffman::readDataFile(std::string fstr) {
	// ---
	return false;
}

// ---------- READ TABLEFILE FROM DISK --------------------------------------------------
bool Huffman::readTableFile(std::string fstr) {
	char charbuffer;
	char buffer[256];
	TableEntry temp;
	
	if (tablefile) delete tablefile;
	tablefile =    new Tablefile;
	
	std::ifstream file(fstr.c_str(), std::ios::binary);
	
	if (!file) {
		std::cout << "Could not open tablefile\n";
		file.close();
		return false;
	}
	else {
		
		// Read magic number and check contents
		file.read(&charbuffer, 1);
		if (charbuffer != 0xA0) {
			std::cout << "Invalid tablefile\n";
			file.close();
			return false;
		}
		
        try {
        // Read the table entries
            while (!file.eof()) {
                // Read the char in question
                file.read(&charbuffer, 1);
                temp.data = charbuffer;
                if (file.fail()) throw "Error reading tablefile";
                
                // Read the size (number of bits) this encoded char uses
                file.read(&charbuffer, 1);
                temp.size = charbuffer;
			    if (file.fail()) throw "Error reading tablefile";
            
                // Read the bits for this encoded char
                file.read(buffer, 4);
                temp.bits = (int)buffer;
    			if (file.fail()) throw "Error reading tablefile";
                
                // Append the new entry into the data vector
                tablefile->data.push_back(temp);
            }
        }
        catch (char* err) {
            file.close();
            std::cout << err << "\n";
            return false;
        }
	}
	file.close();
    return true;
}

// ---------- WRITE TABLEFILE TO DISK ---------------------------------------------------
bool Huffman::writeTableFile(std::string fstr) {
	fstr += ".htbl";
    std::ofstream file(fstr.c_str(), std::ios::binary);
    TableEntries::iterator it;

    if (!file) {
        std::cout << "Could not write Tablefile for encoded data\n";
        file.close();
        return false;
    }
    else {
        file.write(&tablefile->magicNumber, 1);

        for (it = tablefile->data.begin(); it != tablefile->data.end(); it++) {
            file.write(&it->data, 1);
            file.write(&it->size, 1);
            file.write((char*)&it->bits, 4);
        }
    }
    file.close();
    return true;
}

// ---------- WRITE DATAFILE TO DISK ----------------------------------------------------
bool Huffman::writeDataFile(std::string fstr) {
	fstr += ".hdta";
    std::ofstream file(fstr.c_str(), std::ios::binary);

    if (!file) {
        std::cout << "Could not write Datafile for encoded data\n";
        file.close();
        return false;
    }
    else {
        file.write(&datafile->magicNumber, 1);
        file.write((char*)&datafile->size, 4);
        file.write(&datafile->paddingOffset, 1);
        file.write((char*)datafile->data, datafile->size);
    }
    file.close();
    return true;
}