#ifndef HUFFMAN_H
#define HUFFMAN_H

// ---------- INCLUDES ------------------------------------------------------------------
#include <map>
#include <vector>
#include <string>
#include "Node.h"

// ---------- HUFFMAN CLASS -------------------------------------------------------------
class Huffman {
private:
    /*
    DATAFILE:
    BYTE    0xHF
    BYTE    PADDING OFFSET
    CHAR*   DATA
    
    TABLEFILE:
    BYTE    0xHF
    
        per entry:
        CHAR ch
        CHAR paddingOffset
        int  data
    */
    
    // ---------- STRUCTS ---------------------------------------------------------------
    struct DataFile {
        char  magicNumber;
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
        int  tableSize;
        std::vector<TableEntry> data;
    };

    // ---------- VARIABLES -------------------------------------------------------------
    Node*       tree;
    DataFile*   datafile;
    TableFile*  tablefile;
    std::string decodedResult;
    std::vector<std::pair<int, int>>        encodedResult;
    std::map<char, std::pair<int, int>>*    encodingMap;
    std::map<char, int>*                    frequencies;

    // ---------- PRIVATE FUNCTIONS -----------------------------------------------------
    std::map<char, int>*                getFrequencies(char* data, int size);
    std::vector<std::pair<int, int>>    buildEncodedResult(char* data, int size);
    
    // Create data structs from private data
    void createDataFile(std::vector<std::pair<int, int>>& v);
    void createTableFile(std::map<char, std::pair<int, int>>& m);
    
    // Read data structs from file
    void readDataFile(std::string fstr);
    void readTableFile(std::string fstr);
    
    // Write data structs to file
    void writeTableFile(Tablefile* t);
    void writeDataFile(Datafile* d);
    
    // DIV
    void Sort(std::vector<Node*>& v);
    void buildTree();
    void showTree();
    void showIntVector(std::vector<int>& v);
    
public:
    // ---------- PUBLIC FUNCTIONS ------------------------------------------------------
    Huffman();
    ~Huffman();
    void encode(std::string filename);
    void decode(std::string data_filename, std::string table_filename);
};

#endif