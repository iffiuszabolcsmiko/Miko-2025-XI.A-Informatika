#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

struct TreeNode
{
    int adat;
    TreeNode *parent, *left, *right;
    TreeNode(int adat, TreeNode *parent = 0, TreeNode *left = 0, TreeNode *right = 0)
    {
        this->adat = adat;
        this->parent = parent;
        this->left = left;
        this->right = right;
    }
    ~TreeNode()
    {
        if(left)
            delete left;
        if(right)
            delete right;
    }
};

class KeresoFa
{
    TreeNode *root;

    void beszur_rekurziv(TreeNode *p, int adat)
    {
        if(adat < p->adat)
        {
            if(p->left)
                beszur_rekurziv(p->left, adat);
            else
                p->left = new TreeNode(adat, p);
        }
        else
        {
            if(p->right)
                beszur_rekurziv(p->right, adat);
            else
                p->right = new TreeNode(adat, p);
        }
    }

    void inorder(TreeNode *root)
    {
        if(root == 0)
            return;
        inorder(root -> left);
        cout << root -> adat << " ";
        inorder(root -> right);
    }

    void printTree(TreeNode* node, string prefix = "", bool isLast = true, bool isRoot = true)
    {
        if(!node) return;

        cout << prefix;

        if(!isRoot)
            cout << (isLast ? "\xc0\xc4\xc4" : "\xc3\xc4\xc4");

        cout << node->adat << endl;

        if(!isRoot)
            prefix += (isLast ? "   " : "\xb3  ");

        //bal gyerek (ha van jobb akkor nem utolso, nem gyoker)
        if(node->left)
            printTree(node->left, prefix, node->right == nullptr, false);

        //jobb gyerek (utolso, nem gyoker)
        if(node->right)
            printTree(node->right, prefix, true, false);
    }
public:

    KeresoFa()
    {
        root = 0;
    }

    ~KeresoFa()
    {
        if(root)
            delete root;
    }

    void beszur(int adat)
    {
        if(root == 0)
            root = new TreeNode(adat);
        else
            beszur_rekurziv(root, adat);
    }

    void kiir()
    {
        inorder(root);
        cout << endl;
    }

    void kiirFa()
    {
        printTree(root);
        cout << endl;
    }

    TreeNode *keres(int elem)
    {
        TreeNode*p = root;
        while(p != 0 && p->adat != elem)
        {
            if(p->adat < elem) p = p->right;
            else p = p->left;
        }
        return p;
    }

    int minimum()
    {
        TreeNode *p = root;
        while(p != 0 && p->left != 0)
        {
            p = p->left;
        }
        if(p == 0)
            return 0;
        else
            return p->adat;
    }
    int maximum()
    {
        TreeNode *p = root;
        while(p != 0 && p->right != 0)
        {
            p = p->right;
        }
        if(p == 0)
            return 0;
        else
            return p->adat;
    }
};

int main()
{
    srand(time(0));

    KeresoFa a;
    for(int i = 0; i < 15; i++){
        a.beszur(rand() % 100);
    }
    a.beszur(42);

    a.kiir();
    a.kiirFa();
    cout << "Keres 42: " << a.keres(42) << endl;
    cout << "Min: " << a.minimum() << endl;
    cout << "Max: " << a.maximum() << endl;
    return 0;
}
