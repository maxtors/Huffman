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
    
    struct DataFile {
        char    magicNumber;
        char    paddingOffset;
        char*   data;
    };
    
    struct TableEntry{
        char    data;
        char    size;
        int     bits;
    };
    
    struct TableFile {
        char    magicNumber;
        int     tableSize;
        std::vector<TableEntry> data;
    };
    
    Node*                               tree;
    std::string                         decodedResult;
    std::vector<int>                    encodedResult;
    std::map<char, std::pair<int, int>> encodingMap;
    std::map<char, double>*             frequencies;
    
    std::map<char, double>*     getFrequencies(std::string s);
    void                        Sort(std::vector<Node*>& v);
    void                        buildTree();
    void                        showTree();
    void                        showIntVector(std::vector<int>& v);
    std::vector<int>            buildEncodedResult(std::string s);
    std::string                 buildDecodedResult(std::map<char, std::pair<int, int>>& m,
                                                   int size, char* data);
                                                   
    DataFile*   createDataFile(std::vector<int>& v);
    TableFile*  createTableFile(std::map<char, std::pair<int, int>>& m);
    
    DataFile*   readDataFile(ifstream* file);
    TableFile*  readTableFile(ifstream* file);
    
    void        writeDataFile(ofstream* file);
    void        writeDataFile(ofstream* file);
    
    */
    
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

    Node*                               tree;
    std::string                         decodedResult;
    std::vector<bool>                   encodedResult;
    std::map<char, std::vector<bool>>*  encodingMap;
    std::map<char, double>*             frequencies;
    std::map<char, double>*             getFrequencies(std::string s);
    std::vector<bool>                   buildEncodedResult(std::string s);
    void Sort(std::vector<Node*>& v);
    void buildTree();
    void showTree();
    void showBoolVector(std::vector<bool>& v);
public:
    Huffman();
    ~Huffman();
    
    /*
    
    void encode(ifstream* file);
    void decode(ifstream* table, ifstream* data)
    
    */
    
    void encode(std::string s);
    void decode(std::string s);
};

#endif