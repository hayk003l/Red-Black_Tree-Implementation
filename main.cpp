#include <iostream>
#include "redBlack.hpp"

int main() {
    RedBlackTree rb;

    rb.insert(41);
    rb.insert(38);
    rb.insert(31);
    rb.insert(12);
    rb.insert(19);
    rb.insert(8);

    rb.deleteNode(38);

    rb.printTree();

    

    return 0;
}