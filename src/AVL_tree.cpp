#include "AVL_tree.h"

/*******************************************************************************************************************
class AVL_tree():       Implementation of the AVL search tree. Every public function has
                        it's protected counterpart - that is mainly because this implementation
                        doesn't return the actual tree to the main, so the programmer can't alter
                        the tree. Each operation on the tree is done in the class itself.
    public:
        -AVL_tree():            Initiate the description
        -~AVL_tree():           Recursively destroy the nodes
        -addWord(std::string):  Add the given word in the AVL tree
        -findWord(std::string): Search for the given word in the tree
        -getDesc():             Return the description of the structure

            The next functions output their data in "./out/avl-tree-*ORDER.txt"
        -inorder():             In-order representation of the tree
        -preorder():            Pre-order representation of the tree
        -postorder():           Post-order representation of the tree

    protected:
        -insertNewNode(dataAVL, nodeAVL):   A function to add a new word to the tree. Returns the new tree with the added word.
        -newPointer(dataAVL, nodeAVL):      A function to add a new node to the tree. Returns the new tree with the added node.
        -searchNode(std::string, nodeAVL):  A function to search a given string in the tree. Returns the node that the word is found.
        -deleteNode(std::string, nodeAVL):  A function to delete a given string from the tree. Returns the new tree without the deleted word.
        -inorder(nodeAVL):                  In-order representation of the tree
        -preorder(nodeAVL):                 Pre-order representation of the tree
        -postorder(nodeAVL):                Post-order representation of the tree
        -deconstructor(nodeAVL*):           A function to delete each node along with its childs.

        -reconstruct(nodeAVL):              A function that is called each time we add or delete a word.
                                            It applies changes(RR/RL/LL/LR rotates) to the tree in order to make it AVL.
        -RR_rotate(nodeAVL):                Right - Right Rotate of the tree
        -RL_rotate(nodeAVL):                Right - Left Rotate of the tree
        -LL_rotate(nodeAVL):                Left - Left Rotate of the tree
        -LR_rotate(nodeAVL):                Left - Right Rotate of the tree
        -height(nodeAVL):                   Returns the height of the given node
        -subTreeDifference(nodeAVL):        Returns the height difference of the node's children.

    private:
        -tree:          The tree
        -description:   A string that holds the name of the current class.

    Helping data structure:
        struct dataAVL:          A data structure storing the word and how many times it's found in the text.
        struct nodeAVL:          A data structure storing the data of the node as well as the right and left child.
*******************************************************************************************************************/

/*  ============================================================ *
 *                      PUBLIC CLASSES                           *
 *  ============================================================ */

AVL_tree::AVL_tree()
{
    //std::cout << "AVL Tree constructor." << std::endl;
    description = "avl-tree";
    tree = nullptr;
}

std::string AVL_tree::getDesc()
{
    return description;
}

void AVL_tree::addWord(std::string word)
{
    if (word.empty()) return;   // Check if we have an empty string

    dataAVL temp;           // Process the string to the data structure we use
    temp.occurencies = 1;
    temp.word = word;

    if (tree == nullptr) { // if the tree has no node - therefore it's the first word we add
        //std::cout << "Tree is empty - inserting " << word << " at root." << std::endl;
        tree = newPointer(temp, tree); // make a new node and add the word
    }
    else { // otherwise, the tree exists
        //std::cout << "Trying to insert the word: " << word << std::endl;
        tree = insertNewNode(temp, tree); // use the protected helping function to add the word to the tree
        tree = reconstruct(tree); // reconstruct the tree to keep the height difference < 1
    }
}

void AVL_tree::deleteWord(std::string word)
{
    //std::cout << "Trying to find the node holding the word " << word << " in the tree..." << std::endl;
    tree = deleteNode(word, tree); // use the protected helping function to delete the word
    //std::cout << "Deleted the word. Reconstructing the tree..." << std::endl;
    tree = reconstruct(tree); // reconstruct the tree to keep the height difference < 2
}

void AVL_tree::findWord(std::string word)
{
    // use the protected helping function to search the node with the word we are given
    // this function is public, therefore we have to write if we found the word or not
    nodeAVL *temp = searchNode(word, tree);
    if(temp != nullptr)
        std::cout << "Requested word " << temp->table.word << " was found " << temp->table.occurencies << " time(s) in the text." << std::endl;
    else
        std::cout << "Requested word " << word << " was not found in the tree." << std::endl;
}

void AVL_tree::postorder()
{
    std::streambuf *psbuf, *backup; // used to interchange between console output and file output
    std::ofstream filestr; // the handle to file output
    filestr.open ("./out/avl-tree-postorder.txt", std::ios::out); // open the file and get ready to write
    backup = std::cout.rdbuf(); // take a backup of the cout buffer
    psbuf = filestr.rdbuf();   // get the file's buffer
    std::cout.rdbuf(psbuf);    // assign the file's buffer to cout - from now on, if we want to write something to the console,
                               // it will be re-directed to the output file

    // BEGIN REPRESENTING THE TREE IN POST-ORDER
    std::cout << "Post-order traversal:" << std::endl;
    postorder(tree->left);
    postorder(tree->right);
    std::cout << "\troot " << tree->table.word << " has " << tree->table.occurencies << " occurencies." << std::endl;

    filestr.close(); // close the output file
    std::cout.rdbuf(backup); // restore the buffer to cout - from now on, whatever we write with cout, it will be directed to the console
}

void AVL_tree::inorder()
{
    std::streambuf *psbuf, *backup; // used to interchange between console output and file output
    std::ofstream filestr; // the handle to file output
    filestr.open ("./out/avl-tree-postorder.txt", std::ios::out); // open the file and get ready to write
    backup = std::cout.rdbuf(); // take a backup of the cout buffer
    psbuf = filestr.rdbuf();   // get the file's buffer
    std::cout.rdbuf(psbuf);    // assign the file's buffer to cout - from now on, if we want to write something to the console,
                               // it will be re-directed to the output file

    // BEGIN REPRESENTING THE TREE IN IN-ORDER
    std::cout << "In-order traversal:" << std::endl;
    inorder(tree->left);
    std::cout << "\troot " << tree->table.word << " has " << tree->table.occurencies << " occurencies." << std::endl;
    inorder(tree->right);

    filestr.close(); // close the output file
    std::cout.rdbuf(backup); // restore the buffer to cout - from now on, whatever we write with cout, it will be directed to the console
}

void AVL_tree::preorder()
{
    std::streambuf *psbuf, *backup; // used to interchange between console output and file output
    std::ofstream filestr; // the handle to file output
    filestr.open ("./out/avl-tree-postorder.txt", std::ios::out); // open the file and get ready to write
    backup = std::cout.rdbuf(); // take a backup of the cout buffer
    psbuf = filestr.rdbuf();   // get the file's buffer
    std::cout.rdbuf(psbuf);    // assign the file's buffer to cout - from now on, if we want to write something to the console,
                               // it will be re-directed to the output file

    // BEGIN REPRESENTING THE TREE IN PRE-ORDER
    std::cout << "Pre-order traversal:" << std::endl;
    std::cout << "\troot " << tree->table.word << " has " << tree->table.occurencies << " occurencies." << std::endl;
    preorder(tree->left);
    preorder(tree->right);

    filestr.close(); // close the output file
    std::cout.rdbuf(backup); // restore the buffer to cout - from now on, whatever we write with cout, it will be directed to the console
}

// Delete the child nodes before deleting the root node.
AVL_tree::~AVL_tree()
{
    deconstructor(tree->left);
    deconstructor(tree->right);
    delete tree;
}


/*  ============================================================ *
 *                  PROTECTED CLASSES                            *
 *  ============================================================ */

nodeAVL* AVL_tree::reconstruct(nodeAVL* root)
{
    //std::cout << "Trying to balance the tree." << std::endl;
    int diff = subTreeDifference(root); // Get the total difference of the child's height
    if (diff > 1) { // if the difference is bigger than 1
        if (subTreeDifference(root->left) > 0) // and the left child has a positive difference in it's children
            root = LL_rotate(root); // we need a Left - Left Rotate
        else
            root = LR_rotate(root); // otherwise we need a Left - Right Rotate
    }
    else if (diff < -1) { // if the difference is less than -1
        if (subTreeDifference(root->right) > 0) // and the right child has a positive difference in it's children
            root = RL_rotate(root); // we need a Right - Left Rotate
        else
            root = RR_rotate(root); // otherwise we need a Right - Right Rotate
    }
    return root;
}

nodeAVL* AVL_tree::RR_rotate(nodeAVL* root)
{
    // Right - Right Rotate of the given node
    nodeAVL *temp = new nodeAVL;
    temp = root->right;
    root->right = temp->left;
    temp->left = root;
    //std::cout << "\t\tPerformed right-right rotation." << std::endl;
    return temp;
}

nodeAVL* AVL_tree::RL_rotate(nodeAVL* root)
{
    // Right - Left Rotate of the given node
    nodeAVL *temp = new nodeAVL;
    temp = root->right;
    root->right = LL_rotate(temp);
    //std::cout << "\t\tPerformed right-left rotation." << std::endl;
    return RR_rotate(root);
}

nodeAVL* AVL_tree::LL_rotate(nodeAVL* root)
{
    // Left - Left Rotate of the given node
    nodeAVL *temp = new nodeAVL;
    temp = root->left;
    root->left = temp->right;
    temp->right = root;
    //std::cout << "\t\tPerformed left-left rotation." << std::endl;
    return temp;
}

nodeAVL* AVL_tree::LR_rotate(nodeAVL* root)
{
    // Left - Right Rotate of the given node
    nodeAVL *temp = new nodeAVL;
    temp = root->left;
    root->left = RR_rotate(temp);
    //std::cout << "\t\tPerformed left-right rotation." << std::endl;
    return LL_rotate(root);
}

// Return the height number of the given node
int AVL_tree::height(nodeAVL* root)
{

    int h = 0;
    if (root != nullptr) { // check if the node has data
        int left = height(root->left); // get the height of it's left child
        int right = height(root->right); // get the height of it's right child
        int max_height = (left > right) ? left : right; // store the maximum height of the two in max_height(if left height is bigger, then max_height will be the left height)
        h = max_height + 1; // add one to the max_height
    }
    //std::cout << "\t\tThe tree has height equal to " << h << std::endl;
    return h; // return the current's node height
}

// Get the node's children height and return the difference
int AVL_tree::subTreeDifference(nodeAVL* root)
{

    int left = height(root->left);
    int right = height(root->right);
    //std::cout << "\t\t\tThe left and right subtrees have a difference of " << (left - right) << std::endl;
    return (left - right);
}

// A function that is called when the *root is nullptr - creates a new node
nodeAVL* AVL_tree::newPointer(dataAVL key, nodeAVL *root)
{
    root = new nodeAVL;
    root->table = key;
    root->left = nullptr;
    root->right = nullptr;
    return root;
}

// A recursive function that adds a new node to the correct position
nodeAVL* AVL_tree::insertNewNode(dataAVL key, nodeAVL *root)
{
    if(root == nullptr) { // if the given node/subtree doesn't exist
        root = newPointer(key, root); // create it and add the word
        //std::cout << "\tCreating node with the word " << key.word << std::endl;
    }
    else { // if it exists
        if(root->table.word.compare(key.word) > 0) { // check if the word should go to the left
            //std::cout << "\t\t" << key.word << " is smaller than the current word (" << root->table.word << "). Going to the left." << std::endl;
            root->left = insertNewNode(key, root->left); // insert the word in the left subtree

        }
        else if (root->table.word.compare(key.word) < 0) { // or if the word should go to the right
            //std::cout << "\t\t" << key.word << " is bigger than the current word (" << root->table.word << "). Going to the right." << std::endl;
            root->right = insertNewNode(key, root->right); // insert the word in the right subtree
        }
        else {
            //std::cout << "\t\t" << key.word << " was found in the tree." << std::endl;
            root->table.occurencies++; // if the word is found in the current node, just increment the occurencies
        }
    }
    return root;
}

// A recursive function to delete a word
nodeAVL* AVL_tree::deleteNode(std::string key, nodeAVL *root)
{
    if(root == nullptr) return nullptr; // if the given node/subtree is nullptr, the word doesn't exist

    if(root->table.word.compare(key) > 0) // if the given word is smaller than the current node's word
        root->left = deleteNode(key, root->left); // go to the left
    else if (root->table.word.compare(key) < 0) // else if the given word is bigger
        root->right = deleteNode(key, root->right); // go to the right
    else { // if the current node holds the word we want to delete
        // check if the node has children
        if(root->left == nullptr && root->right != nullptr) { // if it has only one(right child)
            //std::cout << "\t" << "Node has no left child - moving the right child up." << std::endl;
            root = root->right; // re-write the current node with the information found in the right child
        }
        else if (root->left != nullptr && root->right == nullptr) { // if it has only one(left) child)
            //std::cout << "\t" << "Node has no right child - moving the left child up." << std::endl;
            root = root->left; // re-write the current node with the information found in the left child
        }
        else { // the node has two children or non
            //std::cout << "\t" << "Node has either two children or none. Reconstructing the tree..." << std::endl;
            if (root->left == nullptr && root->right == nullptr) { // if it has none
                // the node had no children, therefore deleting the node is safe
                root = nullptr; // it's safe to just delete the node
            }
            else {
                // the node has two children, find the successor
                //      successor is the lowest left node of the right subtree (credits: https://www.geeksforgeeks.org/binary-search-tree-set-2-delete/ )
                nodeAVL *temp = root->right;
                while(temp != nullptr && temp->left != nullptr) {
                    temp = temp->left;
                }
                // replace the data from the successor to the node
                root->table = temp->table;
                // However, the successor node can have a right child
                // insert that child to the tree, beginning from the replaced node
                if(temp->right != nullptr) {
                    insertNewNode(temp->right->table, root);
                }
                // delete the successor node
                root->right = deleteNode(temp->table.word, root->right);
            }
        }
    }
    return root;
}

// A recursive function to search for the given word
nodeAVL* AVL_tree::searchNode(std::string key, nodeAVL* root)
{
    if (root == nullptr) {
        // in case it's null and we don't return, the program will crush
        //std::cout << "\t" << root << " was not found in the tree" << std::endl;
        return nullptr;
    }
    if (root->table.word.compare(key) > 0) // if the given word is smaller than the current node's word
        return searchNode(key, root->left); // search to the left child
    else if (root->table.word.compare(key) < 0) // if the given word is bigger
        return searchNode(key, root->right); // search to the right child
    else { // if the current node hold the word we are searching for
        //std::cout << "\t" << key << " was found in the tree." << std::endl;
        return root; // return the current node
    }
}

// Recursive function to output the tree in-order
void AVL_tree::inorder(nodeAVL *root)
{
    if(root == nullptr) {
        //std::cout << "Node is empty." << std::endl;
        return;
    }
    inorder(root->left);
    std::cout << "\t" << root->table.word << " has " << root->table.occurencies << " occurencies." << std::endl;
    inorder(root->right);
}

// Recursive function to output the tree pre-order
void AVL_tree::preorder(nodeAVL *root)
{
    if(root == nullptr) {
        //std::cout << "Node is empty." << std::endl;
        return;
    }
    std::cout << "\t" << root->table.word << " has " << root->table.occurencies << " occurencies." << std::endl;
    preorder(root->left);
    preorder(root->right);

}

// Recursive function to output the tree post-order
void AVL_tree::postorder(nodeAVL *root)
{
    if(root == nullptr) {
        //std::cout << "Node is empty." << std::endl;
        return;
    }
    postorder(root->left);
    postorder(root->right);
    std::cout << "\t" << root->table.word << " has " << root->table.occurencies << " occurencies." << std::endl;
}

// Function to delete the tree
void AVL_tree::deconstructor(nodeAVL* root)
{
    if(root == nullptr) return; // if the current node is already deleted(doesn't exist), do nothing

    if(root->left != nullptr) // if the left child exists
        deconstructor(root->left); // delete it

    if(root->right != nullptr) // if the right child exists
        deconstructor(root->right); // delete it

    delete root; // by now, the node's children are deleted, so delete the node
}
