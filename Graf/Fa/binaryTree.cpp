#include <iostream>

using namespace std;

struct TreeNode {
    int data;
    TreeNode *left;
    TreeNode *right;

    TreeNode(int data)
    {
        this -> data = data;
        this -> left = 0;
        this -> right = 0;
    }
    TreeNode(int data, TreeNode *left, TreeNode *right)
    {
        this -> data = data;
        this -> left = left;
        this -> right = right;
    }
    ~TreeNode()
    {
        if(left)
            delete left;
        if(right)
            delete right;
    }
};

void preorder(TreeNode *root)
{
    if(root == 0)
        return;
    cout << root -> data << " ";
    preorder(root -> left);
    preorder(root -> right);
}

void inorder(TreeNode *root)
{
    if(root == 0)
        return;
    inorder(root -> left);
    cout << root -> data << " ";
    inorder(root -> right);
}

void postorder(TreeNode *root)
{
    if(root == 0)
        return;
    postorder(root -> left);
    postorder(root -> right);
    cout << root -> data << " ";
}

void printTree(TreeNode* node, string prefix = "", bool isLast = true, bool isRoot = true)
{
    if(!node) return;

    cout << prefix;

    if(!isRoot)
        cout << (isLast ? "\xc0\xc4\xc4" : "\xc3\xc4\xc4");

    cout << node->data << endl;

    if(!isRoot)
        prefix += (isLast ? "   " : "\xb3  ");

    //bal gyerek (ha van jobb akkor nem utolso, nem gyoker)
    if(node->left)
        printTree(node->left, prefix, node->right == nullptr, false);

    //jobb gyerek (utolso, nem gyoker)
    if(node->right)
        printTree(node->right, prefix, true, false);
}

int main()
{
    /*
    for(unsigned char c = 0; c < 255; c++)
        cout << hex << (int)c << ": " << c << endl;
    */

    TreeNode *root;
    root = new TreeNode(1,
        new TreeNode(2,
            new TreeNode(4),
            new TreeNode(5)),
        new TreeNode(3,
            new TreeNode(6),
            new TreeNode(7)));

    cout << "Tree structure:" << endl;
    printTree(root);

    cout << endl << "Preorder:" << endl;
    preorder(root);
    cout << endl << "Inorder:" << endl;
    inorder(root);
    cout << endl << "Postorder:" << endl;
    postorder(root);

    delete root;
    return 0;
}
