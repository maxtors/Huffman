// ---------- INCLUDES ------------------------------------------------------------------
#include <iostream>
#include "Huffman.h"

// ---------- MAIN ----------------------------------------------------------------------
int main() {
    Huffman h;
    h.encode("Test string to see how this works...");

    std::cout << "\n\n"; system("pause");
    return 0;
}