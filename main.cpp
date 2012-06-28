// ---------- INCLUDES ------------------------------------------------------------------
#include <iostream>
#include "Huffman.h"

// ---------- MAIN ----------------------------------------------------------------------
int main() {
    Huffman h;
    h.encode("test.rar");

    std::cout << "\n\n"; system("pause");
    return 0;
}