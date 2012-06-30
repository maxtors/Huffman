// ---------- INCLUDES ------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include "Huffman.h"

// ---------- MAIN ----------------------------------------------------------------------
int main(int argc, char* argv[]) {
    std::ifstream file;
    Huffman h;

    h.encode("README");
    std::cout << "\n"; system("pause");

    /*
    try {
        if (argc != 3 && argc != 4) throw "Invalid number of arguments";

        if (strcmp(argv[1],"-e")==0) {
            if (argc != 3) throw "Innvalid number of arguments";
            file.open(argv[2]);
            if (!file) throw "Could not open file";
            file.close();

            // Encode the wanted file
            h.encode(argv[2]);
        }
        else if (strcmp(argv[1],"-d")==0) {
            if (argc != 4) throw "Innvalid number of arguments";
            file.open(argv[2]);
            if (!file) throw "Could not open datafile";
            file.close();
            file.open(argv[2]);
            if (!file) throw "Could not open tablefile";
            file.close();
            
            // Decode the wanted files
            h.decode(argv[2], argv[3]);
        }
        else {
            throw "Incorrect arguments";
        }
    }
    catch (char* err) {
        if (file.is_open()) file.close();
        std::cout << "\n\n" << err << ".\n\n";
        std::cout << "\t-Encoding: -e filename.type\n";
        std::cout << "\t-Decoding: -d file1.datafile file2.tablefile\n";
    }
    */
    return 0;
}