#include <iostream>
#include "unordered_table.h"
#include "ordered_table.h"
#include "binary_tree.h"

using namespace std;


int main()
{
    //cout << "Hello world!" << endl;
    /*ordered_table asd = ordered_table();
    asd.addWord("a");
    asd.addWord("ads");
    asd.addWord("c");
    asd.addWord("b");
    asd.addWord("");
    asd.printTable();
    asd.deleteWord("ads");
    asd.printTable();
    asd.deleteWord("b");
    asd.printTable();
    //cout << asd[0] << endl;*/

    binary_tree bt = binary_tree();
    bt.addWord("a");
    bt.addWord("ads");
    bt.addWord("c");
    bt.addWord("b");
    bt.addWord("");
    bt.addWord("b");
    std::cout << "PREORDER" << std::endl << std::endl;
    bt.preorder();
    std::cout << "POSTORDER" << std::endl << std::endl;
    bt.postorder();
    std::cout << "INORDER" << std::endl << std::endl;
    bt.inorder();
    return 0;
}
