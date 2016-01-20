#include <iostream>

using namespace std;

struct tree
{
    int data1;
    int data2;
	struct tree *left;  // Pointer to the left subtree
	struct tree *mid; // Pointer to the middle subtree
	struct tree *right;  // Pointer to the right subtree
    struct tree *parent; // A pointer to the parent
    int node; // 2 node or 3 node
};

tree* restructure(tree *root, int val)
{
    tree* current = new tree;
    current = root;

    int v1 = current->data1;
    int v2 = current->data2;
    int v3 = val;

    if(current->parent == NULL) //no parent i.e root
    {
        tree* newnode1 = new tree;
        newnode1->data1 = 0;
        newnode1->data2 = -1;
        newnode1->left = NULL;
        newnode1->right = NULL;
        newnode1->mid = NULL;
        newnode1->parent = NULL;
        newnode1->node = 2;

        tree* newnode2 = new tree;
        newnode2->data1 = 0;
        newnode2->data2 = -1;
        newnode2->left = NULL;
        newnode2->right = NULL;
        newnode2->mid = NULL;
        newnode2->parent = NULL;
        newnode2->node = 2;

        if(v2 < v3)
        {
            //1 2 3
            newnode1->data1 = v1;
            current->data1 = v2;
            current->data2 = -1;
            newnode2->data1 = v3;
            current->left = newnode1;
            current->right = newnode2;
            newnode1->parent = current;
            newnode2->parent = current;
            current->node = 2;
        }
        else if (v1 < v3)
        {
            //1 3 2
            newnode1->data1 = v1;
            current->data1 = v3;
            newnode2->data1 = v2;
            current->data2 = -1;
            current->left = newnode1;
            current->right = newnode2;
            newnode1->parent = current;
            newnode2->parent = current;
            current->node = 2;
        }
        else
        {
            //3 1 2
            newnode1->data1 = v3;
            newnode2->data1 = v2;
            current->data2 = -1;
            current->left = newnode1;
            current->right = newnode2;
            newnode1->parent = current;
            newnode2->parent = current;
            current->node = 2;
        }
    } //no parent i.e root
    else //parent present
    {
        tree* parent = new tree;
        parent = current->parent;
        int v4 = parent->data1;
        if(parent->node == 2) //parent is 2 node
        {
            tree* newnode1 = new tree;
            newnode1->data1 = 0;
            newnode1->data2 = -1;
            newnode1->left = NULL;
            newnode1->right = NULL;
            newnode1->mid = NULL;
            newnode1->parent = NULL;
            newnode1->node = 2;

            if(v3 < v4)
            {
                //left child
                if(v2 < v3)
                {
                    //1 2 3
                    parent->data2 = v1;
                    parent->data1 = v2;
                    current->data2 = -1;
                    newnode1->data1 = v3;
                    parent->mid = newnode1;
                    newnode1->parent = parent;
                    current->node = 2;
                    parent->node = 3;
                }
                else if (v1 < v3)
                {
                    //1 3 2
                    parent->data2 = v4;
                    parent->data1 = v3;
                    newnode1->data1 = v2;
                    current->data2 = -1;
                    parent->mid = newnode1;
                    newnode1->parent = parent;
                    current->node = 2;
                    parent->node = 3;
                }
                else
                {
                    //3 1 2
                    parent->data2 = v4;
                    parent->data1 = v1;
                    current->data1 = v3;
                    newnode1->data1 = v2;
                    current->data2 = -1;
                    parent->mid = newnode1;
                    newnode1->parent = parent;
                    current->node = 2;
                    parent->node = 3;
                }
            }
            else
            {
                //right child
                if(v2 < v3)
                {
                    //1 2 3
                    parent->data2 =  v2;
                    current->data2 = -1;
                    newnode1->data1 = v1;
                    parent->mid = newnode1;
                    newnode1->parent = parent;
                    current->data1 = v3;
                    current->node = 2;
                    parent->node = 3;
                }
                else if (v1 < v3)
                {
                    //1 3 2
                    parent->data2 = v3;
                    newnode1->data1 = v1;
                    parent->mid = newnode1;
                    current->data1 = v2;
                    current->data2 = -1;
                    newnode1->parent = parent;
                    current->node = 2;
                    parent->node = 3;
                }
                else
                {
                    //3 1 2
                    parent->data2 = v1;
                    newnode1->data1 = v3;
                    parent->mid = newnode1;
                    current->data1 = v2;
                    current->data2 = -1;
                    newnode1->parent = parent;
                    current->node = 2;
                    parent->node = 3;
                }
            }
        } //parent is 2 node
        else if(parent->node == 3) //parent is 3 node
        {
            //parent needs restructure //left right mid
            v4 = parent->data1;
            int v5 = parent->data2;

            tree* newnode1 = new tree;
            newnode1->data1 = 0;
            newnode1->data2 = -1;
            newnode1->left = NULL;
            newnode1->right = NULL;
            newnode1->mid = NULL;
            newnode1->parent = NULL;
            newnode1->node = 2;

            if(v3 < v4)
            {
                //left child
                if(v2 < v3)
                {
                    //1 2 3
                    tree* mid = new tree;
                    mid = parent->mid;
                    tree* right = new tree;
                    right = parent->right;
                    mid->parent = NULL;
                    current->parent = NULL;
                    right->parent = NULL;

                    parent = restructure(parent, v2);
                    current->data2 = -1;

                    tree* pright = new tree;
                    pright = parent->right;
                    tree* pleft = new tree;
                    pleft = parent->left;

                    pright->right = right;
                    right->parent = pright;
                    pright->left = mid;
                    mid->parent = pright;

                    newnode1->data1 = v3;
                    pleft->right = newnode1;
                    newnode1->parent = pleft;
                    pleft->left = current;
                    current->parent = pleft;
                    current->node = 2;
                }
                else if (v1 < v3)
                {
                    //1 3 2
                    tree* mid = new tree;
                    mid = parent->mid;
                    tree* right = new tree;
                    right = parent->right;
                    mid->parent = NULL;
                    current->parent = NULL;
                    right->parent = NULL;

                    parent = restructure(parent, v3);

                    tree* pright = new tree;
                    pright = parent->right;
                    tree* pleft = new tree;
                    pleft = parent->left;

                    pright->right = right;
                    right->parent = pright;
                    pright->left = mid;
                    mid->parent = pright;

                    newnode1->data1 = v2;
                    current->data2 = -1;
                    pleft->right = newnode1;
                    newnode1->parent = pleft;
                    pleft->left = current;
                    current->parent = pleft;
                    current->node = 2;
                }
                else
                {
                    //3 1 2
                    tree* mid = new tree;
                    mid = parent->mid;
                    tree* right = new tree;
                    right = parent->right;
                    mid->parent = NULL;
                    current->parent = NULL;
                    right->parent = NULL;

                    parent = restructure(parent, v1);

                    tree* pright = new tree;
                    pright = parent->right;
                    tree* pleft = new tree;
                    pleft = parent->left;

                    pright->right = right;
                    right->parent = pright;
                    pright->left = mid;
                    mid->parent = pright;

                    newnode1->data1 = v3;
                    pleft->left = newnode1;
                    newnode1->parent = pleft;
                    current->data1 = v2;
                    current->data2 = -1;
                    pleft->right = current;
                    current->parent = pleft;
                    current->node = 2;
                }
            }
            else if(v3 < v5)
            {
                //mid child
                if(v2 < v3)
                {
                    //1 2 3
                    tree* left = new tree;
                    left = parent->left;
                    tree* right = new tree;
                    right = parent->right;
                    left->parent = NULL;
                    current->parent = NULL;
                    right->parent = NULL;

                    parent = restructure(parent, v2);
                    current->data2 = -1;

                    tree* pright = new tree;
                    pright = parent->right;
                    tree* pleft = new tree;
                    pleft = parent->left;

                    pright->right = right;
                    right->parent = pright;
                    newnode1->data1 = v3;
                    pright->left = newnode1;
                    newnode1->parent = pright;

                    pleft->right = current;
                    current->parent = pleft;
                    pleft->left = left;
                    left->parent = pleft;
                    current->node = 2;
                }
                else if (v1 < v3)
                {
                    //1 3 2
                    tree* left = new tree;
                    left = parent->left;
                    tree* right = new tree;
                    right = parent->right;
                    left->parent = NULL;
                    current->parent = NULL;
                    right->parent = NULL;

                    parent = restructure(parent, v3);

                    tree* pright = new tree;
                    pright = parent->right;
                    tree* pleft = new tree;
                    pleft = parent->left;

                    pright->right = right;
                    right->parent = pright;
                    newnode1->data1 = v2;
                    current->data2 = -1;
                    pright->left = newnode1;
                    newnode1->parent = pright;

                    pleft->right = current;
                    current->parent = pleft;
                    pleft->left = left;
                    left->parent = pleft;
                    current->node = 2;
                }
                else
                {
                    //3 1 2
                    tree* left = new tree;
                    left = parent->left;
                    tree* right = new tree;
                    right = parent->right;
                    left->parent = NULL;
                    current->parent = NULL;
                    right->parent = NULL;

                    parent = restructure(parent, v1);

                    tree* pright = new tree;
                    pright = parent->right;
                    tree* pleft = new tree;
                    pleft = parent->left;

                    pright->right = right;
                    right->parent = pright;
                    current->data1 = v2;
                    current->data2 = -1;
                    pright->left = current;
                    current->parent = pright;

                    newnode1->data1 = val;
                    pleft->right = newnode1;
                    newnode1->parent = pleft;
                    pleft->left = left;
                    left->parent = pleft;
                    current->node = 2;
                }
            }
            else
            {
                //right child
                if(v2 < v3)
                {
                    //1 2 3
                    tree* mid = new tree;
                    mid = parent->mid;
                    tree* left = new tree;
                    left = parent->left;
                    mid->parent = NULL;
                    current->parent = NULL;
                    left->parent = NULL;

                    parent = restructure(parent, v2);
                    current->data2 = -1;

                    tree* pright = new tree;
                    pright = parent->right;
                    tree* pleft = new tree;
                    pleft = parent->left;

                    pleft->left = left;
                    left->parent = pleft;
                    pleft->right = mid;
                    mid->parent = pleft;

                    newnode1->data1 = v3;
                    pright->right = newnode1;
                    newnode1->parent = pright;
                    pright->left = current;
                    current->parent = pright;
                    current->node = 2;
                }
                else if (v1 < v3)
                {
                    //1 3 2
                    tree* mid = new tree;
                    mid = parent->mid;
                    tree* left = new tree;
                    left = parent->left;
                    mid->parent = NULL;
                    current->parent = NULL;
                    left->parent = NULL;

                    parent = restructure(parent, v3);

                    tree* pright = new tree;
                    pright = parent->right;
                    tree* pleft = new tree;
                    pleft = parent->left;

                    pleft->left = left;
                    left->parent = pleft;
                    pleft->right = mid;
                    mid->parent = pleft;

                    newnode1->data1 = v2;
                    current->data2 = -1;
                    pright->right = newnode1;
                    newnode1->parent = pright;
                    pright->left = current;
                    current->parent = pright;
                    current->node = 2;
                }
                else
                {
                    //3 1 2
                    tree* mid = new tree;
                    mid = parent->mid;
                    tree* left = new tree;
                    left = parent->left;
                    mid->parent = NULL;
                    current->parent = NULL;
                    left->parent = NULL;

                    parent = restructure(parent, v1);

                    tree* pright = new tree;
                    pright = parent->right;
                    tree* pleft = new tree;
                    pleft = parent->left;

                    pleft->left = left;
                    left->parent = pleft;
                    pleft->right = mid;
                    mid->parent = pleft;

                    newnode1->data1 = v3;
                    pright->left = newnode1;
                    newnode1->parent = pright;
                    current->data1 = v2;
                    current->data2 = -1;
                    pright->right = current;
                    current->parent = pright;
                    current->node = 2;
                }
            }
        } //parent is 3 node
    }
    return current;
}

tree* insert( tree* root,int val)
{
    tree* current = new tree;
    current = root;

    if(current == NULL)  //root
    {
        tree* newnode = new tree;
        newnode->data1 = val;
        newnode->data2 = -1;
        newnode->left = NULL;
        newnode->right = NULL;
        newnode->mid = NULL;
        newnode->parent = NULL;
        newnode->node = 2;

        //cout<<"yes"<<endl;
        current = newnode;
    }
    else if(current->node == 2) //node is 2 node
     {
        if(current->left == NULL)
        {
            if(current->data1 < val)
            {
                current->data2 = val;
                current->node = 3;
            }
            else
            {
                current->data2 = current->data1;
                current->data1 = val;
                current->node = 3;
            }
        }
        else if(current->data1 < val)
        {
            current->right = insert (current->right, val); //insert in right subtree
        }
        else
        {
            current->left = insert (current->left, val); //insert in left subtree
        }
    }
    else if (current->node == 3) //node is 3 node
    {
        if(current->left == NULL)
        {
            //restructure
            current = restructure(current, val);
        }
        else if(val < current->data1)
        {
            current->left = insert (current->left, val); //insert in left subtree
        }
        else if(val < current->data2)
        {
            current->mid = insert (current->mid, val); //insert in mid subtree
        }
        else
        {
            current->right = insert (current->right, val); //insert in right subtree
        }
    }
    return current;
}

int inorder (tree *node)
{
    int count=0;
    if (node == NULL)
    {
        return count;
    }
    else
    {
        count++;
        count += inorder(node->left);
        cout<< " " << node->data1 << " ";
        if(node->node == 3)
        {
            count += inorder(node->mid);
            cout<<" " << node->data2 <<" ";
        }
        count +=inorder(node->right);
    }
    return count;
}

int main()
{
    struct tree *root = NULL;

    if(inorder(root) == 0)
        cout<<" Tree is empty"<<endl;

    root = insert(root, 10);
    root = insert(root, 7);
    root = insert(root, 20);
    root = insert(root, 115);
    root = insert(root, 1);
    root = insert(root, -5);
    root = insert(root, -15);

    if(inorder(root) == 0)
        cout<<" Tree is empty"<<endl;

    return 0;
}
