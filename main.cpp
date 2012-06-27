// ---------- INCLUDES --------------------------------------------------------
#include <iostream>
#include "Huffman.h"

// ---------- MAIN ------------------------------------------------------------
int main() {
    Huffman h("ERDBEERE");
    h.buildTree();
    h.showTree();
    system("pause");
    return 0;
}