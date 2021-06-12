#include <iostream>
#include "unordered_table.h"
#include "ordered_table.h"
#include "binary_tree.h"
#include "AVL_tree.h"

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

    /*AVL_tree avlt = AVL_tree();
    avlt.addWord("a");
    avlt.addWord("ads");
    avlt.addWord("c");
    avlt.addWord("b");
    avlt.addWord("");
    avlt.addWord("b");
    avlt.preorder();
    avlt.postorder();
    avlt.inorder();
    avlt.deleteWord("ads");
    cout << "" << endl << endl << endl;
    avlt.preorder();
    avlt.postorder();
    avlt.inorder();


    std::cout << "" << std::endl << std::endl;
    binary_tree bt = binary_tree();
    bt.addWord("b");
    bt.addWord("ads");
    bt.addWord("c");
    bt.addWord("a");
    bt.addWord("");
    bt.addWord("b");
    bt.preorder();
    bt.postorder();
    bt.inorder();
    bt.deleteWord("b");
    cout << "" << endl << endl << endl;
    bt.preorder();
    bt.postorder();
    bt.inorder();

    for(int i = 0; i < 1000; i++)
        bt.findWord("b");
        //*/
    return 0;
}
