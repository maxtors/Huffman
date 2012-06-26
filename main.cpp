// ---------- INCLUDES --------------------------------------------------------
#include <iostream>
#include "Huffman.h"

// ---------- MAIN ------------------------------------------------------------
int main() {
    Huffman h("Hei hei, dette er min file lille streng");
    h.buildTree();
    return 0;
}