#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <string>
#include <iostream>

struct dataAVL {
    std::string word;
    int occurencies;
};

struct nodeAVL {
    dataAVL table;
    nodeAVL *left;
    nodeAVL *right;
};

class AVL_tree
{
    public:
        AVL_tree();
        virtual ~AVL_tree();

        void addWord(std::string word);
        void deleteWord(std::string word);
        void findWord(std::string word);
        void inorder();
        void preorder();
        void postorder();

    protected:
        nodeAVL* insertNewNode(dataAVL key, nodeAVL *root);
        nodeAVL* newPointer(dataAVL key, nodeAVL *root);
        nodeAVL* searchNode(std::string key, nodeAVL *root);
        nodeAVL* deleteNode(std::string key, nodeAVL *root);
        void inorder(nodeAVL *root);
        void preorder(nodeAVL *root);
        void postorder(nodeAVL *root);
        void deconstructor(nodeAVL* root);

        nodeAVL* reconstruct(nodeAVL *root);
        nodeAVL* RR_rotate(nodeAVL *root);
        nodeAVL* RL_rotate(nodeAVL *root);
        nodeAVL* LL_rotate(nodeAVL *root);
        nodeAVL* LR_rotate(nodeAVL *root);
        int height(nodeAVL *root);
        int subTreeDifference(nodeAVL *root);

    private:
        nodeAVL *tree;
};

#endif // AVL_TREE_H
