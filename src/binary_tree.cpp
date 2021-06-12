#include "binary_tree.h"

/*  ============================================================ *
 *                      PUBLIC CLASSES                           *
 *  ============================================================ */

binary_tree::binary_tree()
{
    std::cout << "Binary Search Tree constructor." << std::endl;
    tree = nullptr;
}

void binary_tree::addWord(std::string word)
{
    data temp;
    temp.occurencies = 1;
    temp.word = word;

    if (word.empty()) return;

    if(tree == nullptr) {
        //std::cout << "Tree is empty - inserting " << word << " at root" << std::endl;
        tree = newPointer(temp, tree);
    }
    else
        tree = insertNewNode(temp, tree);
}

void binary_tree::deleteWord(std::string word)
{
    //std::cout << "Trying to find the node holding the word " << word << " in the tree..." << std::endl;
    tree = deleteNode(word, tree);
}


void binary_tree::findWord(std::string word)
{
    node *temp = searchNode(word, tree);
    if(temp != nullptr)
        std::cout << "Requested word " << temp->table.word << " was found " << temp->table.occurencies << " time(s) in the text." << std::endl;
    else
        std::cout << "Requested word " << word << " was not found in the tree." << std::endl;
}

void binary_tree::postorder()
{
    std::cout << "Post-order traversal:" << std::endl;
    postorder(tree->left);
    postorder(tree->right);
    std::cout << "\troot " << tree->table.word << " has " << tree->table.occurencies << " occurencies." << std::endl;

}

void binary_tree::inorder()
{
    std::cout << "In-order traversal:" << std::endl;
    inorder(tree->left);
    std::cout << "\troot " << tree->table.word << " has " << tree->table.occurencies << " occurencies." << std::endl;
    inorder(tree->right);
}

void binary_tree::preorder()
{
    std::cout << "Pre-order traversal:" << std::endl;
    std::cout << "\troot " << tree->table.word << " has " << tree->table.occurencies << " occurencies." << std::endl;
    preorder(tree->left);
    preorder(tree->right);
}


binary_tree::~binary_tree()
{
    deconstructor(tree->left);
    deconstructor(tree->right);
    delete tree;
}

/*  ============================================================ *
 *                  PROTECTED CLASSES                            *
 *  ============================================================ */

node* binary_tree::newPointer(data key, node *root)
{
    root = new node;
    root->table = key;
    root->left = nullptr;
    root->right = nullptr;
    return root;
}

node* binary_tree::insertNewNode(data key, node *root)
{
    if(root == nullptr) {
        root = newPointer(key, root);
        //std::cout << "\tCreating node with the word " << key.word << std::endl;
    }
    else {
        if(root->table.word.compare(key.word) > 0) {
            //std::cout << "\t\t" << key.word << " is smaller than the current word (" << root->table.word << "). Going to the left." << std::endl;
            root->left = insertNewNode(key, root->left);
        }
        else if (root->table.word.compare(key.word) < 0) {
            //std::cout << "\t\t" << key.word << " is bigger than the current word (" << root->table.word << "). Going to the right." << std::endl;
            root->right = insertNewNode(key, root->right);
        }
        else {
            //std::cout << "\t\t" << key.word << " was found in the tree." << std::endl;
            root->table.occurencies++;
        }
    }

    return root;
}

node* binary_tree::deleteNode(std::string key, node *root)
{
    if(root == nullptr) return nullptr;

    if(root->table.word.compare(key) > 0)
        root->left = deleteNode(key, root->left);
    else if (root->table.word.compare(key) < 0)
        root->right = deleteNode(key, root->right);
    else {
        if(root->left == nullptr && root->right != nullptr) {
            //std::cout << "\t" << "Node has no left child - moving the right child up." << std::endl;
            root = root->right;
        }
        else if (root->left != nullptr && root->right == nullptr) {
            //std::cout << "\t" << "Node has no right child - moving the left child up." << std::endl;
            root = root->left;
        }
        else {
            //std::cout << "\t" << "Node has either two children or none. Reconstructing the tree..." << std::endl;
            if (root->left == nullptr && root->right == nullptr) {
                // the node had no children, therefore deleting the node is safe
                root = nullptr;
            }
            else {
                // the node has two children, find the successor
                //      successor is the lowest left node of the right subtree (credits: https://www.geeksforgeeks.org/binary-search-tree-set-2-delete/ )
                node *temp = root->right;
                while(temp != nullptr && temp->left != nullptr)
                    temp = temp->left;
                // replace the data from the successor to the node
                root->table = temp->table;
                // However, the successor node can have a right child
                // insert that child to the tree, beginning from the replaced node
                if(temp->right != nullptr) {
                    insertNewNode(temp->right->table, root);
                }
                // delete the temporary node
                root->right = deleteNode(temp->table.word, root->right);
            }
        }
    }
    return root;
}

node* binary_tree::searchNode(std::string key, node* root)
{

    if (root == nullptr) {
        // in case it's null and we don't return, the program will crush
        //std::cout << "\t" << root << " was not found in the tree" << std::endl;
        return nullptr;
    }
    if (root->table.word.compare(key) > 0)
        return searchNode(key, root->left);
    else if (root->table.word.compare(key) < 0)
        return searchNode(key, root->right);
    else {
        //std::cout << "\t" << key << " was found in the tree." << std::endl;
        return root;
    }
}

void binary_tree::inorder(node *root)
{
    if(root == nullptr) {
        //std::cout << "Node is empty." << std::endl;
        return;
    }
    inorder(root->left);
    std::cout << "\t" << root->table.word << " has " << root->table.occurencies << " occurencies." << std::endl;
    inorder(root->right);

}

void binary_tree::preorder(node *root)
{
    if(root == nullptr) {
        //std::cout << "Node is empty." << std::endl;
        return;
    }
    std::cout << "\t" << root->table.word << " has " << root->table.occurencies << " occurencies." << std::endl;
    preorder(root->left);
    preorder(root->right);

}

void binary_tree::postorder(node *root)
{
    if(root == nullptr) {
        //std::cout << "Node is empty." << std::endl;
        return;
    }
    postorder(root->left);
    postorder(root->right);
    std::cout << "\t" << root->table.word << " has " << root->table.occurencies << " occurencies." << std::endl;
}

void binary_tree::deconstructor(node* root)
{
    if(root == nullptr) return;

    if(root->left != nullptr)
        deconstructor(root->left);

    if(root->right != nullptr)
        deconstructor(root->right);

    delete root;
}
