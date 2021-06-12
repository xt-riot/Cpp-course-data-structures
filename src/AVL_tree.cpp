#include "AVL_tree.h"

/*  ============================================================ *
 *                      PUBLIC CLASSES                           *
 *  ============================================================ */

AVL_tree::AVL_tree()
{
    std::cout << "AVL Tree constructor." << std::endl;
    tree = nullptr;
}

void AVL_tree::addWord(std::string word)
{
    dataAVL temp;
    temp.occurencies = 1;
    temp.word = word;

    if (word.empty()) return;

    if (tree == nullptr) {
        //std::cout << "Tree is empty - inserting " << word << " at root." << std::endl;
        tree = newPointer(temp, tree);
        return;
    }
    else {
        //std::cout << "Trying to insert the word: " << word << std::endl;
        tree = insertNewNode(temp, tree);
        tree = reconstruct(tree);
    }
}

void AVL_tree::deleteWord(std::string word)
{
    //std::cout << "Trying to find the node holding the word " << word << " in the tree..." << std::endl;
    tree = deleteNode(word, tree);
    //std::cout << "Deleted the word. Reconstructing the tree..." << std::endl;
    tree = reconstruct(tree);
}

void AVL_tree::findWord(std::string word)
{
    nodeAVL *temp = searchNode(word, tree);
    if(temp != nullptr)
        std::cout << "Requested word " << temp->table.word << " was found " << temp->table.occurencies << " time(s) in the text." << std::endl;
    else
        std::cout << "Requested word " << word << " was not found in the tree." << std::endl;
}

void AVL_tree::postorder()
{
    std::cout << "Post-order traversal:" << std::endl;
    postorder(tree->left);
    postorder(tree->right);
    std::cout << "\troot " << tree->table.word << " has " << tree->table.occurencies << " occurencies." << std::endl;

}

void AVL_tree::inorder()
{
    std::cout << "In-order traversal:" << std::endl;
    inorder(tree->left);
    std::cout << "\troot " << tree->table.word << " has " << tree->table.occurencies << " occurencies." << std::endl;
    inorder(tree->right);
}

void AVL_tree::preorder()
{
    std::cout << "Pre-order traversal:" << std::endl;
    std::cout << "\troot " << tree->table.word << " has " << tree->table.occurencies << " occurencies." << std::endl;
    preorder(tree->left);
    preorder(tree->right);
}

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
    int diff = subTreeDifference(root);
    if (diff > 1) {
        if (subTreeDifference(root->left) > 0)
            root = LL_rotate(root);
        else
            root = LR_rotate(root);
    }
    else if (diff < -1) {
        if (subTreeDifference(root->right) > 0)
            root = RL_rotate(root);
        else
            root = RR_rotate(root);
    }
    return root;
}

nodeAVL* AVL_tree::RR_rotate(nodeAVL* root)
{
    nodeAVL *temp = new nodeAVL;
    temp = root->right;
    root->right = temp->left;
    temp->left = root;
    //std::cout << "\t\tPerformed right-right rotation." << std::endl;
    return temp;
}

nodeAVL* AVL_tree::RL_rotate(nodeAVL* root)
{
    nodeAVL *temp = new nodeAVL;
    temp = root->right;
    root->right = LL_rotate(temp);
    //std::cout << "\t\tPerformed right-left rotation." << std::endl;
    return RR_rotate(root);
}

nodeAVL* AVL_tree::LL_rotate(nodeAVL* root)
{
    nodeAVL *temp = new nodeAVL;
    temp = root->left;
    root->left = temp->right;
    temp->right = root;
    //std::cout << "\t\tPerformed left-left rotation." << std::endl;
    return temp;
}

nodeAVL* AVL_tree::LR_rotate(nodeAVL* root)
{
    nodeAVL *temp = new nodeAVL;
    temp = root->left;
    root->left = RR_rotate(temp);
    //std::cout << "\t\tPerformed left-right rotation." << std::endl;
    return LL_rotate(root);
}

int AVL_tree::height(nodeAVL* root)
{
    int h = 0;
    if (root != nullptr) {
        int left = height(root->left);
        int right = height(root->right);
        int max_height = (left > right) ? left : right;
        h = max_height + 1;
    }
    //std::cout << "\t\tThe tree has height equal to " << h << std::endl;
    return h;
}

int AVL_tree::subTreeDifference(nodeAVL* root)
{
    int left = height(root->left);
    int right = height(root->right);
    //std::cout << "\t\t\tThe left and right subtrees have a difference of " << (left - right) << std::endl;
    return (left - right);
}


nodeAVL* AVL_tree::newPointer(dataAVL key, nodeAVL *root)
{
    root = new nodeAVL;
    root->table = key;
    root->left = nullptr;
    root->right = nullptr;
    return root;
}

nodeAVL* AVL_tree::insertNewNode(dataAVL key, nodeAVL *root)
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

nodeAVL* AVL_tree::deleteNode(std::string key, nodeAVL *root)
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


nodeAVL* AVL_tree::searchNode(std::string key, nodeAVL* root)
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

void AVL_tree::deconstructor(nodeAVL* root)
{
    if(root == nullptr) return;

    if(root->left != nullptr)
        deconstructor(root->left);

    if(root->right != nullptr)
        deconstructor(root->right);

    delete root;
}
