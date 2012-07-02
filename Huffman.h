#ifndef HUFFMAN_H
#define HUFFMAN_H

// ---------- INCLUDES ------------------------------------------------------------------
#include <map>
#include <vector>
#include <string>
#include "Node.h"

// ---------- STRUCTS -------------------------------------------------------------------
struct DataFile {
    char  magicNumber;
    int   size;
    char  paddingOffset;
    char* data;
};
    
struct TableEntry{
    char data;
    char size;
    int  bits;
};
    
struct TableFile {
    char magicNumber;
    std::vector<TableEntry> data;
};

// ---------- TYPEDEFS -------------------------------------------------------------
typedef std::vector<Node*>          node_v;
typedef std::vector<int>            int_v;
typedef std::pair<int, int>         intpair;
typedef std::vector<intpair>        intpair_v;
typedef std::map<char, intpair>     char_intpair_m;
typedef std::map<char, int>         char_int_m;
typedef std::vector<TableEntry>     TableEntries;

// ---------- HUFFMAN CLASS -------------------------------------------------------------
class Huffman {
private:

    // ---------- VARIABLES -------------------------------------------------------------
    Node*           tree;
    DataFile*       datafile;
    TableFile*      tablefile;
    std::string     decodedResult;
    intpair_v       encodedResult;
    char_intpair_m* encodingMap;
    char_int_m*     frequencies;

    // ---------- PRIVATE FUNCTIONS -----------------------------------------------------
    char_int_m* getFrequencies(char* data, int size);
    intpair_v   buildEncodedResult(char* data, int size);
    
    // Create data structs from private data
    void createDataFile(intpair_v& v);
    void createTableFile(char_intpair_m& m);
    
    // Read data structs from file
    bool readDataFile(std::string fstr);
    bool readTableFile(std::string fstr);
    
    // Write data structs to file
    bool writeTableFile(std::string fstr);
    bool writeDataFile(std::string fstr);
    
    // DIV
    void Sort(node_v& v);
    void buildTree();
    void showTree();
    void showIntVector(int_v& v);
    
public:
    // ---------- PUBLIC FUNCTIONS ------------------------------------------------------
    Huffman();
    ~Huffman();
    void encode(std::string filename);
    void decode(std::string data_filename, std::string table_filename);
};

#endif