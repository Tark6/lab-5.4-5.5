#include "Huffman.h"

int main()
{

    Huffman h;
    h.foo("aaaaaaaaaaaaaaabbbccccccccccccccccccccccccccccccccccccccccccccccccccdddddddddddddddddddddddddeeeeeee");
    h.coding("abcde");
    cout << endl;
    h.decode("11011110101110");

    return 0;
}
