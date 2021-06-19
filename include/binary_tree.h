#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <string>
#include <iostream>
#include <fstream>

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

        void addWord(std::string);
        void deleteWord(std::string);
        void findWord(std::string);
        void inorder();
        void preorder();
        void postorder();

        std::string getDesc();

    protected:
        node* insertNewNode(data, node*);
        node* newPointer(data, node*);
        node* searchNode(std::string, node*);
        node* deleteNode(std::string, node*);
        void inorder(node*);
        void preorder(node*);
        void postorder(node*);
        void deconstructor(node*);

    private:
        node *tree;
        std::string description;
};

#endif // BINARY_TREE_H
