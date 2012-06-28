// ---------- INCLUDES ------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include "Huffman.h"

// ---------- MAIN ----------------------------------------------------------------------
int main(int argc, char* argv[]) {
    std::ifstream file;
    Huffman h;

    try {
        if (argc != 3 && argc != 4) throw "Invalid number of arguments";
        if (strcmp(argv[1],"-e")!=0 &&
            strcmp(argv[1],"-d")!=0) throw "Incorrect arguemnt";
        file.open(argv[2]);
        if (!file) throw "Could not open file";
        file.close();
        if (strcmp(argv[1],"-e")==0 && argc != 3) throw "Invalid number of arguments";
        if (strcmp(argv[1],"-d")==0 && argc != 4) throw "Invalid number of arguments";

        if (strcmp(argv[1],"-e")==0) {
            h.encode(argv[2]);
        }
    }
    catch (char* err) {
        if (file.is_open()) file.close();
        std::cout << "\n\n" << err << ".\n\n"
                  << "\t-Encoding: -e filename.type\n"
                  << "\t-Decoding: -d file1.datafile file2.tablefile\n";
    }

    return 0;
}