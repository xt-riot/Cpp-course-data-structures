#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <string>
#include <iostream>

struct data {
    std::string word;
    int occurencies;
};

struct node {
    data table;
    node *left;
    node *right;
};

class binary_tree
{
    public:
        binary_tree();
        virtual ~binary_tree();

        void addWord(std::string word);
        void deleteWord(std::string word);
        void findWord(std::string word);
        void inorder();
        void preorder();
        void postorder();

    protected:
        node* insertNewNode(data key, node *root);
        node* newPointer(data key, node *root);
        node* searchNode(std::string key, node *root);
        node* deleteNode(std::string key, node *root);
        void inorder(node *root);
        void preorder(node *root);
        void postorder(node *root);
        void deconstructor(node* root);

    private:
        node *tree;
};

#endif // BINARY_TREE_H
