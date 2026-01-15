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

int main()
{
    TreeNode *root;
    root = new TreeNode(1,
        new TreeNode(2,
            new TreeNode(4),
            new TreeNode(5)),
        new TreeNode(3,
            new TreeNode(6),
            new TreeNode(7)));

    cout << endl << "Preorder:" << endl;
    preorder(root);
    cout << endl << "Inorder:" << endl;
    inorder(root);
    cout << endl << "Postorder:" << endl;
    postorder(root);
    return 0;
}
